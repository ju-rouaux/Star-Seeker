/**
 * \file particules.c
 * 
 * \brief Module de définition de particules
 * 
 * \author Julien Rouaux
 */


#include <stdio.h>
#include <stdlib.h>
#include <moteur.h>
#include <particules.h>
#include <math.h>
#include <outils.h>


/** 
 * \brief Mets à jour la particule ou la détruit si sa durée de vie est terminée.
 * 
 * \param moteur Le moteur du jeu
 * \param particule La particule à actualiser
 * \param j_x Position en x du joueur
 * \param j_y Position en y du joueur
 * 
 * \return -1 si la particule doit être détruite, sinon 0.
 */
static int updateParticule(t_moteur * moteur, t_particule * particule, float j_x, float j_y)
{
    particule->duree_de_vie -= moteur->temps - moteur->temps_precedent; //Retirer le temps écoulé à la durée de vie 
    if(particule->duree_de_vie <= 0)
        return -1;

    if(particule->type_particule == P_XP)
    {
        int norme;
        particule->direction_vx = j_x - particule->x;
        particule->direction_vy = j_y - particule->y;
        norme = sqrt(pow(particule->direction_vx, 2) + pow(particule->direction_vy, 2));
        if(norme == 0)
            return -1;
        else
            particule->vitesse = 15.0 / norme;
    }

    return deplacerEntite(moteur, (t_entite*) particule);
}


/**
 * \brief Création d'une particule.
 * 
 * \param type La nature de la particule désirée
 * \param x La position de départ en x
 * \param y La position de départ en y
 * \param texture Tileset des particules
 * 
 * \return Le pointeur particule (NULL si echec).
 */
t_particule * creerParticule(e_type_particule type, float x, float y, SDL_Texture * texture)
{
    t_entite * entite = creerEntite(x, y, texture);
    t_particule * particule = realloc(entite, sizeof(t_particule));
    if(particule == NULL)
    {
        detruireEntite(&entite);
        return NULL;
    }
    entite = NULL;

    particule->type = E_PARTICULE;
    particule->update = (int (*)(t_moteur *, t_entite *, float, float)) updateParticule;
    particule->type_particule = type;

    switch (type)
    {
    case P_MORT:
        particule->animation = creerAnimation(50, 16);
        particule->id_animation = 0;
        particule->taille = 0.8;
        particule->duree_de_vie = 800;
        particule->direction_vx = 0;
        particule->direction_vy = -1;
        particule->vitesse = 0.5;
        break;
    
    case P_TOUCHE:
        particule->id_animation = 1;
        particule->taille = 0.3;
        particule->duree_de_vie = 300;
        break;

    case P_XP:
        particule->animation = creerAnimation(70, 16);
        particule->id_animation = 2;
        particule->taille = 0.4;
        particule->duree_de_vie = 10000;
        particule->x += (-5.0 + de(10)) / 5;
        particule->y += (-5.0 + de(10)) / 5;
        break;

    case P_DASH:
        particule->animation = creerAnimation(100, 4);
        particule->id_animation = 3;
        particule->taille = 0.9;
        particule->duree_de_vie = 400;
        break;

    default:
        detruireEntite((t_entite**) &particule);
        return NULL;
    }

    return particule;
}
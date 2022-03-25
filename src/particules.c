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


/** 
 * \brief Mets à jour la particule ou la détruit si sa durée de vie est terminée.
 * 
 * \param moteur Le moteur du jeu
 * \param projectile La particule à actualiser
 * 
 * \return -1 si la particule doit être détruite, sinon 0.
 */
static int updateParticule(t_moteur * moteur, t_particule * particule)
{
    particule->duree_de_vie -= moteur->temps - moteur->temps_precedent; //Retirer le temps écoulé à la durée de vie 
    if(particule->duree_de_vie <= 0)
        return -1;

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

    switch (type)
    {
    case P_MORT:
        particule->id_animation = 0;
        particule->taille = 0.8;
        particule->duree_de_vie = 800;
        particule->direction_vy = -1;
        particule->vitesse = 0.5;
        break;
    
    case P_TOUCHE:
        particule->id_animation = 1;
        particule->taille = 0.5;
        particule->duree_de_vie = 100;
        break;

    default:
        detruireEntite((t_entite**) &particule);
        return NULL;
    }

    return particule;
}
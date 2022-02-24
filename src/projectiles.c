/**
 * \file projectiles.h
 * 
 * \brief Module de définition de projectiles
 * 
 * \author Julien Rouaux
 */

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <moteur.h>
#include <entite.h>
#include <animation.h>
#include <projectiles.h>


#define NB_PROJECTILES_DIFFERENTS 1 //Pour l'id max d'animation


/** 
 * \brief Fonction générique de projectile lui donnant une trajectoire en ligne
 * à vitesste constante.
 * 
 * \param moteur Le moteur du jeu
 * \param projectile Le projectile à actualiser
 * 
 * \return -1 si le projectile doit être détruit.
 */
static int updateProjectile(t_moteur * moteur, t_projectile * projectile)
{
    //Si l'on souhaite on peut faire des fonctions spécifiques à un projectile,
    //par exemple pour lui donner une trajectoire courbée en variant sa direction
    projectile->duree_de_vie -= moteur->temps - moteur->temps_precedent; //Retirer le temps écoulé à la durée de vie 
    if(projectile->duree_de_vie <= 0)
        return -1;

    return deplacerEntite(moteur, (t_entite*) projectile);
}


/**
 * \brief Fonction de spécialisation d'un projectile pour sa création.
 * 
 * Ce projectile est de petite taille mais rapide.
 * 
 * \param projectile Le projectile venant d'être créé
 * 
 * \return 0 si succès, une valeur négative si echec.
 */
static int proj_balle(t_projectile * projectile)
{
    projectile->animation = NULL; //Pas d'animation
    projectile->id_animation = 0;

    projectile->taille = 0.4;
    projectile->vitesse = 4;
    projectile->dommages = 20;
    projectile->duree_de_vie = 1500;

    projectile->update = (int (*)(t_moteur*, t_entite*)) updateProjectile;

    return 0;
}


/**
 * \brief Fonction de spécialisation d'un projectile pour sa création.
 * 
 * Ce projectile est de grande taille mais lent.
 * 
 * \param projectile Le projectile venant d'être créé
 * 
 * \return 0 si succès, une valeur négative si echec.
 */
static int proj_boule_feu(t_projectile * projectile)
{
    projectile->animation = creerAnimation(1000, 2, NB_PROJECTILES_DIFFERENTS);
    if(projectile->animation == NULL)
        return -1;
    projectile->id_animation = 1;

    projectile->taille = 0.7;
    projectile->vitesse = 2;
    projectile->dommages = 30;
    projectile->duree_de_vie = 3000;

    projectile->update = (int (*)(t_moteur*, t_entite*)) updateProjectile;

    return 0;
}


/**
 * \brief Libère la mémoire allouée à une structure projectile.
 * 
 * \param projectile L'adresse du pointeur du projectile
 */
void detruireProjectile(t_projectile ** projectile)
{
    if(*projectile != NULL)
    {
        if((*projectile)->animation != NULL)
            detruireAnimation(&(*projectile)->animation);
        free(*projectile);
    }
    *projectile = NULL;
}


/**
 * \brief Création d'un projectile.
 * 
 * \param type La nature du projectile désiré
 * \param x La position de départ en x
 * \param y La position de départ en y
 * \param direction_vx Sa direction en x
 * \param direction_vy Sa direction en y
 * \param cible Le type de l'entité qui doit subir des dégats s'il est touché
 * \param texture Tileset des projectiles
 * 
 * \return Le pointeur projectile (NULL si echec).
 */
t_projectile * creerProjectile(e_type_projectile type, float x, float y, float direction_vx, float direction_vy, e_type_entite cible, SDL_Texture * texture)
{
    int retour = 0; //Retour de fonction pour gérer les cas d'erreur
    t_projectile * projectile = malloc(sizeof(t_projectile));
    if(projectile == NULL)
        return NULL;

    //Données spécifiques au projectile
    switch (type)
    {
    case BALLE:
        retour = proj_balle(projectile);
        break;
    case BOULE_FEU:
        retour = proj_boule_feu(projectile);
        break;
    default:
        printf("Type projectile inconnu, annulation...\n");
        free(projectile);
        return NULL;
        break;
    }

    if(retour != 0)
    {
        free(projectile);
        return NULL;
    }

    //Données communes au projectile
    projectile->x = x;
    projectile->y = y;
    projectile->direction_vx = direction_vx;
    projectile->direction_vy = direction_vy;
    projectile->cible = cible;
    projectile->type = E_PROJECTILE;
    projectile->texture = texture;

    projectile->hitbox.h = 0;
    projectile->hitbox.w = 0;
    projectile->hitbox.x = 0;
    projectile->hitbox.y = 0;

    projectile->detruire = (void (*)(t_entite**)) detruireProjectile;

    return projectile;
}

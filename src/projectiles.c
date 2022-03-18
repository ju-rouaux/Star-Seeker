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


// ----------------------- Définition -----------------------

//Liste des projectiles disponibles
#include <definitions/definitions_projectiles.h>


/**
 * \brief Actualise les champs de la structure projectile vers les paramètres décrits par le type.
 * 
 * \param projectile Le projectile à actualiser
 * \param nouvelle_attaque La description désirée 
 */
int chargerProjectile(t_projectile * projectile, e_type_projectile type)
{
    switch (type)
    {
    case BALLE:
        return proj_balle(projectile);
    case BOULE_FEU:
        return proj_boule_feu(projectile);
    case BOULET:
        return proj_boule_metal(projectile);
    case SHURIKEN:
        return proj_shuriken(projectile);
    case SABRE:
        return proj_sabre(projectile);
    default:
        printf("Type projectile inconnu, annulation...\n");
        return -1;
    }
}


// ----------------------- Fonctionnement -----------------------


/**
 * \brief Libère la mémoire allouée à une structure projectile.
 * 
 * \param projectile L'adresse du pointeur du projectile
 */
void detruireProjectile(t_projectile ** projectile)
{
    if(*projectile != NULL)
    {
        detruireEntite((t_entite**) projectile);
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
    t_entite * entite = creerEntite(x, y, texture);
    t_projectile * projectile = realloc(entite, sizeof(t_projectile));
    if(projectile == NULL)
    {
        detruireEntite(&entite);
        return NULL;
    }
    entite = NULL;

    //Données spécifiques au projectile
    retour = chargerProjectile(projectile, type);

    if(retour != 0)
    {
        free(projectile);
        return NULL;
    }

    //Données communes au projectile
    projectile->direction_vx = direction_vx;
    projectile->direction_vy = direction_vy;
    projectile->type = E_PROJECTILE;

    projectile->detruire = (void (*)(t_entite**)) detruireProjectile;

    projectile->cible = cible;

    return projectile;
}

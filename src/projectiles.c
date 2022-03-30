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
#include <personnage.h>
#include <joueur.h>
#include <liste.h>
#include <projectiles.h>


// ----------------------- Définition -----------------------

//Liste des projectiles disponibles
#include <definitions/definitions_projectiles.h>


/**
 * \brief Actualise les champs de la structure projectile vers les paramètres décrits par le type.
 * 
 * \param projectile Le projectile à actualiser
 * \param type Le type de projectile
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
    case TOURNER:
        return proj_tourner(projectile);
    case SABRE:
        return proj_sabre(projectile);
    //case LASER:
    //    return proj_laser(projectile);
    default:
        printf("Type projectile inconnu, annulation...\n");
        return -1;
    }
}


// ----------------------- Fonctionnement -----------------------


/**
 * \brief Pour le projectile donné, cette fonction traverse la liste des entités ainsi que le joueur
 * à la recherche d'une cible avec laquelle le projectile pourrait être en collision.
 * 
 * \param projectile Le projectile cherchant une cible
 * \param joueur Le joueur
 * \param liste La liste des entités
 * 
 * \return -1 si collision avec une entité, sinon 0.
 */
int faireDegats(t_projectile * projectile, t_joueur * joueur, t_liste * liste)
{
    //Sauvegarde de la tête de la liste, pour la remettre à cet endroit à la fin de la fonction
    t_element * sauvElementCourant = liste->ec; 
    t_personnage * monstre;
    
    //Si joueur est cible
    SDL_Rect hitbox_joueur; //Calculer une hitbox plus petite pour le joueur
    hitbox_joueur.x = joueur->hitbox.x + joueur->hitbox.w/3;
    hitbox_joueur.y = joueur->hitbox.y;
    hitbox_joueur.w = joueur->hitbox.w/3;
    hitbox_joueur.h = 9*joueur->hitbox.h/10;
    if(projectile->cible == E_JOUEUR && SDL_HasIntersection(&projectile->hitbox, &hitbox_joueur))
    {
        joueur->pv -= projectile->dommages;
        return -1;
    }
    else //Si le reste est cible
    {
        en_tete(liste);
        while(!hors_liste(liste))
        {
            valeur_elt(liste, (t_entite**) &monstre);
            if(monstre->type == E_MONSTRE && projectile->cible == E_MONSTRE && SDL_HasIntersection(&projectile->hitbox, &monstre->hitbox))
            {
                monstre->pv -= projectile->dommages;
                liste->ec = sauvElementCourant; //Replacer la tête de la liste
                return -1;
            }
            suivant(liste);
        }
    }

    liste->ec = sauvElementCourant; //Replacer la tête de la liste

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

/**
 *\file player.c 
 * 
 *
 * \brief Module de gestion de deplacement du joueur
 * \author Julien Rouaux & Guillaume Richard
 */

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <moteur.h>
#include <entite.h>
#include <animation.h>
#include <joueur.h>

/**
 * 
 * 
 * code 0 idle, 1 marche, 2 attaque epee, 3 projectile
 */
static int getIdAnimationJoueur(int vecteur_x, int vecteur_y, int code_animation)
{
    int id_animation;

    //Calculer direction
    if(!vecteur_x && !vecteur_y) //Si vecteur nul, personage idle vers l'avant
        id_animation = 4;
    else
    {
        if(vecteur_x && !vecteur_y) //Droite ou gauche 
            id_animation = vecteur_x > 0 ? 2 : 6;
        else if(!vecteur_x && vecteur_y) //Haut ou bas
            id_animation = vecteur_y > 0 ? 4 : 0;
        else //Diagonales
        {
            if(vecteur_x > 0)
                id_animation = vecteur_y > 0 ? 3 : 1;
            else
                id_animation = vecteur_y > 0 ? 5 : 7;
        }
    }

    //Calculer animation
    id_animation = 2*id_animation + code_animation;
    
    return id_animation;
}

static void getDirectionJoueur(t_joueur_flags * flags, float * vecteur_x, float * vecteur_y)
{
    int direction_x = flags->to_right == flags->to_left ? 0 : (flags->to_right > flags->to_left ? 1 : -1);
    int direction_y = flags->to_down == flags->to_up ? 0 : (flags->to_down > flags->to_up ? 1 : -1);
    
    if(direction_x || direction_y) //Si le joueur se dirige dans une direction, actualiser les vecteurs
    {
        if(vecteur_x != NULL)
                *vecteur_x = direction_x;
        if(vecteur_y != NULL)
                *vecteur_y = direction_y;
    }
}


/**
 * \brief Méthode appelée à chaque frame, permet de définir le comportement du joueur
 * 
 * 
 * 
 */
static int updateJoueur(t_moteur * moteur, t_joueur * joueur)
{
    int etat = 0;
    getDirectionJoueur(joueur->flags, &joueur->direction_vx, &joueur->direction_vy);
    
    //Déterminer l'état du joueur
    if(joueur->flags->to_down || joueur->flags->to_left || joueur->flags->to_right || joueur->flags->to_up) //Si joueur bouge
    {
        deplacerEntite(moteur, (t_entite*) joueur);
        etat = 1;
    }
    //if(attaque....) 

    joueur->id_animation = getIdAnimationJoueur((int)joueur->direction_vx, (int)joueur->direction_vy, etat);
    
    return 0;
}

static t_joueur_flags * creerJoueurFlags()
{
    t_joueur_flags * flags = malloc(sizeof(t_joueur_flags));
    if(flags == NULL)
    {
        printf("Impossible d'allouer la mémoire pour les flags du joueur\n");
        return NULL;
    }

    flags->to_down = 0;
    flags->to_up = 0;
    flags->to_left = 0;
    flags->to_right = 0;

    return flags;
}


static void detruireJoueurFlags(t_joueur_flags ** flags)
{
    if(*flags != NULL)
        free(*flags);
    *flags = NULL;
}


/**
 * 
 * 
 */
t_joueur * creerJoueur(float x, float y, SDL_Texture * apparence)
{
    t_joueur * joueur = malloc(sizeof(t_joueur));
    if(joueur == NULL)
    {
        printf("Impossible d'allouer la mémoire pour joueur\n");
        return NULL;
    }

    joueur->flags = creerJoueurFlags();
    if(joueur->flags == NULL)
    {
        printf("Le joueur n'a pas pu être créé\n");
        free(joueur);
        return NULL;
    }

    joueur->animation = creerAnimation(50, 4, 15);
    if(joueur->animation == NULL)
    {
        printf("Le joueur n'a pas pu être créé\n");
        detruireJoueurFlags(&joueur->flags);
        free(joueur);
        return NULL;
    }

    joueur->x = x;
    joueur->y = y;
    joueur->direction_vx = 0;
    joueur->direction_vy = 0;
    joueur->vitesse = 6.5;
    joueur->type = E_JOUEUR;

    joueur->texture = apparence;
    joueur->taille = PROPORTION_JOUEUR;
    joueur->id_animation = 0; //idle

    joueur->update = (int (*)(t_moteur*, t_entite*)) updateJoueur;

    joueur->pv = 100;

    return joueur;
}

/**
 * 
 * 
 */
void detruireJoueur(t_joueur ** joueur)
{
    if(*joueur != NULL)
    {
        detruireJoueurFlags(&(*joueur)->flags);
        detruireAnimation(&(*joueur)->animation);
        free(*joueur);
    }
    *joueur = NULL;
}


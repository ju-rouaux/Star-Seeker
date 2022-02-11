/**
 *\file player.c 
 * 
 *
 * \brief Module de gestion de deplacement du joueur
 * \author Guillaume et Julien Rouaux
 */

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <entite.h>
#include <joueur.h>
#include <animation.h>

/**
 * \brief Avance le joueur de "vitesse / FPS" pixels dans la direction indiquée par ses flags
 * 
 * 
 */
static void updatePositionJoueur(t_joueur * joueur)
{
    float distance = joueur->vitesse;
    joueur->x += distance * (joueur->flags->to_right - joueur->flags->to_left);
    joueur->y += distance * (joueur->flags->to_down - joueur->flags->to_up);
}

/**
 * \brief Méthode appelée à chaque frame, permet de définir le comportement du joueur
 * 
 * 
 * 
 */
static void updateJoueur(t_joueur * joueur, unsigned int temps)
{
    updatePositionJoueur(joueur);
    //Animation...
}

static t_player_flags * creerPlayerFlags()
{
    t_player_flags * flags = malloc(sizeof(t_player_flags));
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


static void detruirePlayerFlags(t_player_flags ** flags)
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

    joueur->flags = creerPlayerFlags();
    if(joueur->flags == NULL)
    {
        printf("Le joueur n'a pas pu être créé\n");
        free(joueur);
        return NULL;
    }

    joueur->animation = creerAnimation(0.2);
    if(joueur->animation == NULL)
    {
        printf("Le joueur n'a pas pu être créé\n");
        detruirePlayerFlags(&joueur->flags);
        free(joueur);
        return NULL;
    }

    joueur->x = x;
    joueur->y = y;
    joueur->vitesse = 0.15;
    joueur->pv = 100;

    joueur->texture = apparence;
    joueur->taille = PROPORTION_JOUEUR;
    joueur->nb_textures = 3;
    joueur->partie_texture_courrante = 0;
    
    joueur->type = E_JOUEUR;

    joueur->update = (void (*)(t_entite*, unsigned int)) updateJoueur;
    
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
        detruirePlayerFlags(&(*joueur)->flags);
        detruireAnimation(&(*joueur)->animation);
        free(*joueur);
    }
    *joueur = NULL;
}


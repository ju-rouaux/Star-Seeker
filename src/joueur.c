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
 * 
 * 
 * 
 */
static void animerJoueur(t_joueur * joueur, int vecteur_x, int vecteur_y, int code_animation)
{
    int id_animation;

    if(!vecteur_x && !vecteur_y) //Inactif
        id_animation = 0;
    else
    {
        if(vecteur_x && !vecteur_y) //Haut ou bas
            id_animation = vecteur_x > 0 ? 3 : 7;
        else if(!vecteur_x && vecteur_y) //Droite ou gauche
            id_animation = vecteur_y > 0 ? 5 : 1;
        else
        {
            if(vecteur_x > 0)
                id_animation = vecteur_y > 0 ? 4 : 2;
            else
                id_animation = vecteur_y > 0 ? 6 : 8;
        }
    }

    id_animation += code_animation;
}


/**
 * \brief Avance le joueur de "vitesse / FPS" pixels dans la direction indiquée par ses flags
 * 
 * \return La direction du joueur (0 si inactif, sinon entre 1 et 8 en partant du haut et en tournant dans le sens des aiguilles d'une montre)
 */
static void updatePositionJoueur(t_joueur * joueur, int * vecteur_x, int * vecteur_y)
{
    float distance = joueur->vitesse;
    int direction_x = joueur->flags->to_right == joueur->flags->to_left ? 0 : (joueur->flags->to_right > joueur->flags->to_left ? 1 : -1);
    int direction_y = joueur->flags->to_down == joueur->flags->to_up ? 0 : (joueur->flags->to_down > joueur->flags->to_up ? 1 : -1);
    
    joueur->x += distance * direction_x;
    joueur->y += distance * direction_y;

    if(vecteur_x != NULL)
        *vecteur_x = direction_x;
    if(vecteur_y != NULL)
        *vecteur_y = direction_y;
}

/**
 * \brief Méthode appelée à chaque frame, permet de définir le comportement du joueur
 * 
 * 
 * 
 */
static void updateJoueur(t_joueur * joueur, unsigned int temps)
{
    int vecteur_x, vecteur_y;
    updatePositionJoueur(joueur, &vecteur_x, &vecteur_y);
    
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


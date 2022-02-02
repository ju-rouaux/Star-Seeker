/**
 *\file player.c 
 * 
 *
 * \brief Module de gestion de deplacement du joueur
 * \author Guillaume
 */

#include <stdio.h>

#include <SDL2/SDL.h>
#include <moteur.h>
#include <joueur.h>
#include <camera.h>

/**
 * 
 * 
 */
t_position * creerPosition(int x, int y)
{
    t_position * position = malloc(sizeof(t_position));
    if(position == NULL)
    {
        printf("Impossible d'allouer la mémoire pour t_position\n");
        return NULL;
    }

    position->x = x;
    position->y = y;

    return position;
}

/**
 * 
 * 
 */
void detruirePosition(t_position ** position)
{
    if(*position != NULL)
        free(*position);
    *position = NULL;
}


t_player_flags * creerPlayerFlags()
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


void detruirePlayerFlags(t_player_flags ** flags)
{
    if(*flags != NULL)
        free(*flags);
    *flags = NULL;
}


/**
 * 
 * 
 */
t_joueur * creerJoueur(int x, int y)
{
    t_joueur * joueur = malloc(sizeof(t_joueur));
    if(joueur == NULL)
    {
        printf("Impossible d'allouer la mémoire pour joueur\n");
        return NULL;
    }

    joueur->position = creerPosition(x, y);
    if(joueur->position == NULL)
    {
        printf("Le joueur n'a pas pu être créé\n");
        free(joueur);
        return NULL;
    }

    joueur->flags = creerPlayerFlags();
    if(joueur->flags == NULL)
    {
        printf("Le joueur n'a pas pu être créé\n");
        detruirePosition(&joueur->position);
        free(joueur);
        return NULL;
    }

    joueur->vitesse = 0.18;
    
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
        detruirePosition(&(*joueur)->position);
        detruirePlayerFlags(&(*joueur)->flags);
        free(*joueur);
    }
    *joueur = NULL;
}


/**
 * \brief Avance le joueur de "vitesse / FPS" pixels dans la direction indiquée par ses flags
 * 
 * 
 */
void updatePositionJoueur(t_joueur * joueur, int echelle)
{
    float distance = joueur->vitesse * echelle;
    joueur->position->x += distance * (joueur->flags->to_right - joueur->flags->to_left);
    joueur->position->y += distance * (joueur->flags->to_down - joueur->flags->to_up);
}

/**
 * \brief modifie les coordonées du joueur dans un structure et renvoie la structure
 * 
 * 
 * \param keyboard pointeur sur la liste d'evenements
 * \param player pointeur sur le joueur appartenant a une structure
 * \return move retourne la structure du joueur
 */

/*
move move_player(SDL_Event * keyboard, move * player) {
    refresh_keys(keyboard, player);
    if (player -> arrow_down == 1) {
        player -> y -= 1;
        initialize_keys(player);
    }

    if (player -> arrow_left == 1) {
        player -> x -= 1;
        initialize_keys(player);
    }

    if (player -> arrow_right == 1) {
        player -> x += 1;
        initialize_keys(player);
    }

    if (player -> arrow_up == 1) {
        player -> y += 1;
        initialize_keys(player);
    }

    return *player;

}*/

/**
 * \brief Sert a avoir les informations des fleches (Appuyée ou non) pour le deplacement du joueur
 * 
 * \param keyboard pointeur sur la liste d'evenements
 * \param player pointeur sur le joueur appartenant a la structure move
 *
 */
/*
void refresh_keys(SDL_Event * keyboard, move * player) {

    while (SDL_PollEvent(keyboard)) {
        switch (keyboard -> type) {
        case SDL_KEYDOWN: 
            switch (keyboard -> key.keysym.sym) {
            case SDLK_UP:
                player -> arrow_up = 1;
                break;
            case SDLK_DOWN:
                player -> arrow_down = 1;
                break;
            case SDLK_LEFT:
                player -> arrow_left = 1;
                break;
            case SDLK_RIGHT:
                player -> arrow_right = 1;
                break;
            }
        }
    }

}
*/

/**
 * \brief Fonction servant a reset les informations concernant les fleches dans la strcuture joueur
 * 
 * \param player pointeur sur le joueur appartenant a la structure move
 */

void initialize_keys(move * player) {

    player -> arrow_down = 0;
    player -> arrow_left = 0;
    player -> arrow_right = 0;
    player -> arrow_up = 0;

}
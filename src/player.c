/**
 *\file player.c 
 * 
 *
 * \brief Module de gestion de deplacement du joueur
 * \author Guillaume
 */

#include <stdio.h>

#include <SDL2/SDL.h>

#include <player.h>


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
 * \brief modifie les coordonées du joueur dans un structure et renvoie la structure
 * 
 * 
 * \param keyboard pointeur sur la liste d'evenements
 * \param player pointeur sur le joueur appartenant a une structure
 * \return move retourne la structure du joueur
 */


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

}
/**
 * \brief Sert a avoir les informations des fleches (Appuyée ou non) pour le deplacement du joueur
 * 
 * \param keyboard pointeur sur la liste d'evenements
 * \param player pointeur sur le joueur appartenant a la structure move
 *
 */

void refresh_keys(SDL_Event * keyboard, move * player) {

    while (SDL_PollEvent(keyboard)) {
        switch (keyboard -> type) {
        case SDL_KEYDOWN: /** Si une touche est appuyée*/
            switch (keyboard -> key.keysym.sym) {
            case SDLK_UP:/** Fleche du haut*/
                player -> arrow_up = 1;
                break;
            case SDLK_DOWN:/** Fleche du bas*/
                player -> arrow_down = 1;
                break;
            case SDLK_LEFT:/** Fleche de gauche*/
                player -> arrow_left = 1;
                break;
            case SDLK_RIGHT:/** Fleche de droite*/
                player -> arrow_right = 1;
                break;
            }
        }
    }

}

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
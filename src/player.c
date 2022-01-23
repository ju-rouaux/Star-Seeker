/**
 *\file player.c 
 * 
 *
 * \brief Gestion des deplacements du joueur
 * \author Guillaume
 */

#include <stdio.h>

#include <SDL2/SDL.h>

#include <player.h>


move move_player(SDL_Event * keyboard, move * player) {
    refresh_keys(keyboard, player);
    if (player -> arrow_down == 1){
        player -> y -= 1;
        initialize_keys(player);
    }

    if (player -> arrow_left == 1){
        player -> x -= 1;
        initialize_keys(player);
    }

    if (player -> arrow_right == 1){
        player -> x += 1;
        initialize_keys(player);
    }

    if (player -> arrow_up == 1){
        player -> y += 1;
        initialize_keys(player);
    }

   printf("\nCoordonnées du joueur : x = %d, y = %d", player -> x, player -> y);

    return *player;

}

void refresh_keys(SDL_Event * keyboard, move * player) {

    while (SDL_PollEvent(keyboard)) {
        switch (keyboard->type) {
        case SDL_KEYDOWN:
            switch (keyboard->key.keysym.sym) {
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

void initialize_keys(move * player){

    player->arrow_down = 0;
    player->arrow_left = 0;
    player->arrow_right = 0;
    player->arrow_up = 0;

}
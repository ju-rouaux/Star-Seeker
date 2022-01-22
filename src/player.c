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
    refresh_keys( * keyboard, player);
    if (player -> arrow_down == 1)
        player -> y = player -> y + 10;

    if (player -> arrow_left == 1)
        player -> x = player -> x - 10;

    if (player -> arrow_right == 1)
        player -> x = player -> x + 10;

    if (player -> arrow_up == 1)
        player -> y = player -> y - 10;

    printf("\nCoordonnées du joueur : x = %d, y = %d", player -> x, player -> y);
    printf("\no");

    return *player;

}

void refresh_keys(SDL_Event keyboard, move * player) {

    while (SDL_PollEvent( & keyboard)) {
        switch (keyboard.type) {
        case SDL_KEYDOWN:
            switch (keyboard.key.keysym.sym) {
            case SDLK_UP:
                player -> arrow_up = 1;printf("upp");
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
            };
        case SDL_KEYUP:
            switch (keyboard.key.keysym.sym) {
            case SDLK_UP:
                player -> arrow_up = 0;
                printf("up-down");
                break;
            case SDLK_DOWN:
                player -> arrow_down = 0;
                break;
            case SDLK_LEFT:
                player -> arrow_left = 0;
                break;
            case SDLK_RIGHT:
                player -> arrow_right = 0;
                break;
            };
        };
    }

}
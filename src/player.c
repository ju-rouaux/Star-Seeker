#include <stdio.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <player.h>

/**
 *\file player.c 
 * 
 *
 * \brief Gestion des deplacements du joueur
 * \author Guillaume
 */

move move_player(move * player) {

        refresh_keys(player);
    if (player->arrow_down == 1)
        player->y = player->y + 10;

    if (player->arrow_left == 1)
        player->x = player->x - 10;

    if (player->arrow_right == 1)
        player->x = player->x + 10;

    if (player->arrow_up == 1)
        player->y = player->y - 10;
    
    printf("\nCoordonnées du joueur : x = %d, y = %d",player->x, player->y);
    
    return *player;

}

int refresh_keys(move * player) {
        SDL_Event arrows ;
        arrows.type = 0;
        arrows.key.keysym.sym = 0;

        switch (arrows.type) {
        case SDL_KEYDOWN:
            switch (arrows.key.keysym.sym) {
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
            case SDLK_ESCAPE:
                return 1;
                break;
            }

        }
        return 0;
}
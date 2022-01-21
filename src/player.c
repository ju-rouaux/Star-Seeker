#include <stdio.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <player.h>

/**
 * \brief Gestion des deplacements du joueur
 * 
 */

move move_player(move * player) {

    while(refresh_keys(&player) != 1){

    if (player->arrow_down == 1)
        player->y = player->y + 10;

    if (player->arrow_left == 1)
        player->x = player->x - 10;

    if (player->arrow_right == 1)
        player->x = player->x + 10;

    if (player->arrow_up == 1)
        player->y = player->y - 10;
    
    }

    return *player;

}

int refresh_keys(move * player) {
        SDL_Event arrows;

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
                return 1;break;
            }

        }
        return 0;
}
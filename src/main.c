#include <stdio.h>

#include <SDL2/SDL.h>

#include <window.h>

#include <player.h>

#include <event.h>

int main(int argc, char * argv[]) {
    SDL_Window * window = NULL;
    SDL_Renderer * renderer = NULL;
    SDL_Event event;
    move * player = malloc(sizeof(move));
    player -> x = 0;
    player -> y = 0;
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    creerFenetreEtRendu( & window, & renderer);

    while (handleEvents(event) != 1) {

        move_player( & event, player);
    }
    free(player);
    detruireFenetreEtRendu( & window, & renderer);
    SDL_Quit();
    return 0;

}
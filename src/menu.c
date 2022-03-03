#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <window.h>
#include <moteur.h>
#include <menu.h>

#define WINDOW_WIDTH 300
#define WINDOW_HEIGHT (WINDOW_WIDTH)

/*
- x, y: upper left corner.
- texture, rect: outputs.
*/
void get_text_and_rect(t_moteur * moteur, int x, int y, char *text,
        TTF_Font *font, SDL_Texture **texture, SDL_Rect *rect) {
    int text_width;
    int text_height;
    SDL_Surface *surface;
    SDL_Color textColor = {255, 255, 255, 0};

    surface = TTF_RenderText_Solid(font, text, textColor);
    *texture = SDL_CreateTextureFromSurface(moteur->renderer, surface);
    text_width = surface->w;
    text_height = surface->h;
    SDL_FreeSurface(surface);
    rect->x = x;
    rect->y = y;
    rect->w = text_width;
    rect->h = text_height;
}

int chargerMenu(t_moteur * moteur){
    SDL_Event event;
    SDL_Rect rect1, rect2;
    SDL_Texture *texture1, *texture2;
    int quit;


    TTF_Init();
    TTF_Font *font = TTF_OpenFont("/info/etu/l2info/s204416/Bureau/Star-Seeker/OpenSans-Regular.ttf", 24);
    if (font == NULL) {
        fprintf(stderr, "error: font not found\n");
        exit(EXIT_FAILURE);
    }
    get_text_and_rect(moteur, 0, 0, "hello", font, &texture1, &rect1);
    get_text_and_rect(moteur, 0, rect1.y + rect1.h, "world", font, &texture2, &rect2);

    quit = 0;
    while (!quit) {
        while (SDL_PollEvent(&event) == 1) {
            if (event.type == SDL_QUIT) {
                quit = 1;
            }
        }
        SDL_SetRenderDrawColor(moteur->renderer, 0, 0, 0, 0);
        SDL_RenderClear(moteur->renderer);

        /* Use TTF textures. */
        SDL_RenderCopy(moteur->renderer, texture1, NULL, &rect1);
        SDL_RenderCopy(moteur->renderer, texture2, NULL, &rect2);

        SDL_RenderPresent(moteur->renderer);
    }

  SDL_Delay(5000);
    /* Deinit TTF. */
    SDL_DestroyTexture(texture1);
    SDL_DestroyTexture(texture2);
    TTF_Quit();

    return 0;
}

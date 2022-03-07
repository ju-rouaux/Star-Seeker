#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <window.h>
#include <moteur.h>
#include <menu.h>


/*
- x, y: upper left corner.
- texture, rect: outputs.
*/
void get_text_and_rect(t_moteur * moteur, int x, int y, char *text,
        TTF_Font *font, SDL_Texture **texture, SDL_Rect *rect, int rect_y) {
    SDL_Surface *surface;
    SDL_Color textColor = {255, 255, 255, 0};
    surface = TTF_RenderText_Solid(font, text, textColor);
    *texture = SDL_CreateTextureFromSurface(moteur->renderer, surface);
    SDL_FreeSurface(surface);
    rect->x = 100;
    rect->y = rect_y;
    rect->w = moteur->echelle * 1.2;
    rect->h = moteur->echelle * 1.2;
    SDL_SetRenderDrawColor(moteur->renderer,187,255,75,255);
    SDL_RenderDrawRect(moteur->renderer,rect);
}

int chargerMenu(t_moteur * moteur){
    SDL_Rect nouvelle_partie,continuer,options,quitter;
    SDL_Texture *texture_nouvelle_partie,*texture_continuer,*texture_options,*texture_quitter;


    TTF_Init();
    TTF_Font *font = TTF_OpenFont("/info/etu/l2info/s204416/Bureau/Star-Seeker/OpenSans-Regular.ttf", 20);
    if (font == NULL) {
        fprintf(stderr, "error: font not found\n");
        exit(EXIT_FAILURE);
    }

    get_text_and_rect(moteur, 20, 50, "Nouvelle Partie", font, &texture_nouvelle_partie, &nouvelle_partie, moteur->window_height * 0.01);
    updateEchelle(moteur);
    get_text_and_rect(moteur, 20, 100, "Continuer", font, &texture_continuer, &continuer,moteur->window_height *0.25);
    updateEchelle(moteur);
    get_text_and_rect(moteur, 20, 200, "Options", font, &texture_options, &options, moteur->window_height *0.5);
    updateEchelle(moteur);
    get_text_and_rect(moteur, 20, 400, "Quitter", font, &texture_quitter, &quitter,moteur->window_height * 0.75);
    updateEchelle(moteur);
        /* Use TTF textures. */
        SDL_RenderCopy(moteur->renderer, texture_nouvelle_partie, NULL, &nouvelle_partie);
        updateEchelle(moteur);
        SDL_RenderCopy(moteur->renderer, texture_continuer, NULL, &continuer);
        updateEchelle(moteur);
        SDL_RenderCopy(moteur->renderer, texture_options, NULL, &options);
        updateEchelle(moteur);
        SDL_RenderCopy(moteur->renderer, texture_quitter, NULL, &quitter);
        updateEchelle(moteur);

        SDL_RenderPresent(moteur->renderer);
        updateEchelle(moteur);
    /* Deinit TTF. */
    SDL_DestroyTexture(texture_nouvelle_partie);
    SDL_DestroyTexture(texture_continuer);
    SDL_DestroyTexture(texture_options);
    SDL_DestroyTexture(texture_quitter);
    TTF_Quit();

    return 0;
}

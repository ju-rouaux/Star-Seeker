#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <window.h>
#include <moteur.h>

int chargerMenu(t_moteur * moteur){

    SDL_Rect menu;

    menu.h = 64;
    menu.w = 64;
    menu.x = 0;
    menu.y = 0;
  SDL_SetRenderDrawColor(moteur->renderer,51,21,242,SDL_ALPHA_OPAQUE);
  SDL_RenderFillRect(moteur->renderer,&menu);
  SDL_RenderPresent(moteur->renderer);
    return 0;

}


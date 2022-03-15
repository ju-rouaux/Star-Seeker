#ifndef _JEU_MENU_PLANETES_
#define _JEU_MENU_PLANETES_

#include <SDL2/SDL.h>

#include <SDL2/SDL_image.h>

#include <SDL2/SDL_ttf.h>

#include <moteur.h>



typedef struct s_planetes {
    SDL_Texture * texture;
    SDL_Rect rect;
}t_planetes;


int chargerMenu_planetes(t_moteur * moteur, int nb_boutons, int r, int g, int b);


#endif //_JEU_MENU_PLANETES_
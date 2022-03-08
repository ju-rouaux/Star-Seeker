#ifndef _JEU_MENU_
#define _JEU_MENU_

#include <moteur.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

typedef struct s_menu{
    SDL_Texture * texture;
    SDL_Rect rect;
}t_menu;


int chargerMenu(t_moteur * moteur);




#endif //_JEU_MENU_
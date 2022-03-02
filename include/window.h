/**
 * \file window.h
 * 
 * \brief Module de création de la fenêtre du jeu et son rendu
 * 
 * \author Julien Rouaux
*/

#ifndef _JEU_WINDOW_
#define _JEU_WINDOW_

#include <SDL2/SDL.h>

int creerFenetreEtRendu(SDL_Window ** window, SDL_Renderer ** renderer);
void detruireFenetreEtRendu(SDL_Window ** window, SDL_Renderer ** renderer);

#endif //_JEU_WINDOW_
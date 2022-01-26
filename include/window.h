#ifndef _JEU_WINDOW_
#define _JEU_WINDOW_

#include <SDL2/SDL.h>

#define NB_FPS 60

int creerFenetreEtRendu(SDL_Window ** window, SDL_Renderer ** renderer);
void detruireFenetreEtRendu(SDL_Window ** window, SDL_Renderer ** renderer);

#endif //_JEU_WINDOW_
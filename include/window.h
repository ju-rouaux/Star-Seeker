#ifndef _JEU_WINDOW_
#define _JEU_WINDOW_

#include <SDL2/SDL.h>

#define NB_FPS 60

//Compteur du nombre de frames générées depuis l'exécution du programme
//(si 60 FPS, on peut aller à un peu plus de 414 jours d'exécution avant bug)
int COMPTEUR_DE_FRAMES = 0;

int creerFenetreEtRendu(SDL_Window ** window, SDL_Renderer ** renderer);
void detruireFenetreEtRendu(SDL_Window ** window, SDL_Renderer ** renderer);

#endif //_JEU_WINDOW_
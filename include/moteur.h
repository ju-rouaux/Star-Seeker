#include <SDL2/SDL.h>
#include <textures.h>
//include vecteur.h

//Structure contenant toutes les données utiles au moteur de jeu
typedef struct
{
    SDL_Window * window;
    SDL_Renderer * renderer;
    t_textures * textures;
} t_moteur;

t_moteur * chargerMoteur();
void detruireMoteur(t_moteur ** moteur);
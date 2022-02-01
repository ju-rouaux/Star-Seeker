#ifndef _JEU_MOTEUR_
#define _JEU_MOTEUR_

#include <SDL2/SDL.h>
#include <textures.h>
//include vecteur.h

#define NB_FPS 60
#define TEMPS_POUR_CHAQUE_SECONDE (1000/NB_FPS)

//Structure contenant toutes les données utiles au moteur de jeu
/**
 * \struct t_moteur
 * \brief Objet contenant les données nécéssaires au rendu du jeu
 */
typedef struct
{
    SDL_Window * window;
    SDL_Renderer * renderer;
    t_textures * textures;
} t_moteur;

t_moteur * chargerMoteur();
void detruireMoteur(t_moteur ** moteur);

#endif // _JEU_MOTEUR_
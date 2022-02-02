#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <moteur.h>
#include <camera.h>
#include <rendu_joueur.h>
#include <joueur.h>

/**
 * \brief Dessine le joueur à ses coordonnées
 * 
 */
int dessinerJoueur(t_moteur * moteur, t_joueur * joueur, t_camera * camera)
{
    SDL_Rect destination;

    destination.h = camera->echelle * PROPORTION_JOUEUR;
    destination.w = camera->echelle * PROPORTION_JOUEUR;

    destination.x = joueur->position->x - camera->x - destination.w / 2;
    destination.y = joueur->position->y - camera->y - 3*destination.h/ 4;

    return SDL_RenderCopy(moteur->renderer, moteur->textures->player, NULL, &destination);
}


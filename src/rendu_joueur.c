/**
 * \file
 * \brief Module de rendu du joueur
 * 
 * \author Julien Rouaux
 */

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
 * \param moteur Structure moteur du jeu
 * \param joueur Structure du joueur actuel
 * \param camera Structure de la caméra actuelle
 * 
 * \return 0 si succès, sinon une valeur négative (SDL_Error() pour connaitre l'erreur)
 */
int dessinerJoueur(t_moteur * moteur, t_joueur * joueur, t_camera * camera)
{
    SDL_Rect destination;

    destination.h = camera->echelle * PROPORTION_JOUEUR;
    destination.w = camera->echelle * PROPORTION_JOUEUR;
    
    destination.x = joueur->position->x*camera->echelle - camera->x - destination.w / 2;
    destination.y = joueur->position->y*camera->echelle - camera->y - 3*destination.h/ 4;

    return SDL_RenderCopy(moteur->renderer, moteur->textures->player, NULL, &destination);
}


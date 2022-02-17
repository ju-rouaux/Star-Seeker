/**
 * \file camera.h
 * 
 * \brief Module de calcul de position de caméra pour savoir où
 * dessiner les éléments sur la fenêtre.
 * 
 * \author Julien Rouaux
 */

#ifndef _JEU_CAMERA_
#define _JEU_CAMERA_

#include <SDL2/SDL.h>

typedef struct s_moteur t_moteur; //Indiquer au compilateur que le type existe

/**
 * \struct t_camera
 * \brief Modélise une caméra virtuelle qu'il suffit de bouger pour déplacer tout l'affichage des
 * éléments sur la fenêtre.
 */
typedef struct
{
    float x; /**< Position en x du centre de la caméra par rapport au niveau */
    float y; /**< Position en y du centre de la caméra par rapport au niveau */
    float futur_x; /**< Stockage d'une future position de la caméra en x (pour l'animation de transition) */
    float futur_y; /**< Stockage d'une future position de la caméra en y (pour l'animation de transition) */
} t_camera;


t_camera * creerCamera(float x, float y);
void detruireCamera(t_camera ** camera);

void updateCamera(t_moteur * moteur, int largeur, int hauteur, int orig_x, int orig_y, float j_x, float j_y);
void updateFutureCamera(t_moteur * moteur, int largeur, int hauteur, int orig_x, int orig_y, float j_x, float j_y);

#endif //_JEU_CAMERA_
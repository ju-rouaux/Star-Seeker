#ifndef _JEU_CAMERA_
#define _JEU_CAMERA_

#include <SDL2/SDL.h>
#include <niveau.h>

typedef struct
{
    int x; /**< Position en x du centre de la caméra par rapport au niveau */
    int y; /**< Position en y du centre de la caméra par rapport au niveau */
    int futur_x; /**< Stockage d'une future position de la caméra en x pour la gestion d'animation */
    int futur_y; /**< Stockage d'une future position de la caméra en y pour la gestion d'animation */

    int echelle; /**< Echelle du jeu, c'est à dire la taille des éléments */

    int window_width; /**< Largeur de la fenêtre */
    int window_height; /**< Hauteur de la fenêtre */
} t_camera;


void updateScale(SDL_Window * window, t_camera * camera);

t_camera * creerCamera(SDL_Window * window, int x, int y);
void detruireCamera(t_camera ** camera);

void updateCamera(t_camera * camera, const t_dimensions_salle * dimensions, int orig_x, int orig_y, float j_x, float j_y);
void updateFutureCamera(t_camera * camera, const t_dimensions_salle * dimensions, int orig_x, int orig_y, float j_x, float j_y);

//int transitionCamera(t_camera * camera, float duree, int ** avancer_x, int ** avancer_y);


#endif //_JEU_CAMERA_
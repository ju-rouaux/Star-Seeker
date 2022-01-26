#ifndef _JEU_CAMERA_
#define _JEU_CAMERA_

#define NB_TILE_LARGEUR 15 //Représente la surface au sol
#define NB_TILE_HAUTEUR 9

typedef struct
{
    int x;
    int y;
    int futur_x;
    int futur_y;
    int echelle;
} t_camera;

void updateScale(SDL_Window * window, t_camera * camera);
t_camera * creerCamera(int x, int y);
t_camera * creerCamera(int x, int y);
void calculerPosCamera(int * x, int * y, const t_dimensions_salle * dimensions, int orig_x, int orig_y, int j_x, int j_y, int echelle);
void updateCamera(t_camera * camera, const t_dimensions_salle * dimensions, int orig_x, int orig_y, int j_x, int j_y);
void updateFutureCamera(t_camera * camera, const t_dimensions_salle * dimensions, int orig_x, int orig_y, int j_x, int j_y);
int transitionCamera(t_camera * camera, float duree, int ** avancer_x, int ** avancer_y);

#endif //_JEU_CAMERA_
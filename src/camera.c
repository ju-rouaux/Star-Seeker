/**
 * \file
 * 
 * 
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <camera.h>
#include <niveau.h>

/**
 * \brief Calcule la taille en pixel d'un bloc selon la taille de l'écran et 
 * actualise le champ echelle de la caméra selon la valeur calculée.
 * 
 * \param window La fenêtre d'affichage
 * \param camera La caméra à actualiser
 */
void updateScale(SDL_Window * window, t_camera * camera)
{
    int l = 400;
    int h = 170;

    SDL_GetWindowSize(window, &l, &h);
    
    if(h < l) //Si la hauteur est petite, on se base sur cette dimension
        camera->echelle = h / (NB_TILE_HAUTEUR + 1); //On laisse un demi bloc de vide avec les bordures
    
    else //Si la largeur est petite, on se base sur cette dimension
        camera->echelle = l / (NB_TILE_LARGEUR + 1);
}

/**
 * \brief Nb Echelle à 0, penser à l'actualiser avant utilisation
 * 
 */
t_camera * creerCamera(int x, int y)
{
    t_camera * camera = malloc(sizeof(t_camera));
    if(camera == NULL)
    {
        printf("Impossible d'allouer l'espace pour la caméra\n");
        return NULL;
    }

    camera->x = x;
    camera->y = y;
    camera->echelle = 0;

    return camera;
}

void detruireCamera(t_camera ** camera)
{
    if(*camera != NULL)
        free(*camera);
    *camera = NULL;
}

/**
 * \brief Place la caméra au bon endroit selon la configuration de la salle et 
 * de la position du joueur.
 * 
 * \param camera Camera à actualiser
 * \param dimensions Nombre de sous-salles contenues dans la salle
 * \param orig_x Coordonnées d'origine de la salle en x (à l'échelle)
 * \param orig_y Coordonnées d'origine de la salle en y (à l'échelle)
 * \param j_x Position en x du joueur relative au niveau
 * \param j_y Position en y du joueur relative au niveau
 */
void updateCamera(t_camera * camera, t_dimensions_salle * dimensions, int orig_x, int orig_y, int j_x, int j_y)
{
    int quart; //Largeur ou longueur du quart d'une salle

    if(dimensions == NULL || (dimensions->largeur == 1))
        camera->x = (orig_x + camera->echelle) / 2;
    else
    {
        quart = (orig_x + dimensions->largeur*camera->echelle) / 4;
        if(j_x < quart)
            camera->x = quart;
        else if(j_x > 3*quart)
            camera->x = 3*quart;
        else
            camera->x = j_x;
    }

    if(dimensions == NULL || (dimensions->hauteur == 1))
        camera->y = (orig_y + camera->echelle) / 2;
    else
    {
        quart = (orig_y + dimensions->hauteur*camera->echelle) / 4;
        if(j_y < quart)
            camera->y = quart;
        else if(j_y > 3*quart)
            camera->y = 3*quart;
        else
            camera->x = j_x;
    }
}

/**
 * 
 * 
 */
void calculerPosCamera(const t_camera * camera, const t_dimensions_salle * dimensions, int j_x, int j_y, int * x, int * y)
{
    
}

void transitionCamera(t_camera * camera)
{
    if
}
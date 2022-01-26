/**
 * \file
 * EN COURS D'ECRITURE
 * C'EST LE BORDEL ICI
 * 
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <camera.h>
#include <niveau.h>
#include <window.h>

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
 * \brief Calule la position de la caméra au bon endroit selon la configuration de la salle et 
 * de la position du joueur.
 * 
 * \param x Retour de la position en x
 * \param y Retour de la position en y
 * \param dimensions Nombre de sous-salles contenues dans la salle
 * \param orig_x Coordonnées d'origine de la salle en x (à l'échelle)
 * \param orig_y Coordonnées d'origine de la salle en y (à l'échelle)
 * \param j_x Position en x du joueur relative au niveau
 * \param j_y Position en y du joueur relative au niveau
 * \param echelle Echelle du niveau
 */
void calculerPosCamera(int * x, int * y, const t_dimensions_salle * dimensions, int orig_x, int orig_y, int j_x, int j_y, int echelle)
{
    int quart; //Largeur ou longueur du quart d'une salle

    if(dimensions == NULL || (dimensions->largeur == 1))
        *x = (orig_x + echelle) / 2;
    else
    {
        quart = (orig_x + dimensions->largeur*echelle) / 4;
        if(j_x < quart)
            *x = quart;
        else if(j_x > 3*quart)
            *x = 3*quart;
        else
            *x = j_x;
    }

    if(dimensions == NULL || (dimensions->hauteur == 1))
        *y = (orig_y + echelle) / 2;
    else
    {
        quart = (orig_y + dimensions->hauteur*echelle) / 4;
        if(j_y < quart)
            *y = quart;
        else if(j_y > 3*quart)
            *y = 3*quart;
        else
            *x = j_x;
    }
    
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
void updateCamera(t_camera * camera, const t_dimensions_salle * dimensions, int orig_x, int orig_y, int j_x, int j_y)
{
    calculerPosCamera(&camera->x, &camera->y, dimensions, orig_x, orig_y, j_x, j_y, camera->echelle);
}

/**
 * \brief Actualise la future position de la caméra selon la configuration de la future salle et 
 * de la position du joueur.
 * 
 * \param camera Camera à actualiser
 * \param dimensions Nombre de sous-salles contenues dans la salle
 * \param orig_x Coordonnées d'origine de la salle en x (à l'échelle)
 * \param orig_y Coordonnées d'origine de la salle en y (à l'échelle)
 * \param j_x Position en x du joueur relative au niveau
 * \param j_y Position en y du joueur relative au niveau
 */
void updateFutureCamera(t_camera * camera, const t_dimensions_salle * dimensions, int orig_x, int orig_y, int j_x, int j_y)
{
    calculerPosCamera(&camera->futur_x, &camera->futur_y, dimensions, orig_x, orig_y, j_x, j_y, camera->echelle);
}

//Vrai tant que l'animation est en cours
//duree en secondes
//Cette fonction doit être améliorée pour calculer sa vitesse elle même
//Si avancer NULL, calculer combien avancer et informer le calcul. sinon avancer de ce qui est indiqué
int transitionCamera(t_camera * camera, float duree, int ** avancer_x, int ** avancer_y)
{
    if(avancer_x == NULL)
    {
        *avancer_x = malloc(sizeof(int));
        **avancer_x = (camera->futur_x - camera->x) / (NB_FPS * duree); //Distance / nb de FPS alloué à la durée
    }
    if(avancer_y == NULL)
    {
        *avancer_y = malloc(sizeof(int));
        **avancer_y = (camera->futur_y - camera->y) / (NB_FPS * duree); //Distance / nb de FPS alloué à la durée
    }

    camera->x += **avancer_x;
    camera->y += **avancer_y;

    //Si on est suffisamment près de la destination, y aller directement.
    //On admet que si un des axes est arrivé, l'autre l'est aussi
    if(abs(camera->futur_x - camera->x) < abs(**avancer_x) || abs(camera->futur_y - camera->y) < abs(**avancer_y))
    {
        camera->x = camera->futur_x;
        camera->y = camera->futur_y;
        camera->futur_x = 0;
        camera->futur_y = 0;
        free(*avancer_x);
        free(*avancer_y);
        avancer_x = NULL;
        avancer_y = NULL;
        return 0;
    }

    return 1;
}
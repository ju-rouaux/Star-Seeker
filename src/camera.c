/**
 * \file
 * \brief Module de calcul de position de caméra pour savoir où
 * dessiner les éléments sur la fenêtre
 * 
 * \author Julien Rouaux
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
    int l = 1280;
    int h = 720;

    SDL_GetWindowSize(window, &l, &h);

    camera->window_height = h;
    camera->window_width = l;
    
    if(h < l) //Si la hauteur est petite, on se base sur cette dimension
        camera->echelle = h / (NB_TILE_HAUTEUR + 3); //On laisse un bloc et demi de vide avec les bordures
    
    else //Si la largeur est petite, on se base sur cette dimension
        camera->echelle = l / (NB_TILE_LARGEUR + 3);
}


/**
 * \brief Alloue la mémoire pour une caméra, et appelle updateScale automatiquement.
 * 
 * \param window SDL_Window du jeu
 * \param x Position de la caméra en x
 * \param y Position de la caméra en y
 * 
 * \return Le pointeur de la caméra, NULL si échec
 */
t_camera * creerCamera(SDL_Window * window, int x, int y)
{
    t_camera * camera = malloc(sizeof(t_camera));
    if(camera == NULL)
    {
        printf("Impossible d'allouer l'espace pour la caméra\n");
        return NULL;
    }

    camera->x = x;
    camera->y = y;
    camera->futur_x = x;
    camera->futur_y = y;

    updateScale(window, camera);

    return camera;
}


/**
 * \brief Libère la mémoire allouée à une caméra et mets son pointeur à NULL.
 * 
 * \param camera L'adresse du pointeur de la caméra
 */
void detruireCamera(t_camera ** camera)
{
    if(*camera != NULL)
        free(*camera);

    *camera = NULL;
}

/**
 * \brief Calule la position de la caméra de telle sorte à ce que son origine soit au centre de la salle ou sur le joueur
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
static void calculerPosCamera(int * x, int * y, const t_dimensions_salle * dimensions, int orig_x, int orig_y, int j_x, int j_y, int echelle)
{
    int demi; //Largeur ou longueur d'une demi salle

    if(dimensions == NULL || (dimensions->largeur == 1))
    {
        *x = orig_x + (echelle*NB_TILE_LARGEUR) / 2;
    }
    else
    {
        demi = echelle * NB_TILE_LARGEUR / 2;
        if(j_x < orig_x + demi)
            *x = orig_x + demi;
        else if(j_x > orig_x + dimensions->largeur*echelle*NB_TILE_LARGEUR - demi)
            *x = orig_x + dimensions->largeur*echelle*NB_TILE_LARGEUR - demi;
        else
            *x = j_x;
    }

    if(dimensions == NULL || (dimensions->hauteur == 1))
        *y = orig_y + (echelle*NB_TILE_HAUTEUR) / 2;
    else
    {
        demi = echelle * NB_TILE_HAUTEUR / 2;
        if(j_y < orig_y + demi)
            *y = orig_y + demi;
        else if(j_y > orig_y + dimensions->hauteur*echelle*NB_TILE_HAUTEUR - demi)
            *y = orig_y + dimensions->hauteur*echelle*NB_TILE_HAUTEUR - demi;
        else
            *y = j_y;
    }
}


/**
 * \brief Place la caméra au bon endroit selon la configuration de la salle et 
 * de la position du joueur. Le sujet de la caméra sera placé au centre.
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
    
    //Maintenant que l'origine de la caméra est placée au bon endroit,
    //faire se déplacer l'origine de telle sorte à ce que le centre de la fenetre
    //accueille l'origine de la caméra.
    camera->x = camera->x - camera->window_width / 2;
    camera->y = camera->y - camera->window_height / 2;
}


/**
 * \brief Actualise la future position de la caméra selon la configuration de la future salle et 
 * de la position du joueur. Le sujet de la caméra sera placé au centre.
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
    
    //Maintenant que l'origine de la caméra est placée au bon endroit,
    //faire se déplacer l'origine de telle sorte à ce que le centre de la fenetre
    //accueille l'origine de la caméra.
    camera->futur_x = camera->futur_x - camera->window_width / 2;
    camera->futur_y = camera->futur_y - camera->window_height / 2;
}


//Vrai tant que l'animation est en cours
//duree en secondes
//Cette fonction doit être améliorée pour calculer sa vitesse elle même
//Si avancer NULL, calculer combien avancer et informer le calcul. sinon avancer de ce qui est indiqué
//Cette fonction n'est pas encore prête
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
/*
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
*/
    return 1;
}
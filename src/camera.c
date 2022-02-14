/**
 * \file camera.c
 * 
 * \brief Module de calcul de position de caméra pour savoir où
 * dessiner les éléments sur la fenêtre.
 * 
 * \author Julien Rouaux
 */


#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <moteur.h>
#include <camera.h>


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
t_camera * creerCamera(SDL_Window * window, float x, float y)
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
 * \param largeur Nombre de sous-salles contenues dans la salle en largeur
 * \param hauteur Nombre de sous-salles contenues dans la salle en hauteur
 * \param orig_x Coordonnées d'origine de la salle en x
 * \param orig_y Coordonnées d'origine de la salle en y
 * \param j_x Position en x du joueur relative au niveau
 * \param j_y Position en y du joueur relative au niveau
 * \param echelle Echelle du niveau
 */
static void calculerPosCamera(float * x, float * y, int largeur, int hauteur, int orig_x, int orig_y, float j_x, float j_y, float echelle)
{
    float demi; //Largeur ou longueur d'une demi salle

    orig_x *= NB_TILE_LARGEUR;
    orig_y *= NB_TILE_HAUTEUR;

    if(largeur == 1)
    {
        *x = orig_x + NB_TILE_LARGEUR / 2.0;
    }
    else
    {
        demi = NB_TILE_LARGEUR / 2.0;
        if(j_x < orig_x + demi)
            *x = orig_x + demi;
        else if(j_x > orig_x + largeur*NB_TILE_LARGEUR - demi)
            *x = orig_x + largeur*NB_TILE_LARGEUR - demi;
        else
            *x = j_x;
    }

    if(hauteur == 1)
        *y = orig_y + NB_TILE_HAUTEUR / 2.0;
    else
    {
        demi = NB_TILE_HAUTEUR / 2.0;
        if(j_y < orig_y + demi)
            *y = orig_y + demi;
        else if(j_y > orig_y + hauteur*NB_TILE_HAUTEUR - demi)
            *y = orig_y + hauteur*NB_TILE_HAUTEUR - demi;
        else
            *y = j_y;
    }
}


/**
 * \brief Place la caméra au bon endroit selon la configuration de la salle et 
 * de la position du joueur. Le sujet de la caméra sera placé au centre.
 * 
 * \param camera Camera à actualiser
 * \param largeur Nombre de sous-salles contenues dans la salle en largeur
 * \param hauteur Nombre de sous-salles contenues dans la salle en hauteur
 * \param orig_x Coordonnées d'origine de la salle en x
 * \param orig_y Coordonnées d'origine de la salle en y
 * \param j_x Position en x du joueur relative au niveau
 * \param j_y Position en y du joueur relative au niveau
 */
void updateCamera(t_camera * camera, int largeur, int hauteur, int orig_x, int orig_y, float j_x, float j_y)
{
    calculerPosCamera(&camera->x, &camera->y, largeur, hauteur, orig_x, orig_y, j_x, j_y, camera->echelle);
    
    //Maintenant que l'origine de la caméra est placée au bon endroit,
    //faire se déplacer l'origine de telle sorte à ce que le centre de la fenetre
    //accueille l'origine de la caméra.
    camera->x = camera->x - (float)camera->window_width / 2 / camera->echelle;
    camera->y = camera->y - (float)camera->window_height / 2 / camera->echelle;
}


/**
 * \brief Actualise la future position de la caméra selon la configuration de la future salle et 
 * de la position du joueur. Le sujet de la caméra sera placé au centre.
 * 
 * \param camera Camera à actualiser
 * \param largeur Nombre de sous-salles contenues dans la salle en largeur
 * \param hauteur Nombre de sous-salles contenues dans la salle en hauteur
 * \param orig_x Coordonnées d'origine de la salle en x
 * \param orig_y Coordonnées d'origine de la salle en y
 * \param j_x Position en x du joueur relative au niveau
 * \param j_y Position en y du joueur relative au niveau
 */
void updateFutureCamera(t_camera * camera, int largeur, int hauteur, int orig_x, int orig_y, float j_x, float j_y)
{
    calculerPosCamera(&camera->futur_x, &camera->futur_y, largeur, hauteur, orig_x, orig_y, j_x, j_y, camera->echelle);
    
    //Maintenant que l'origine de la caméra est placée au bon endroit,
    //faire se déplacer l'origine de telle sorte à ce que le centre de la fenetre
    //accueille l'origine de la caméra.
    camera->futur_x = camera->futur_x - (float)camera->window_width / 2 / camera->echelle;
    camera->futur_y = camera->futur_y - (float)camera->window_height / 2 / camera->echelle;
}


/*

PAS UTILISABLE, C'EST L'EBAUCHE D'UNE IDEE

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
}*/
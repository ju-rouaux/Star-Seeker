/**
 * \file test_position_camera.c
 * 
 * \brief Script de test de la fonction de calcul de la position de la caméra.
 * 
 * La fonction est tirée de camera.c
 * 
 * \author Julien Rouaux
 */


//gcc test/test_position_camera.c -o test_position_camera


#include <stdio.h>

#define NB_TILE_LARGEUR 13
#define NB_TILE_HAUTEUR 7


/**
 * \brief Calule la position de la caméra de telle sorte à ce que son origine soit au centre de la salle ou sur le joueur.
 * 
 * \param x Retour de la position en x
 * \param y Retour de la position en y
 * \param largeur Nombre de sous-salles contenues dans la salle en largeur
 * \param hauteur Nombre de sous-salles contenues dans la salle en hauteur
 * \param orig_x Coordonnées d'origine de la salle en x
 * \param orig_y Coordonnées d'origine de la salle en y
 * \param j_x Position en x du joueur
 * \param j_y Position en y du joueur
 */
static void calculerPosCamera(float * x, float * y, int largeur, int hauteur, int orig_x, int orig_y, float j_x, float j_y)
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



int main(void)
{
    int largeur, hauteur; //Dimensions d'une salle du jeu
    int orig_x = 0, orig_y = 0; //Position d'une salle du jeu
    float j_x, j_y; //Position du joueur

    float x, y; //Coordonnées de la caméra attendues


    printf("Test lorsque joueur au bord d'une salle, à gauche.\n");
    largeur = 2;
    hauteur = 1;
    calculerPosCamera(&x, &y, largeur, hauteur, orig_x, orig_y, 1, 1);
    if(x == NB_TILE_LARGEUR/2.0 && y == NB_TILE_HAUTEUR/2.0)
        printf("--> Test OK\n\n");


    printf("Test lorsque joueur au bord d'une salle, à droite.\n");
    largeur = 2;
    hauteur = 1;
    calculerPosCamera(&x, &y, largeur, hauteur, orig_x, orig_y, (NB_TILE_LARGEUR*2) - 1, 1);
    if(x == NB_TILE_LARGEUR + NB_TILE_LARGEUR/2.0 && y == NB_TILE_HAUTEUR/2.0)
        printf("--> Test OK\n\n");


    printf("Test lorsque joueur au bord d'une salle, en haut.\n");
    largeur = 1;
    hauteur = 2;
    calculerPosCamera(&x, &y, largeur, hauteur, orig_x, orig_y, 1, 1);
    if(x == NB_TILE_LARGEUR/2.0 && y == NB_TILE_HAUTEUR/2.0)
        printf("--> Test OK\n\n");


    printf("Test lorsque joueur au bord d'une salle, en bas.\n");
    largeur = 1;
    hauteur = 2;
    calculerPosCamera(&x, &y, largeur, hauteur, orig_x, orig_y, 1, (NB_TILE_HAUTEUR*2) - 1);
    if(x == NB_TILE_LARGEUR/2.0 && y == NB_TILE_HAUTEUR + NB_TILE_HAUTEUR/2.0)
        printf("--> Test OK\n\n");


    printf("Test lorsque joueur au centre d'une salle.\n");
    largeur = 2;
    hauteur = 2;
    calculerPosCamera(&x, &y, largeur, hauteur, orig_x, orig_y, NB_TILE_LARGEUR, NB_TILE_HAUTEUR);
    if(x == NB_TILE_LARGEUR && y == NB_TILE_HAUTEUR) //j_x et j_y
        printf("--> Test OK\n\n");


    return 0;
}
#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NOMBRE_DE_PORTES 4

typedef struct
{
    int i; /**< Coordonnée en hauteur, de la salle d'origine dans la matrice niveau */
    int j; /**< Coordonnée en largeur, de la salle d'origine dans la matrice niveau */

    int largeur; /**< Largeur de la salle */
    int hauteur; /**< Hauteur de la salle */

    int nombre; /**< Nombre de sous-salles (utile pour la libération de la mémoire)*/
} t_dimensions_salle;


typedef struct s_salle
{
    int complete; /**< Booléen, vrai si la salle est complétée (plus de monstres) */

    struct s_salle * portes[NOMBRE_DE_PORTES]; /**< Salles reliées à notre salle */
    int id_salle; /**< Manière d'identifier si plusieurs salles forment une même salle */
    t_dimensions_salle * dimensions; /**< Informations sur le groupe de salle de notre salle */

    //t_obstacle ** (matrice d'obstacles)
} t_salle;


typedef struct
{
    t_salle ** salles;
    int h; /**< Hauteur du niveau (dimensions de la matrice en i) */
    int l; /**< Largeur du niveau (dimensions de la matrice en j) */

    t_salle * salle_chargee; /**<  Salle ou sous salle où se situe le joueur */
    int i_charge;
    int j_charge;
} t_niveau;

t_salle * read_file_struct_salle(char * filename);
t_salle * write_file_struct_salle(char * filename);
/**
 * \file niveau.h
 * \brief Module de chargement d'un niveau en structure interprétable pour le jeu.
 * 
 * \author Julien Rouaux
 */


#ifndef _JEU_NIVEAU_
#define _JEU_NIVEAU_

#include <stdio.h> //type FILE
#include <moteur.h>
#include <entite.h>


/**
 * \enum e_porte
 * \brief Position d'une porte dans une salle.
*/
typedef enum
{
    UP, RIGHT, DOWN, LEFT
} e_porte;


/**
 * \struct t_dimensions_salle
 * \brief Informations sur le nombre de sous-salles formant la salle.
 * 
 * La salle d'origine désigne la salle la plus en haut à gauche du groupe.
 */
typedef struct
{
    int i; /**< Coordonnée en hauteur, de la salle d'origine dans la matrice niveau */
    int j; /**< Coordonnée en largeur, de la salle d'origine dans la matrice niveau */

    int largeur; /**< Largeur de la salle */
    int hauteur; /**< Hauteur de la salle */

    int nombre; /**< Nombre de sous-salles (utile pour la libération de la mémoire)*/
} t_dimensions_salle;


/**
 * \struct t_salle
 * \brief Structure représentant une salle et les salles qui lui sont liées.
 * 
 * Une salle est un rectangle, mais peut être associée à d'autres salles pour former des 
 * salles aux formes plus complexes. Plusieurs sous-salles formant une même salle complexe 
 * portent le même id_salle et pointent sur la même structure dimensions.
*/
typedef struct s_salle
{
    int complete; /**< Booléen, vrai si la salle est complétée (plus de monstres) */

    struct s_salle * portes[NOMBRE_DE_PORTES]; /**< Salles reliées à notre salle */
    int id_salle; /**< Manière d'identifier si plusieurs salles forment une même salle */
    
    t_dimensions_salle * dimensions; /**< Informations sur le groupe de salle de notre salle */

    t_entite * ennemis[NB_TILE_HAUTEUR][NB_TILE_LARGEUR]; /**< Matrice des entités (monstres) qui existent dans la salle */
    
    //t_obstacle ** (matrice d'obstacles)
} t_salle;


/**
 * \struct t_niveau
 * \brief Structure représentant une matrice de salles, c'est à dire un niveau.
*/
typedef struct
{
    t_salle ** salles; 
    int h; /**< Hauteur du niveau (dimensions de la matrice en i) */
    int l; /**< Largeur du niveau (dimensions de la matrice en j) */

    t_salle * salle_chargee; /**<  Salle ou sous salle où se situe le joueur */
    int i_charge;
    int j_charge;
} t_niveau;


t_niveau * chargerNiveau(FILE * fichier, int * r, int * g, int * b);
void detruireNiveau(t_niveau ** niveau);
int lancerNiveau(FILE * fichier, t_moteur * moteur, t_niveau ** retour_niveau);
void arreterNiveau(t_niveau ** niveau);
void updateNiveau(t_niveau * niveau,float j_x, float j_y, int echelle);


#endif //_JEU_NIVEAU_
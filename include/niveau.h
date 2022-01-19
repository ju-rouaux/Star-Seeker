/**
 * \struct t_obstacle
 * \brief Structure représentant une salle
*/

#ifndef _JEU_NIVEAU_
#define _JEU_NIVEAU_

/*
    Memo structure de salle

    Une salle contient un identifiant et les 4 salles vers
    lesquelles elle dirige. Une porte NULL n'est pas affichée.

    Deux salles avec le même identifiant génèrent une unique salle, elles sont
    reliées entre elles mais la comparaison de leur identifiant permet d'en faire qu'une.

    Pour lier les salles, on regarde toute la matrice. Si une salle du
    dessus ou d'à gauche est non nulle, on relie les deux salles.
*/


#define NOMBRE_DE_PORTES 4 //D'une salle, une par coté

/**
 * \enum e_porte
 * \brief Position d'une porte
*/
typedef enum {
    UP, RIGHT, DOWN, LEFT
} e_porte;


/**
 * \struct t_salle
 * \brief Structure représentant une salle et ses liaisons
*/
typedef struct s_salle{
    int complete; /** Booléen, vrai si la salle est complétée (plus de monstres) */
    struct s_salle * portes[NOMBRE_DE_PORTES]; /** Salles auxquelles sont reliées notre salle */
    int id_salle; /** Manière d'identifier si plusieurs salles forment une même salle */
    //t_monstre ** (liste de monstres)
    //t_obstacle ** (liste d'obstacles)
} t_salle;


/**
 * \struct t_niveau
 * \brief Structure représentant une matrice de salles
*/
typedef struct {
    t_salle ** salles; 
    int h; /** Largeur du niveau */
    int l; /** Hauteur du niveau */
} t_niveau;


t_niveau * chargerNiveau(FILE * fichier);
void detruireNiveau(t_niveau ** niveau);

#endif
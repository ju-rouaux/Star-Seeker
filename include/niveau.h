/**
 * \struct t_obstacle
 * \brief Structure représentant une salle
*/

/*

    Memo structure de salle

    Une salle contient un identifiant et les 4 salles vers
    lesquelles elle dirige. Une porte NULL n'est pas affichée.

    Deux salles avec le même identifiant génèrent une unique salle, elles ne sont justement
    pas reliées entre elles (pointeur à NULL).

    Pour lier les salles, on regarde toute la matrice et si l'identifiant de la salle du
    dessus ou d'à gauche, est identique on relie les salles.
*/

#define NOMBRE_DE_PORTES 4 //Taille maximale d'un groupe de salle (à definir)

typedef enum {
    UP, RIGHT, DOWN, LEFT
} e_porte;

typedef struct s_salle{
    int complete; /** Booléen, vrai si la salle est complétée (plus de monstres) */
    struct s_salle * portes[NOMBRE_DE_PORTES]; /** Ensemble de salles formant une unique salle (tableau de pointeurs sur salle) */
    int id_salle;
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

//Charge à partir d'un fichier le niveau vers t_niveau;

t_niveau * chargerNiveau(const FILE * fichier);
void detruireNiveau(t_niveau ** niveau);
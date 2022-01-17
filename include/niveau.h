/**
 * \struct t_obstacle
 * \brief Structure représentant une salle
*/
typedef struct s_salle{
    int complete; /** Booléen, vrai si la salle est complétée (plus de monstres) */
    struct s_salle ** groupe; /** Ensemble de salles formant une unique salle */
    //t_monstre ** (liste de monstres)
    //t_obstacle ** (liste d'obstacles)
} t_salle;

/**
 * \struct t_niveau
 * \brief Structure représentant une matrice de salles
*/
typedef struct {
    t_salle *** salles; //??????????????????????? je vais voir ça
    int h; /** Largeur du niveau */
    int l; /** Hauteur du niveau */
} t_niveau;

//Charge à partir d'un fichier le niveau vers t_niveau;
int chargerNiveau();
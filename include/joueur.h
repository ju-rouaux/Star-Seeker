#ifndef _MOVE_PLAYER_
#define _MOVE_PLAYER_


#define PROPORTION_JOUEUR 1.6 /**< Taille du joueur par rapport à la taille  d'une tile */

/**
 * \struct move 
 * \brief Objet contenenant toutes les coordonées du joueur ainsi que l'etat des fleches pour son deplacement
 */

typedef struct {
    int arrow_right; /**Booleen, vrai si la fleche de droite est appuyée */
    int arrow_left; /**Booleen, vrai si la fleche de gauche est appuyée */
    int arrow_down; /**Booleen, vrai si la fleche du bas est appuyée */
    int arrow_up; /**Booleen, vrai si la fleche du haut est appuyée */
    int x; /**Variable contenant la position x du joueur*/
    int y; /**Variable contenant la position y du joueur*/
}
move;

typedef struct
{
    int to_up;
    int to_down;
    int to_left;
    int to_right;

} t_player_flags;

/**
 * \struct t_position
 * \brief Structure modélisant la position du joueur sur le niveau
 */
typedef struct
{
    int x;
    int y;
} t_position;

/**
 * \struct t_joueur
 * \brief Structure modélisant le joueur
 */
typedef struct
{
    t_position * position;
    t_player_flags * flags;
    float vitesse; /**< Exprimée sans unité */
    //Autres données comme les pv, expererience...
} t_joueur;

move move_player(SDL_Event * keyboard, move * player);
void refresh_keys(SDL_Event * keyboard, move * player);
void initialize_keys(move * player);
t_joueur * creerJoueur(int x, int y);
void detruireJoueur(t_joueur ** joueur);
void updatePositionJoueur(t_joueur * joueur, int echelle);

#endif
#ifndef _MOVE_PLAYER_
#define _MOVE_PLAYER_

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

move move_player(SDL_Event * keyboard, move * player);
void refresh_keys(SDL_Event * keyboard, move * player);
void initialize_keys(move * player);

#endif
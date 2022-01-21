
typedef struct {
    int arrow_right; /**Booleen, vrai si la fleche de droite est appuyée */
    int arrow_left; /**Booleen, vrai si la fleche de gauche est appuyée */
    int arrow_down; /**Booleen, vrai si la fleche du bas est appuyée */
    int arrow_up; /**Booleen, vrai si la fleche du haut est appuyée */
    int x; /**Variable contenant la position x du joueur*/
    int y; /**Variable contenant la position y du joueur*/
}
move;

move move_player();
int refresh_keys(move * player);
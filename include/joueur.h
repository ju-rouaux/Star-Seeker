#ifndef _MOVE_PLAYER_
#define _MOVE_PLAYER_

#include <SDL2/SDL.h>
#include <entite.h>

#define PROPORTION_JOUEUR 1.6 /**< Taille du joueur par rapport à la taille  d'une tile */

typedef struct
{
    int to_up;
    int to_down;
    int to_left;
    int to_right;

} t_joueur_flags;

/**
 * \struct t_joueur
 * \brief Structure modélisant le joueur
 */
typedef struct
{
    #include <attributs_personnages.h>
    t_joueur_flags * flags;

    //Autres données comme les pv, expererience...
} t_joueur;

t_joueur * creerJoueur(float x, float y, SDL_Texture * apparence);
void detruireJoueur(t_joueur ** joueur);

#endif
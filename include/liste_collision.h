// Mise en oeuvre par pointeurs de listes de dominos

#ifndef _JEU_LISTE_COLLISION_
#define _JEU_LISTE_COLLISION_

#include <SDL2/SDL.h>

typedef struct collision 
{
    SDL_Rect rectangle; 
    struct collision* pred; 
    struct collision* succ;
} t_collision;

typedef struct 
{
    t_collision* drapeau; 
    t_collision* ec;
} t_liste_collision;

void init_liste(t_liste_collision *l);
int liste_vide(t_liste_collision *l);
int hors_liste(t_liste_collision *l);
void en_tete(t_liste_collision *l);
void en_queue(t_liste_collision *l);
void suivant(t_liste_collision *l);
void precedent(t_liste_collision *l);
void valeur_elt(t_liste_collision *l, SDL_Rect *);
void modif_elt(t_liste_collision *l, SDL_Rect);
void oter_elt(t_liste_collision *l);
void ajout_droit(t_liste_collision *l, SDL_Rect);
void ajout_gauche(t_liste_collision *l, SDL_Rect);
int taille(t_liste_collision *l);

#endif

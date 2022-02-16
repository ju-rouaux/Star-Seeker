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

void collision_init_liste(t_liste_collision *l);
int collision_liste_vide(t_liste_collision *l);
int collision_hors_liste(t_liste_collision *l);
void collision_en_tete(t_liste_collision *l);
void collision_en_queue(t_liste_collision *l);
void collision_suivant(t_liste_collision *l);
void collision_precedent(t_liste_collision *l);
void collision_valeur_elt(t_liste_collision *l, SDL_Rect *);
void collision_modif_elt(t_liste_collision *l, SDL_Rect);
void collision_oter_elt(t_liste_collision *l);
void collision_ajout_droit(t_liste_collision *l, SDL_Rect);
void collision_ajout_gauche(t_liste_collision *l, SDL_Rect);
int collision_taille(t_liste_collision *l);

#endif

/**
 * \file menu.c
 * \author Guillaume
 * \brief Menu principal
 * 
 */

#ifndef _JEU_MENU_
#define _JEU_MENU_

#include <SDL2/SDL.h>

#include <SDL2/SDL_image.h>

#include <SDL2/SDL_ttf.h>

#include <moteur.h>

#include <string.h>

#include <menu_options.h>

#define TAILLE_MAX 17

#define NB_B_MENU 4
#define LARGEUR(i) (boutons[i]->largeur)

#define NOMS_B_MENU {"Nouvelle Partie","Charger Partie","Options","Quitter"}


typedef struct s_bouton {
    SDL_Texture * texture;
    SDL_Rect rect;
    int longueur;
}
t_bouton;

int chargerMenu(t_moteur * moteur);
t_bouton ** initialiserBoutons(t_moteur * moteur, int nb_boutons, char nom_boutons[][TAILLE_MAX]);
void detruireBoutons(t_bouton ** * boutons, int nb_boutons);
int update_textureBouton(t_moteur * moteur, t_bouton * bouton, int rect_x, int rect_y);
int maj_TextureMenu(t_moteur * moteur, t_bouton ** boutons, int nb_boutons);

#endif //_JEU_MENU_
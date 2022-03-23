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

#include <window.h>

#include <moteur.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TAILLE_MAX 17

#define NB_B_MENU 4
#define T_LARGEUR 2
#define T_LONGUEUR 1.5
#define B_LARGEUR 2.5
#define B_LONGUEUR 1

#define NOMS_B_MENU {"Nouvelle Partie","Charger Partie","Options","Quitter"}


typedef enum {ERROR_MENU_TEXTURE = -2,ERROR_MENU, M_PRINCIPAL = 1, M_JEU,M_CHARGER,M_OPTIONS, M_KEYMAP, M_QUITTER} e_menu;

typedef struct s_bouton {
    SDL_Texture * texture;
    SDL_Rect rect;
    int longueur;
}t_bouton;



e_menu chargerMenu(t_moteur * moteur);
t_bouton ** initialiserBoutons(t_moteur * moteur, int nb_boutons, char nom_boutons[][TAILLE_MAX]);
void detruireBoutons(t_bouton ** * boutons, int nb_boutons);
int update_textureBouton(t_moteur * moteur, t_bouton * bouton, int rect_x, int rect_y);
int maj_TextureMenu(t_moteur * moteur, t_bouton ** boutons, int nb_boutons);

SDL_Rect * initialiserTexte(t_moteur * moteur, SDL_Texture ** texture, char * texte);
int maj_TextureTexte(t_moteur * moteur,SDL_Rect * rect, SDL_Texture ** texture,int rect_x, int rect_y, char * texte);
void detruireTexte(SDL_Rect ** rect, SDL_Texture * texture);
#endif //_JEU_MENU_
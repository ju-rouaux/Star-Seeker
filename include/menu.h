/**
 * \file menu.h
 * \author Guillaume Richard
 * \brief Menu principal du jeu
 * 
 */

#ifndef _JEU_MENU_
#define _JEU_MENU_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <moteur.h>
#include <window.h>
#include <main.h>

#define TAILLE_MAX 17

#define NB_B_MENU 5
#define T_LARGEUR 2
#define T_LONGUEUR 1.5
#define B_LARGEUR 2.5
#define B_LONGUEUR 1

#define NOMS_B_MENU {"Nouvelle Partie","Charger Partie","Reset Joueur","Options","Quitter"}

/**
 * \struct t_bouton
 * \brief Modelise un bouton avec du texte
 */
typedef struct s_bouton {
    SDL_Texture * texture;/**<Texture a un bouton*/
    SDL_Rect rect;/**<Hitbox d'un bouton*/
    int longueur;/**<Longeur de la chaine de caractères*/
}t_bouton;



e_code_main chargerMenu(t_moteur * moteur);
t_bouton ** initialiserBoutons(t_moteur * moteur, int nb_boutons, char nom_boutons[][TAILLE_MAX]);
void detruireBoutons(t_bouton ** * boutons, int nb_boutons);
int update_textureBouton(t_moteur * moteur, t_bouton * bouton, int rect_x, int rect_y);
int maj_TextureMenu(t_moteur * moteur, t_bouton ** boutons, int nb_boutons);

SDL_Rect * initialiserTexte(t_moteur * moteur, SDL_Texture ** texture, char * texte);
int maj_TextureTexte(t_moteur * moteur,SDL_Rect * rect, SDL_Texture ** texture,int rect_x, int rect_y, char * texte);
void detruireTexte(SDL_Rect ** rect, SDL_Texture * texture);
#endif //_JEU_MENU_

/**
 * \file menu_options_keymap.h
 * \author Guillaume
 * \brief Sous menu pour le mapping des touches
 * 
 */

#ifndef _JEU_MENU_OPTIONS_KEYMAP_
#define _JEU_MENU_OPTIONS_KEYMAP_

#include <moteur.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <menu.h>

#define NB_B_MENU_OPTIONS_KEYMAP 6
#define B_LEFT "Gauche"
#define B_RIGHT "Droite"
#define B_DOWN "Bas"
#define B_UP "Haut"
#define B_PROJECTILE "Projectile"
#define NOMS_B_MENU_OPTIONS_KEYMAP {B_UP, B_DOWN, B_RIGHT, B_LEFT,B_PROJECTILE,B_RETOUR}

int chargerMenu_Options_keymap(t_moteur * moteur);

#endif //_JEU_MENU_OPTIONS_KEYMAP_
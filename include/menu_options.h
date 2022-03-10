/**
 * \file menu.c
 * \author Guillaume
 * \brief Sous menu, volume et acces au menu pour le mapping des touches
 * 
 */

#ifndef _JEU_MENU_OPTIONS_
#define _JEU_MENU_OPTIONS_

#include <moteur.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <menu.h>
#include <menu_options_keymap.h>

#define NB_B_MENU_OPTIONS 3
#define B_VOLUME "Mute audio"
#define B_KEYMAP "Keymap"
#define B_RETOUR "Retour"
#define NOMS_B_MENU_OPTIONS {B_VOLUME,B_KEYMAP,B_RETOUR}

int chargerMenu_Options(t_moteur * moteur);


#endif //_JEU_MENU_OPTIONS_
/**
 * \file menu_options_keymap.h
 * \author Guillaume
 * \brief Sous menu pour le mapping des touches
 * 
 */

#ifndef _JEU_MENU_OPTIONS_KEYMAP_
#define _JEU_MENU_OPTIONS_KEYMAP_

#include <menu.h>

#define NB_B_MENU_OPTIONS_KEYMAP 6
#define NOMS_B_MENU_OPTIONS_KEYMAP {"Haut","Bas","Droite","Gauche","Interaction","Retour"}

e_code_main chargerMenu_Options_keymap(t_moteur * moteur);

#endif //_JEU_MENU_OPTIONS_KEYMAP_
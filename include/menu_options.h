/**
 * \file menu.c
 * \author Guillaume
 * \brief Sous menu, volume et acces au menu pour le mapping des touches
 * Permet au joueur de choisir s'il veut du son et d'acceder au menu pour reparamétrer ses touches
 * 
 */

#ifndef _JEU_MENU_OPTIONS_
#define _JEU_MENU_OPTIONS_

#include <menu.h>

#define NB_B_MENU_OPTIONS 4
#define NOMS_B_MENU_OPTIONS {"Toggle volume","Keymap","Credits","Retour"}

e_code_main chargerMenu_Options(t_moteur * moteur);

#endif //_JEU_MENU_OPTIONS_
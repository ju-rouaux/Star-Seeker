/**
 * \file sauvegarde.c
 * 
 * \brief Sauvegarde des structures du jeu pour permettre au joueur de continuer sa partie.
 * 
 * \author Guillaume Richard & Julien Rouaux
 */

#ifndef _JEU_SAUVEGARDE_
#define _JEU_SAUVEGARDE_

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <joueur.h>
#include <entite.h>
#include <generation_niveau.h>

#define filename_joueur "./save/save_joueur.save"
#define filename_niveau "./save/save_niveau.save"

int chargerSauvegarde(t_joueur * joueur, niveau_informations_t ** niveau);
int sauvegarder(t_joueur * joueur, niveau_informations_t * niveau);

#endif //_JEU_SAUVEGARDE_
/**
 * \file sauvegarde.h
 * \author Guillaume
 * \brief Sauvegarde l'etat actuel de certains objets dans un fichier.
 * Recupere la sauvegarde precedente si elle existe et la charge dans les objets appropriés.
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
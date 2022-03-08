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

typedef enum
{
    NO_FILE = -5, MALLOC_FAIL = -4, READ_OR_WRITE_FAIL = -3, FOPEN_FAIL = -2, SAVE_ERROR = -1, SUCCESS = 0
} err_save;

int sauvegarderPartie(niveau_informations_t ** infos_niveaux, int nb_niveaux, int indice_niveau_charge);
int sauvegarderJoueur(t_joueur * joueur);
int chargerJoueur(t_joueur * joueur);
int chargerPartie(niveau_informations_t *** infos_niveaux, int * nb_niveaux, int * indice_niveau_charge);

#endif //_JEU_SAUVEGARDE_
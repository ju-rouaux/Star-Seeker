/**
 * \file sauvegarde.c
 * 
 * \brief Sauvegarde des structures du jeu pour permettre au joueur de continuer sa partie.
 * 
 * \author Julien Rouaux & Guillaume Richard
 */

#ifndef _JEU_SAUVEGARDE_
#define _JEU_SAUVEGARDE_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <moteur.h>
#include <joueur.h>
#include <generation_niveau.h>
#include <monstre.h>
#include <interaction.h>

/**
 * \enum err_save
 * \brief Erreurs possibles lors des différentes sauvegarde
 */
typedef enum
{
    NO_FILE = -5, MALLOC_FAIL = -4, READ_OR_WRITE_FAIL = -3, FOPEN_FAIL = -2, SAVE_ERROR = -1, SUCCESS = 0
} err_save;

err_save sauvegarderPartie(char * nom_galaxie, niveau_informations_t ** infos_niveaux, int nb_niveaux, int indice_niveau_charge);
err_save sauvegarderJoueur(t_joueur * joueur);
err_save sauvegarderParametres(t_parametres * parametres);
err_save chargerSaveJoueur(t_joueur * joueur);
err_save chargerSavePartie(char ** nom_galaxie, niveau_informations_t *** infos_niveaux, int * nb_niveaux, int * indice_niveau_charge);
err_save chargerSaveParametres(t_parametres * parametres);
#endif //_JEU_SAUVEGARDE_
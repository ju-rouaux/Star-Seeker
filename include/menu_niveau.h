/**
 * \file menu_niveau.h
 * 
 * \brief Menu de sélection d'un niveau d'une partie.
 * 
 * \author Julien Rouaux
 */

#ifndef _JEU_MENU_NIVEAU_
#define _JEU_MENU_NIVEAU_

#include <moteur.h>
#include <generation_niveau.h>

e_code_main afficherMenuNiveau(int * retour, t_moteur * moteur, niveau_informations_t ** infos_niveaux, int nb_infos);

#endif //_JEU_MENU_NIVEAU_
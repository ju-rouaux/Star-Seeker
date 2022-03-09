/**
 * \file partie.h
 * 
 * \brief Module de gestion d'une partie : appel de sauvegarde
 * et appel des différents niveaux.
 * 
 * \author Julien Rouaux
 */

#ifndef _JEU_PARTIE_
#define _JEU_PARTIE_

#include <moteur.h>

int nouvellePartie(t_moteur * moteur, int nb_niveaux);
int chargerPartie(t_moteur * moteur);

#endif //_JEU_PARTIE_
/**
 * \file events.h
 * 
 * \brief Module de gestion des evenements (souris/clavier/fenetre)
 * Detecte les evenements liés au clics de la souris, aux touches appuyées ou relachées et a la croix de la fenetre pour quitter
 * 
 * \author Guillaume Richard
 */

#ifndef _JEU_EVENTS_
#define _JEU_EVENTS_

#include <joueur.h>
#include <moteur.h>
#include <main.h>

e_code_main handleEvents(t_joueur * joueur, t_parametres * parametres);

#endif //_JEU_EVENTS_

/**
 * \file overlay.h
 * 
 * \brief Module de gestion de l'interface utilisateur in-game
 * 
 * \author Camille Remoué
 */

#ifndef _OVERLAY_
#define _OVERLAY_

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <overlay.h>
#include <textures.h> 
#include <joueur.h>
#include <moteur.h>
#include <generation_niveau.h>


void dessiner_map(t_moteur * moteur, niveau_informations_t * infosNiveau, int idSalle);
void dessiner_hud(t_moteur * moteur, t_joueur * joueur);


#endif //_OVERLAY_
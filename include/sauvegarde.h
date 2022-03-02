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
#include <animation.h>
#include <generation_niveau.h>


void save_current_game(char * filename, void * input,size_t size);
int read_file_player(char * filename, t_joueur * joueur);
niveau_informations_t * read_file_niveau(char * filename, niveau_informations_t * niveau);
int file_empty(const char * filename);


void print_struct_player(const t_joueur * tmp);
void print_struct_niveau(const niveau_informations_t * tmp);

#endif _JEU_SAUVEGARDE_
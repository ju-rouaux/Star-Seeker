#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <joueur.h>
#include <entite.h>


void write_file_player(const char * filename, t_joueur * joueur);
t_joueur * read_file_player(const char * filename, t_joueur * joueur);
int file_empty(const char * filename);
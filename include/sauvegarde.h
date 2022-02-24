#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <joueur.h>
#include <entite.h>
#include <animation.h>


void write_file_player(const char * filename, t_joueur * joueur);
t_joueur * read_file_player(const char * filename, t_joueur * joueur);
int file_empty(const char * filename);


void print_struct_player(t_joueur *joueur);
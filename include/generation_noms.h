/**
 * \file generation_noms.h
 * 
 * \brief Générateur de nom de planète et de galaxie aléatoire
 *
 * \author Camille Remoué
 *  
 */

#ifndef _NOMS_GENERATEUR_
#define _NOMS_GENERATEUR_

#define MAX_NOM_NIVEAU 10

char * creer_nom(int taille_mot);
char ** creer_noms_planetes(char * nom_galaxie, int nombre);
void detruireNomsPlanetes(char *** noms_planetes, int nombre);

#endif
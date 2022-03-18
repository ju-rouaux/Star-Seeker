/**
 * \file generateur_nom_planete.h
 * 
 * \brief Générateur de nom de planète et de galaxie aléatoire
 *
 * \author camille
 *  
 */



#ifndef _NOMS_GENERATEUR_
#define _NOMS_GENERATEUR_

#define MAX_NOM_NIVEAU 10

char * creer_nom(int taille_mot);
void creer_noms_planetes(char * nom_galaxie, int nombre, char noms_planetes[][MAX_NOM_NIVEAU]);

#endif
/**
 * \file liste.h
 * 
 * \brief Module de gestion d'une liste.
 * 
 * \author Guillaume Richard
 */

#ifndef _JEU_LISTE_
#define _JEU_LISTE_

#include <stdio.h>
#include <stdlib.h>
#include <entite.h>

typedef struct element {
    t_entite * valeur ;
    struct element* pred ;
    struct element* succ ;
} t_element;

typedef struct {
    t_element * drapeau;
    t_element * ec;
} t_liste ;


void init_liste(t_liste* l);

int liste_vide(t_liste * l);

void detruire_liste(t_liste ** l);

int hors_liste(t_liste * l);

void en_tete(t_liste * l);

void en_queue(t_liste * l);

void precedent(t_liste * l);

void suivant(t_liste * l);

void valeur_elt(t_liste * l, t_entite ** v);

void modif_elt(t_liste * l, t_entite ** v);

void oter_elt(t_liste * l);

void ajout_droit(t_liste * l, t_entite * v);

void ajout_gauche(t_liste * l, t_entite * v);

#endif //_JEU_LISTE_
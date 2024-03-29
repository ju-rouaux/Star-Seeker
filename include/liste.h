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

typedef struct s_entite t_entite;

/**
 * \struct t_element
 * \brief Modelise un element de la liste
 */
typedef struct element {
    t_entite * valeur ; /**<valeur */
    struct element* pred ;/**<element precedant l'element courant*/
    struct element* succ ;/**<element succedant l'element courant*/
} t_element;

/**
 *\struct t_liste
 *\brief Modelise l'emplacement actuel dans la liste
 * 
 */
typedef struct s_liste t_liste;
struct s_liste{
    t_element * drapeau;/**<drapeau de la liste*/
    t_element * ec;/**<l'element courant*/
} ;


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
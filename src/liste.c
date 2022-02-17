/**
 * \file liste.c
 * \author Guillaume Richard
 * \brief Module de gestion de liste
 */

#include "liste.h"

void init_liste(t_liste* l){
// Crée la liste constituée du seul drapeau
    l->drapeau = malloc(sizeof(t_element));
    l->drapeau -> pred = l->drapeau;
    l->drapeau -> succ = l->drapeau;
    l->ec = l->drapeau;
}

int liste_vide(t_liste * l){
    return (l->drapeau->succ == l->drapeau) ;
}

int hors_liste(t_liste * l){
    return (l->ec == l->drapeau) ;
}

void en_tete(t_liste * l){
    if (!liste_vide(l))
        l->ec = l->drapeau->succ;
}

void en_queue(t_liste * l){
    if (!liste_vide(l))
        l->ec = l->drapeau->pred ;
}

void precedent(t_liste * l){
    if (!hors_liste(l))
        l->ec = l->ec->pred;
}

void suivant(t_liste * l) {
    if (!hors_liste(l))
        l->ec = l->ec->succ;
}

void valeur_elt(t_liste * l, void ** v) {
    if (!hors_liste(l))
        *v = l->ec->valeur;
}

void modif_elt(t_liste * l, void ** v) {
    if (!hors_liste(l))
        l->ec->valeur = *v;
}

void oter_elt(t_liste * l) {
    if (!hors_liste(l)) {
        t_element * p;

        (l -> ec -> pred) -> succ = l -> ec -> succ;
        (l -> ec -> succ) -> pred = l -> ec -> pred;
        p = l -> ec;
        precedent(l);
        free(p);
    }
}

void ajout_droit(t_liste * l, void * v) {
    if (liste_vide(l) || !hors_liste(l)) {
        t_element * nouv;

        nouv = (t_element * ) malloc(sizeof(t_element));
        nouv -> valeur = v;
        nouv -> pred = l -> ec;
        nouv -> succ = l -> ec -> succ;
        //Mise a jour des chainages des voisins
        (l -> ec -> succ) -> pred = nouv;
        l -> ec -> succ = nouv;
        //On se positionne sur le nouvel ?lement
        l -> ec = nouv;
    }
}

void ajout_gauche(t_liste * l, void * v) {
    if (liste_vide(l) || !hors_liste(l)) {
        t_element * nouv;

        nouv = malloc(sizeof(t_element));
        nouv -> valeur = v;
        nouv -> pred = l -> ec -> pred;
        nouv -> succ = l -> ec;
        //Mise a jour des chainages des voisins
        (l -> ec -> pred) -> succ = nouv;
        l -> ec -> pred = nouv;
        //On se positionne sur le nouvel element
        l -> ec = nouv;
    }
}


void affichage_liste(t_liste * l) {
    void * tmp;
    if (liste_vide(l))
        printf("Liste Vide");
    else {
        en_tete(l);
        printf("Affichage de la liste : \n");
            while (!hors_liste(l)) {
                valeur_elt(l, &tmp);
                printf("%s ", (char *) tmp);
                suivant(l);
            }
        printf("\n");
    }
}

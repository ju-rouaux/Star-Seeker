/**
 * \file liste.c
 * \author Guillaume Richard
 * \brief Module de gestion de liste en t_entite
 */

#include <entite.h>
#include <liste.h>

void init_liste(t_liste* l){
// Crée la liste constituée du seul drapeau
    l->drapeau = malloc(sizeof(t_element));
    l->drapeau -> pred = l->drapeau;
    l->drapeau -> succ = l->drapeau;
    l->ec = l->drapeau;
}

/**
 * \brief Booleen, vrai si la liste est vide
 * \param l une liste
 * \return int booleen 1 : vrai, 0 : faux
 */
int liste_vide(t_liste * l){
    return (l->drapeau->succ == l->drapeau) ;
}

/**
 * \brief Booleen, l'element courant est hors liste
 * \param l une liste
 * \return int booleen 1 : vrai, 0 : faux
 */
int hors_liste(t_liste * l){
    return (l->ec == l->drapeau) ;
}

/**
 * \brief Met l'element courant au premier element de la liste
 * \param l une liste
 */
void en_tete(t_liste * l){
    if (!liste_vide(l))
        l->ec = l->drapeau->succ;
}

/**
 * \brief Met l'element courant au dernier element de la liste
 * \param l une liste
 */
void en_queue(t_liste * l){
    if (!liste_vide(l))
        l->ec = l->drapeau->pred ;
}

/**
 * \brief Met l'element courant a l'element juste avant l'element courant
 * \param l une liste
 */
void precedent(t_liste * l){
    if (!hors_liste(l))
        l->ec = l->ec->pred;
}

/**
 * \brief Met l'element courant a l'element juste apres l'element courant
 * \param l une liste
 */
void suivant(t_liste * l) {
    if (!hors_liste(l))
        l->ec = l->ec->succ;
}

/**
 * \brief Recupere la valeur de l'element de la liste et _entite *
 */
void valeur_elt(t_liste * l, t_entite ** v) {
    if (!hors_liste(l))
        *v = l->ec->valeur;
}

/**
 * \brief Recupere la valeur de l'element de la liste et l'assigne a v
 * 
 * \param l une liste
 * \param v une valeur
 */
void modif_elt(t_liste * l, t_entite ** v) {
    if (!hors_liste(l))
        l->ec->valeur = *v;
}

/**
 * \brief Supprime l'element de la liste a l'endroit ou est l'ec
 * 
 * \param l une liste
 */
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

/**
 * \brief Ajoute a droite de l'element courant une valeur v
 * 
 * \param l une liste
 * \param v une valeur
 */
void ajout_droit(t_liste * l, t_entite * v) {
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

/**
 * \brief Ajoute a gauche de l'element courant une valeur v
 * 
 * \param l une liste
 * \param v une valeur
 */
void ajout_gauche(t_liste * l, t_entite * v) {
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
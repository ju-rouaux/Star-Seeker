/**
 * \file liste.c
 * \author Guillaume
 * \brief Module de gestion de liste
 * 
 */

#include <stdio.h>

#include<stdlib.h>

#include "liste.h"

/**
 * \brief Initialise la liste
 * 
 * \param l liste 
 */
void init_liste(liste_t * l) {
    l -> premier = NULL;
    l -> dernier = NULL;
}


/**
 * \brief Ajout d'une valeur en fin de liste
 * 
 * \param l une liste
 * \param val une valeur a ajouter
 */
void pushback_liste(liste_t * l, int val) {
    elem_t * nouv = malloc(sizeof(elem_t));

    if (!nouv) exit(EXIT_FAILURE);

    nouv -> valeur = val;
    nouv ->precedent = l->dernier;
    nouv -> suivant = NULL;

    if (l -> dernier) 
        l -> dernier -> suivant = nouv;
    else 
        l -> premier = nouv;

    l -> dernier = nouv;
}


/**
 * \brief Ajout d'une valeur en debut de liste
 * 
 * \param l une liste
 * \param val une valeur a ajouter
 */
void pushfront_liste(liste_t * l, int val) {
    elem_t * nouv = malloc(sizeof(elem_t));

    if (!nouv) exit(EXIT_FAILURE);

    nouv -> valeur = val;
    nouv -> suivant = l -> premier;
    nouv -> precedent = NULL;

    if (l -> premier) 
        l -> premier -> precedent = nouv;
    else 
        l -> dernier = nouv;

    l -> premier = nouv;
}


/**
 * \brief Supprime une valeur en fin de liste.
 * 
 * \param l une liste
 */
int popback_liste(liste_t * l) {
    int val;
    elem_t * tmp = l -> dernier;

    if (!tmp) return -1;
    
    val = tmp -> valeur;
    l -> dernier = tmp -> precedent;
    if (l -> dernier)  
        l -> dernier -> suivant = NULL;
    else 
        l -> premier = NULL;
    
    free(tmp);
    return val;
}


/**
 * \brief Supprime une valeur en début de liste.
 * 
 * \param l une liste
 */
int popfront_liste(liste_t * l) {
    int val;
    elem_t * tmp = l -> premier;
    if (!tmp) return -1;
    val = tmp -> valeur;
    l -> premier = tmp -> suivant;
    if (l -> premier) l -> premier -> precedent = NULL;
    else l -> dernier = NULL;
    free(tmp);
    return val;
}

/**
 * \brief Affiche la liste
 * 
 * \param l une liste
 */
void display_liste(liste_t l) {
    elem_t * pelem = l.premier;
    while (pelem) {
        printf("%d\n", pelem -> valeur);
        pelem = pelem -> suivant;
    }
}


/**
 * \brief Supprime toutes les valeurs dans la liste
 * 
 * \param l une liste
 */
void clear_liste(liste_t * l) {
    elem_t * tmp;
    elem_t * pelem = l -> premier;
    while (pelem) {
        tmp = pelem;
        pelem = pelem -> suivant;
        free(tmp);
    }
    l -> premier = NULL;
    l -> dernier = NULL;
}


/**
 * \brief Supprime un element de la liste a un index donné
 * 
 * \param l liste 
 * \param index index
 */
 
int remove_by_index(liste_t * l, int index) {
    int res = -1; //valeur de retour
    elem_t * ec = l->premier;
    elem_t * temp_liste = NULL;

    if (index + 1 == 0) {
        return popfront_liste(l);
    }

    for (int i = 1; i < index-1; i++) {
        if (ec->suivant == NULL) {
            return -1;
        }
        ec = ec->suivant;
    }

    if (ec->suivant == NULL) {
        return -1;
    }

    temp_liste = ec->suivant;
    res = temp_liste->valeur;
    ec->suivant = temp_liste->suivant;
    free(temp_liste);

    return res;

}

/**
*\brief Vérifie que la liste n'est pas vide
*
*\param l liste
*\return 0 si la liste est vide
*/
int list_empty(liste_t * l){

  if (l -> premier == NULL && l -> dernier == NULL)
    return 1;
  else return 0;

}

/**
*\brief retourne la valeur d'un element donné par un index dans la liste
*
*\param l liste
*\param index index d'un element
*\return la valeur du premier 
*/
int list_get_value(liste_t * l,int index)
{
     int res = -1; //valeur de retour
    elem_t * ec = l->premier;

    if (index + 1 == 0) {
        res =  ec->valeur;
    }

    for (int i = 1; i < index-1; i++) {
        if (ec->suivant == NULL) {
            return -1;
        }
        ec = ec->suivant;
    }
    res = ec->valeur;

    return res;
}

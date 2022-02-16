/**
 * \file liste.h
 * \author Guillaume
 * \brief Module de gestion de liste
 * 
 * 
 */
#ifndef _MODULE_LISTE_
#define _MODULE_LISTE_


#define ERREUR -1

/**
 * \brief Structure representant un element de la liste
 * 
 */
typedef struct elem_s
{
    int valeur;
    struct elem_s * precedent;
    struct elem_s * suivant;
}elem_t;


/**
 * \brief Structure d'accès à la liste
 * 
 */
typedef struct {
    elem_t * premier;
    elem_t * dernier;
}
liste_t;

/**  Initialisation de la liste. */

void init_liste(liste_t * l);

/**  Ajout d'une valeur en fin de liste. */

void pushback_liste(liste_t * l, int val);

/**  Ajout d'une valeur en début de liste. */

void pushfront_liste(liste_t * l, int val);

/**  Retrait d'une valeur en fin de liste. */

int popback_liste(liste_t * l);

/**  Retrait d'une valeur en début de liste. */

int popfront_liste(liste_t * l);

/**  Affichage de la liste. */

void display_liste(liste_t l);

/**  Suppression de tous les éléments de la liste */

void clear_liste(liste_t * l);

/** Suppresion d'un element a un index donné */
int remove_by_index(liste_t * l, int index);
/** Recuperer la valeur d'un element grace a index donné*/
int list_get_value(liste_t * l,int index);
/**Verifie que la liste n'est pas vide*/
int list_empty(liste_t * l);
#endif

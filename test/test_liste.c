/**
 * \file test_liste.c
 * 
 * \brief Script de test pour la liste
 * 
 * Fonction tirées de liste.h modifiée en int
 * 
 * \author Guillaume Richard
 */

//gcc test/test_liste.c -o test_liste

#include <stdio.h>
#include <stdlib.h>

/**
 * \struct t_element
 * \brief Modelise un element de la liste
 */
typedef struct element {
    void * valeur ; /**<valeur */
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
void detruire_liste(t_liste ** l);
int hors_liste(t_liste * l);
void en_tete(t_liste * l);
void en_queue(t_liste * l);
void precedent(t_liste * l);
void suivant(t_liste * l);
void valeur_elt(t_liste * l, int ** v);
void modif_elt(t_liste * l, int ** v);
void oter_elt(t_liste * l);
void ajout_droit(t_liste * l, int * v);
void ajout_gauche(t_liste * l, int * v);

/**
 * \brief Initialise la liste
 * 
 * \param l la liste à initialiser
 */
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
 * \brief Détruit la liste et libere la mémoire allouée
 * \param l la liste a détruire
 */
void detruire_liste(t_liste ** l)
{
    if(*l != NULL)
    {
        en_queue(*l);

        while(!liste_vide(*l))
            oter_elt(*l);

        free((*l)->drapeau);
        free(*l);
    }
    *l = NULL;
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
void valeur_elt(t_liste * l, int ** v) {
    if (!hors_liste(l))
        *v = l->ec->valeur;
}

/**
 * \brief Recupere la valeur de l'element de la liste et l'assigne a v
 * 
 * \param l une liste
 * \param v une valeur
 */
void modif_elt(t_liste * l, int ** v) {
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
void ajout_droit(t_liste * l, int * v) {
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
void ajout_gauche(t_liste * l, int * v) {
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

void main(){

    t_liste * liste_test = malloc(sizeof(t_liste));
    init_liste(liste_test);
    int nb_element = 0;
    int * temp = malloc(sizeof(int));

    printf("Liste vide : liste_vide(liste_test) = %d (1 si vide, 0 sinon)\n",liste_vide(liste_test));
    
    printf("Ajout droit de valeur de 1 à 10\n");
    for(int i = 1; i <= 10; i++){
        ajout_droit(liste_test, i);
        nb_element ++;
    }
    en_tete(liste_test);
    printf("Ajout gauche de valeur de 0 à -10 en tete de la liste\n");
    for(int i = 0; i >= -10; i--){
        ajout_gauche(liste_test, i);
        nb_element ++;
    }

    en_queue(liste_test);
    int modif = 20;
    printf("Modification derniere valeur de la liste par 20\n");
    modif_elt(liste_test, &modif);

    printf("Suppression avant derniere valeur\n");
    precedent(liste_test);
    oter_elt(liste_test);
    nb_element--;

    printf("Affichage de la liste dans l'ordre\n");
    en_tete(liste_test);
    for(int i = 0; i < nb_element; i++){
        valeur_elt(liste_test, &temp);
        printf("Elem %d : %d\n",i + 1,temp);
        suivant(liste_test);
    }

    printf("Affichage de la liste dans l'ordre inverse\n");
    en_queue(liste_test);
    for(int i = 0; i < nb_element; i++){
        valeur_elt(liste_test, &temp);
        printf("Elem %d : %d\n",i + 1,temp);
        precedent(liste_test);
    }

    printf("Destruction de la liste\n");
    detruire_liste(&liste_test);
    if(liste_test == NULL){
        printf("Destruction de la liste réussie\n");
    }
    else{
        printf("Destruction de la liste échouée\n");
    }
    free(temp);
}




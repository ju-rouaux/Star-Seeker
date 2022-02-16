// Mise en oeuvre par pointeurs de listes
#include <stdlib.h>
#include <liste_collision.h>


// Primitives de listes 

void init_liste(t_liste_collision *l) {
	l->drapeau = (t_collision*)malloc(sizeof(t_collision));

	l->drapeau->pred = l->drapeau;
	l->drapeau->succ = l->drapeau;
	l->ec = l->drapeau;
}

int liste_vide(t_liste_collision *l) {
	return ((l->drapeau->pred == l->drapeau) && (l->drapeau->succ == l->drapeau));
}

int hors_liste(t_liste_collision *l) {
	return (l->ec == l->drapeau);
}

void en_tete(t_liste_collision *l) {
	if(!liste_vide(l))
		l->ec = l->drapeau->succ;
}

void en_queue(t_liste_collision *l) {
	if(!liste_vide(l))
		l->ec = l->drapeau->pred;
}

void suivant(t_liste_collision *l) {
	if(!hors_liste(l))
		l->ec = l->ec->succ;
}

void precedent(t_liste_collision *l) {
	if(!hors_liste(l))
		l->ec = l->ec->pred;
}

void valeur_elt(t_liste_collision *l, SDL_Rect* rectangle) {
	if(!hors_liste(l))
		*rectangle = l->ec->rectangle;
}

void modif_elt(t_liste_collision *l, SDL_Rect rectangle) {
	if(!hors_liste(l))
		l->ec->rectangle = rectangle;
}

void oter_elt(t_liste_collision *l) {
	if(!hors_liste(l)) {
		t_collision* p;

		(l->ec->pred)->succ = l->ec->succ;
		(l->ec->succ)->pred = l->ec->pred;
		p = l->ec;
		precedent(l);
		free(p);
	}
}

void ajout_droit(t_liste_collision *l, SDL_Rect rectangle) {
	if(liste_vide(l) || !hors_liste(l)) {
		t_collision* nouv;

		nouv = (t_collision*)malloc(sizeof(t_collision));
		nouv->rectangle = rectangle;
		nouv->pred = l->ec;
		nouv->succ = l->ec->succ;
		//Mise a jour des chainages des voisins
		(l->ec->succ)->pred = nouv;
		l->ec->succ = nouv;
		//On se positionne sur le nouvel element
		l->ec = nouv;
	}
}

void ajout_gauche(t_liste_collision *l, SDL_Rect rectangle) {
	if(liste_vide(l) || !hors_liste(l)) {
		t_collision* nouv;

		nouv = (t_collision*)malloc(sizeof(t_collision));
		nouv->rectangle = rectangle;
		nouv->pred = l->ec->pred;
		nouv->succ = l->ec;
		//Mise a jour des chainages des voisins
		(l->ec->pred)->succ = nouv;
		l->ec->pred = nouv;
		//On se positionne sur le nouvel element
		l->ec = nouv;
	}
}

int taille(t_liste_collision* l){
	int t=0;
	for(en_tete(l);!hors_liste(l);suivant(l))
		t++;
	return t;
}

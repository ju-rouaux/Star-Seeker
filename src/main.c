#include <stdlib.h>

#include <stdio.h>

#include "liste.h"


int main() {


    t_liste * liste = malloc(sizeof(t_liste));

    init_liste(liste);

    ajout_droit(liste, 0);
    ajout_droit(liste, 1);
    ajout_gauche(liste,-1);
    ajout_gauche(liste,-2);
    ajout_droit(liste,5);
    en_tete(liste);
    oter_elt(liste);

    en_queue(liste);
    oter_elt(liste);

    affichage_liste(liste);

    return 0;
}

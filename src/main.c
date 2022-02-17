#include <stdlib.h>

#include <stdio.h>

#include "liste.h"


int main() {


    t_liste * liste = malloc(sizeof(t_liste));

    init_liste(liste);

    ajout_droit(liste, "test1");
    ajout_droit(liste, "test2");
    ajout_gauche(liste,"-test1");
    ajout_gauche(liste,"-test2");
    ajout_droit(liste,"test3");
    // en_tete(liste);
    // oter_elt(liste);

    // en_queue(liste);
    // oter_elt(liste);

    affichage_liste(liste);

    return 0;
}

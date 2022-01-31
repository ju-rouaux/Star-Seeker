#include <stdlib.h>

#include <stdio.h>

#include "liste.h"

int main() {
    liste_t MaListe;

    init_liste( & MaListe);

    pushfront_liste( & MaListe, 10);
    pushback_liste( & MaListe, 20);
    pushback_liste( & MaListe, 40);
    pushback_liste( & MaListe, 50);

    display_liste(MaListe);
    printf("\n");
    remove_by_index( & MaListe, 2);
    printf("\n");
    display_liste(MaListe);
    printf("\n");
    clear_liste( & MaListe);


    return 0;
}

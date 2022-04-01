#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <generation_noms.h>
#include <generation_niveau.h>


void test_nom_planete(int taille_mot){

    srand(time(NULL));

    for (int i = 0; i < 15; i++){



        printf("%s \n", creer_nom(taille_mot));
    }


    int nb = 10;
    char noms_planetes[nb][10];
    
    creer_noms_planetes("zizi", nb, noms_planetes);

}
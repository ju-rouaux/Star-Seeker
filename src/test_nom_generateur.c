#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <noms_generateur.h>
#include <generation_niveau.h>


void test_nom_planete(int taille_mot){

    srand(time(NULL));

    for (int i = 0; i < 15; i++){



        printf("%s \n", creer_nom_galaxie(taille_mot));
    }

}
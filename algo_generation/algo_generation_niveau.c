/**
 * \file algo_generation_niveau.c
 * 
 * \brief Test de création de génération aléatoire de niveau (planète)
 *
 * \author camille
 *  
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>


#define LONGUEUR_NIVEAU_MAX 20
#define HAUTEUR_NIVEAU_MAX 20

// Cases du niveau
#define VIDE 0
#define SALLE -1

//Pourcentages de génération des salles
#define POURCENTAGE_DE_SALLES_GLOBAL 25

#define CHANCE_GEN_SALLE_8_VOISINES_LIBRES 100
#define CHANCE_GEN_SALLE_7_VOISINES_LIBRES 70
#define CHANCE_GEN_SALLE_6_VOISINES_LIBRES 40
#define CHANCE_GEN_SALLE_5_VOISINES_LIBRES 20
#define CHANCE_GEN_SALLE_4_VOISINES_LIBRES 20
#define CHANCE_GEN_SALLE_3_VOISINES_LIBRES 20
#define CHANCE_GEN_SALLE_2_VOISINES_LIBRES 1
#define CHANCE_GEN_SALLE_1_VOISINE_LIBRE 1
#define CHANCE_GEN_SALLE_0_VOISINE_LIBRE 0

#define NOMBRE_VOISINES_DISPO_NOUVELLE_SALLE_MIN 5


//Probabilités pour les indentifications de salles
#define CHANCE_DE_GENERER_EXTENSION_DE_ID_DE_SALLE 15



void afficher_niv(int niv[LONGUEUR_NIVEAU_MAX][HAUTEUR_NIVEAU_MAX]){

    for (int i = 0; i < LONGUEUR_NIVEAU_MAX; i++){
     
     
        for (int j = 0; j < HAUTEUR_NIVEAU_MAX; j++){

            switch(niv[i][j]){

                case VIDE : printf("0 "); break;
                case SALLE : printf("+"); break;
                default : printf("%d ", niv[i][j]);

            } 

        }

        printf("\n");

    }

}

int de(int nbFaces){
    //Dé à nbFaces faces
    return rand() % nbFaces + 1;
}

int coordonnees_valides(int i, int j){
    //Renvoie VRAI si les coordonnées sont valides

    if(i >= 0 && i < LONGUEUR_NIVEAU_MAX && j >= 0 && j < HAUTEUR_NIVEAU_MAX)
        return 1;

    return 0;

}

int nb_salles_adjacentes_dispo(int niv[LONGUEUR_NIVEAU_MAX][HAUTEUR_NIVEAU_MAX], int i, int j, int compterDiagonales){
    //Renvoie le nombre de salles dispos à côté de (i ; j)
    //compterDiagonales détermine si l'on compte les voisines en diagonale (1) ou pas

    int cpt_salles = 0;

    if( (coordonnees_valides(i+1, j) && niv[i+1][j] == VIDE ))
        cpt_salles++;

    if( (coordonnees_valides(i-1, j) && niv[i-1][j] == VIDE ))
        cpt_salles++;

    if( (coordonnees_valides(i, j+1) && niv[i][j+1] == VIDE ))
        cpt_salles++;

    if( (coordonnees_valides(i, j-1) && niv[i][j-1] == VIDE ))
        cpt_salles++;

    if(compterDiagonales == 1){
     
        if( (coordonnees_valides(i+1, j+1) && niv[i+1][j+1] == VIDE ))
            cpt_salles++;

        if( (coordonnees_valides(i-1, j-1) && niv[i-1][j] == VIDE ))
            cpt_salles++;

        if( (coordonnees_valides(i-1, j+1) && niv[i][j+1] == VIDE ))
            cpt_salles++;

        if( (coordonnees_valides(i+1, j-1) && niv[i][j-1] == VIDE ))
            cpt_salles++;
    }

    return cpt_salles;
}

int ajout_salle_adjacente(int niv[LONGUEUR_NIVEAU_MAX][HAUTEUR_NIVEAU_MAX], int i, int j){
    //Crée une nouvelle salle adjacente positionnée aléatoirement à celle passée en paramètre.
    //Ne vérifie pas si les coordonnées passées en paramètre correspondent à une salle.


    
    int direction = rand() % 4;

    for(int directionMax = direction + 4; direction < directionMax; direction++){

        if(i != LONGUEUR_NIVEAU_MAX -1 && i != 0 && j != HAUTEUR_NIVEAU_MAX -1 && j != 0 && niv[ i + (direction % 4 == 0) - (direction % 4 == 1) ][j + (direction % 4 == 2) - (direction % 4 == 3)] == VIDE && nb_salles_adjacentes_dispo(niv, i + (direction % 4 == 0) - (direction % 4 == 1), j + (direction % 4 == 2) - (direction % 4 == 3), 1) > NOMBRE_VOISINES_DISPO_NOUVELLE_SALLE_MIN){
            niv[ i + (direction % 4 == 0) - (direction % 4 == 1) ][j + (direction % 4 == 2) - (direction % 4 == 3)] = SALLE;
            return 1;
        }
 

    }

    return 0;

}

int compterSalle(int niv[LONGUEUR_NIVEAU_MAX][HAUTEUR_NIVEAU_MAX]){


    int cpt = 0;

    for (int i = 0; i < LONGUEUR_NIVEAU_MAX; i++){
     
     
        for (int j = 0; j < HAUTEUR_NIVEAU_MAX; j++){

            if(niv[i][j] != 0)
                cpt++;

        }

    }



    return cpt;
}



void identificationSalles(int niv[LONGUEUR_NIVEAU_MAX][HAUTEUR_NIVEAU_MAX]){


    int id = 1;

    for(int i = 0; i < LONGUEUR_NIVEAU_MAX; i++){

        for(int j = 0; j < HAUTEUR_NIVEAU_MAX; j++){

            if(niv[i][j] == SALLE){

                //Probable ajout d'une extension de salle depuis la salle du haut 
                if (de(100) < CHANCE_DE_GENERER_EXTENSION_DE_ID_DE_SALLE && niv[i][j-1] != VIDE)
                    niv[i][j] = niv[i][j-1];
                
                //Probable ajout d'une extension de salle depuis la salle de gauche
                else if (de(100) < CHANCE_DE_GENERER_EXTENSION_DE_ID_DE_SALLE && niv[i-1][j] != VIDE)
                    niv[i][j] = niv[i-1][j];
                
                else 
                    niv[i][j] = id++;

            }


        }

    }





}





void init_niveau(int niv[LONGUEUR_NIVEAU_MAX][HAUTEUR_NIVEAU_MAX]){

    // Fonction qui initialise la matrice niv[][] avec un niveau aléatoirement généré

    for (int i = 0; i < LONGUEUR_NIVEAU_MAX; i++)
        for (int j = 0; j < HAUTEUR_NIVEAU_MAX; j++)
            niv[i][j] = VIDE;

    
    niv[LONGUEUR_NIVEAU_MAX/2][HAUTEUR_NIVEAU_MAX/2] = 1;


    

    int nbMaxSalles = LONGUEUR_NIVEAU_MAX * HAUTEUR_NIVEAU_MAX * POURCENTAGE_DE_SALLES_GLOBAL / 100;    
   
    int nbSalles = 1;

    while(nbSalles < nbMaxSalles){


        int salle = 0;
        int i, j;

        
        int chancesSalle[9] = {CHANCE_GEN_SALLE_0_VOISINE_LIBRE, CHANCE_GEN_SALLE_1_VOISINE_LIBRE, CHANCE_GEN_SALLE_2_VOISINES_LIBRES, CHANCE_GEN_SALLE_3_VOISINES_LIBRES, CHANCE_GEN_SALLE_4_VOISINES_LIBRES, CHANCE_GEN_SALLE_5_VOISINES_LIBRES, CHANCE_GEN_SALLE_6_VOISINES_LIBRES, CHANCE_GEN_SALLE_7_VOISINES_LIBRES, CHANCE_GEN_SALLE_8_VOISINES_LIBRES};

        while(salle == 0){


            i = rand() % LONGUEUR_NIVEAU_MAX;
            j = rand() % HAUTEUR_NIVEAU_MAX;

           

            if (niv[i][j] != VIDE){



                if(de(100) < chancesSalle[nb_salles_adjacentes_dispo(niv, i, j, 1)] && nb_salles_adjacentes_dispo(niv, i, j, 0) > 0)
                    salle = 1;


            }

           
        }

       
        nbSalles += ajout_salle_adjacente(niv, i, j);

    }


}






void main(){

    srand(time(NULL));

    
    int niv[LONGUEUR_NIVEAU_MAX][HAUTEUR_NIVEAU_MAX];


   

    init_niveau(niv);
    afficher_niv(niv);

    identificationSalles(niv);

    printf("\n%d\n", compterSalle(niv));

    afficher_niv(niv);

}
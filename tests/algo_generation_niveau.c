/**
 * \file 
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


#define LONGUEUR_NIVEAU_MAX 21
#define HAUTEUR_NIVEAU_MAX 21

// Cases du niveau
#define VIDE 0
#define SALLE 1

//Pourcentages de génération des salles
#define POURCENTAGE_DE_SALLES_GLOBAL 10

#define CHANCE_GEN_SALLE_8_VOISINES_LIBRES 100
#define CHANCE_GEN_SALLE_7_VOISINES_LIBRES 70
#define CHANCE_GEN_SALLE_6_VOISINES_LIBRES 10
#define CHANCE_GEN_SALLE_5_VOISINES_LIBRES 2
#define CHANCE_GEN_SALLE_4_VOISINES_LIBRES 0
#define CHANCE_GEN_SALLE_3_VOISINES_LIBRES 0
#define CHANCE_GEN_SALLE_2_VOISINES_LIBRES 0
#define CHANCE_GEN_SALLE_1_VOISINE_LIBRE 0
#define CHANCE_GEN_SALLE_0_VOISINE_LIBRE 0




void afficher_niv(int niv[LONGUEUR_NIVEAU_MAX][HAUTEUR_NIVEAU_MAX]){

    for (int i = 0; i < LONGUEUR_NIVEAU_MAX; i++){
     
     
        for (int j = 0; j < HAUTEUR_NIVEAU_MAX; j++){

            switch(niv[i][j]){

                case VIDE : printf(" "); break;
                case SALLE : printf("@"); break;
                default : printf("?");

            } 

        }

        printf("\n");

    }

}



int coordonnees_valides(int i, int j){
    //Renvoie VRAI si les coordonnées sont valides

    if(i >= 0 && i < LONGUEUR_NIVEAU_MAX && j >= 0 && j < HAUTEUR_NIVEAU_MAX)
        return 1;

    return 0;

}

int nb_salles_adjacentes_dispo(int niv[LONGUEUR_NIVEAU_MAX][HAUTEUR_NIVEAU_MAX], int i, int j){
    //Renvoie le nombre de salles dispos à côté de (i ; j)

    int cpt_salles = 0;

    if( (!coordonnees_valides(i+1, j) || niv[i+1][j] == VIDE ))
        cpt_salles++;

    if( (!coordonnees_valides(i-1, j) || niv[i-1][j] == VIDE ))
        cpt_salles++;

    if( (!coordonnees_valides(i, j+1) || niv[i][j+1] == VIDE ))
        cpt_salles++;

    if( (!coordonnees_valides(i, j-1) || niv[i][j-1] == VIDE ))
        cpt_salles++;

    if( (!coordonnees_valides(i+1, j+1) || niv[i+1][j+1] == VIDE ))
        cpt_salles++;

    if( (!coordonnees_valides(i-1, j-1) || niv[i-1][j] == VIDE ))
        cpt_salles++;

    if( (!coordonnees_valides(i-1, j+1) || niv[i][j+1] == VIDE ))
        cpt_salles++;

    if( (!coordonnees_valides(i+1, j-1) || niv[i][j-1] == VIDE ))
        cpt_salles++;

    //printf("%d ", cpt_salles);

    return cpt_salles;
}

void ajout_salle_adjacente(int niv[LONGUEUR_NIVEAU_MAX][HAUTEUR_NIVEAU_MAX], int i, int j){
    //Crée une nouvelle salle adjacente positionnée aléatoirement à celle passée en paramètre.
    //Ne vérifie pas si les coordonnées passées en paramètre correspondent à une salle.

    int direction;

    while(1){

        direction = rand() % 4;

        switch (direction){

            case 0 : 
                if(i != LONGUEUR_NIVEAU_MAX -1 && niv[i+1][j] == VIDE){
                    niv[i+1][j] = SALLE;
                    return;
                }
                break;

            case 1 : 
                if(i != 0 && niv[i-1][j] == VIDE){
                    niv[i-1][j] = SALLE;
                    return;
                }
                break;

            case 2 : 
                if(j != HAUTEUR_NIVEAU_MAX -1 && niv[i][j+1] == VIDE){
                    niv[i][j+1] = SALLE;
                    return;
                }
                break;

            case 3 : 
                if(j != 0 && niv[i][j-1] == VIDE){
                    niv[i][j-1] = SALLE;
                    return;
                }
                break;
        }


    }

}



void init_niveau(int niv[LONGUEUR_NIVEAU_MAX][HAUTEUR_NIVEAU_MAX]){

    // Fonction qui initialise la matrice niv[][] avec un niveau aléatoirement généré

    for (int i = 0; i < LONGUEUR_NIVEAU_MAX; i++)
        for (int j = 0; j < HAUTEUR_NIVEAU_MAX; j++)
            niv[i][j] = VIDE;

    
    niv[LONGUEUR_NIVEAU_MAX/2][HAUTEUR_NIVEAU_MAX/2] = 2;


    

    int nbMaxSalles = LONGUEUR_NIVEAU_MAX * HAUTEUR_NIVEAU_MAX * POURCENTAGE_DE_SALLES_GLOBAL / 100;    
   

    for(int nbSalles = 1 ; nbSalles < nbMaxSalles; nbSalles++){


        int salle = 0;
        int i, j;

        

        while(salle == 0){

            i = rand() % LONGUEUR_NIVEAU_MAX;
            j = rand() % HAUTEUR_NIVEAU_MAX;

            if (niv[i][j] != VIDE){


                int chancesSalle[9] = {CHANCE_GEN_SALLE_0_VOISINE_LIBRE, CHANCE_GEN_SALLE_1_VOISINE_LIBRE, CHANCE_GEN_SALLE_2_VOISINES_LIBRES, CHANCE_GEN_SALLE_3_VOISINES_LIBRES, CHANCE_GEN_SALLE_4_VOISINES_LIBRES, CHANCE_GEN_SALLE_5_VOISINES_LIBRES, CHANCE_GEN_SALLE_6_VOISINES_LIBRES, CHANCE_GEN_SALLE_7_VOISINES_LIBRES, CHANCE_GEN_SALLE_8_VOISINES_LIBRES};

                int D100 = rand() % 100 + 1;
                if(D100 < chancesSalle[nb_salles_adjacentes_dispo(niv, i, j)])
                    salle = 1;       
        
                
            }
        }

       

        ajout_salle_adjacente(niv, i, j);      

    }


}






void main(){

    srand(time(NULL));

    
    int niv[LONGUEUR_NIVEAU_MAX][HAUTEUR_NIVEAU_MAX];


    init_niveau(niv);
    afficher_niv(niv);


}
/**
 * \file generation_niveau.c
 * 
 * \brief Génération d'un niveau : l'agencement des salles et leurs ids
 *
 * \author Camille
 *  
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

#include <generation_niveau.h>
#include <outils.h>



/**
 *  
 * \param i Coordonnée i
 * \param j Coordonnée j
 * 
 * \return VRAI seulement si les coordonnées sont à l'intérieur de la matrice
*/
static int coordonnees_valides(int i, int j){

    if(i >= 0 && i < LONGUEUR_NIVEAU_MAX && j >= 0 && j < HAUTEUR_NIVEAU_MAX)
        return 1;

    return 0;

}



/**
 * \brief Compter les salles VIDE à côté de la salle (i, j). Possibilité de compter les voisines diagonales ou pas 
 * 
 * \param niv Matrice principale
 * \param i Coordonnée i
 * \param j Coordonnée j
 * \param compterDiagonales Si égal à 0, ne pas compter les voisines diagonales. Toute autre valeur les prend en compte.
 * 
 * \return Le nombre de cases VIDE adjacentes à la case (i, j) :
 */
static int nb_salles_adjacentes_dispo(int niv[LONGUEUR_NIVEAU_MAX][HAUTEUR_NIVEAU_MAX], int i, int j, int compterDiagonales){

    int cpt_salles = 0;

    if( (coordonnees_valides(i+1, j) && niv[i+1][j] == VIDE ))
        cpt_salles++;

    if( (coordonnees_valides(i-1, j) && niv[i-1][j] == VIDE ))
        cpt_salles++;

    if( (coordonnees_valides(i, j+1) && niv[i][j+1] == VIDE ))
        cpt_salles++;

    if( (coordonnees_valides(i, j-1) && niv[i][j-1] == VIDE ))
        cpt_salles++;

    if(compterDiagonales != 0){
     
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



/**
 * 
 * \brief Crée une salle adjacente à un côté aléatoire de (i, j).
 * 
 * Crée une nouvelle salle, adjacente à un côté aléatoire (haut, bas, gauche ou droite) de la salle aux coordonnées (i, j).
 * Prise en compte de NOMBRE_VOISINES_DISPO_NOUVELLE_SALLE_MIN : Ne créera pas de nouvelle salle si son emplacement a trop de voisines non VIDE.
 * Attention : la fonction ne vérifie pas si les coordonnées passées en paramètre correspondent à une salle.
 * 
 * \param niv Matrice principale
 * \param i Coordonnée i
 * \param j Coordonnée j
 * 
 * \return VRAI seulement si une nouvelle salle a été créée.
 */
static int ajout_salle_adjacente(int niv[LONGUEUR_NIVEAU_MAX][HAUTEUR_NIVEAU_MAX], int i, int j){
    
    int direction = rand() % 4;

    for(int directionMax = direction + 4; direction < directionMax; direction++){

        if(i != LONGUEUR_NIVEAU_MAX -1 && i != 0 && j != HAUTEUR_NIVEAU_MAX -1 && j != 0 && niv[ i + (direction % 4 == 0) - (direction % 4 == 1) ][j + (direction % 4 == 2) - (direction % 4 == 3)] == VIDE && nb_salles_adjacentes_dispo(niv, i + (direction % 4 == 0) - (direction % 4 == 1), j + (direction % 4 == 2) - (direction % 4 == 3), 1) > NOMBRE_VOISINES_DISPO_NOUVELLE_SALLE_MIN){
            niv[ i + (direction % 4 == 0) - (direction % 4 == 1) ][j + (direction % 4 == 2) - (direction % 4 == 3)] = SALLE;
            return 1;
        }
 

    }

    return 0;

}


/**
 * \brief Attribue un identifiant entier à chaque salle. En donnant le même id à plusieurs salles adjacentes, on les fusionne.
 *
 * \param niv La matrice du niveau
 *
 */
static void identificationSalles(int niv[LONGUEUR_NIVEAU_MAX][HAUTEUR_NIVEAU_MAX]){

    int id = 1;

    for(int j = 0; j < HAUTEUR_NIVEAU_MAX; j++){

        for(int i = 0; i < LONGUEUR_NIVEAU_MAX; i++){

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


/**
 * \brief initialise la matrice avec un niveau aléatoirement généré
 * 
 * \param niv La matrice de sortie
 * 
 */
static void init_niveau(int niv[LONGUEUR_NIVEAU_MAX][HAUTEUR_NIVEAU_MAX]){

    for (int i = 0; i < LONGUEUR_NIVEAU_MAX; i++)
        for (int j = 0; j < HAUTEUR_NIVEAU_MAX; j++)
            niv[i][j] = VIDE;

    niv[LONGUEUR_NIVEAU_MAX/2][HAUTEUR_NIVEAU_MAX/2] = SALLE;

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


/**
 * \brief Transforme arbitrairement un mot (lettres) en seed (entier)
 * 
 * \param mot chaine de caractères en entrée
 * 
 * \return La seed correspondant au mot.
 */
static int seed_depuis_mot(const char * mot){

    int seed = 0;

    for(int i = 0; i < strlen(mot); i++)
        seed = seed*100 + tolower(*(mot + i));
    

    return seed;

}



/**
* \brief génère une couleur aléatoire en évitant les nuances de gris.
*
* \param couleur La structure de retour
*/
void couleur_aleatoire(t_couleurRVB * couleur){


    couleur->rouge = rand() % 255;
    couleur->vert = rand() % 255;
    
    if (couleur->rouge % 2)
        couleur->bleu = 255 - couleur->rouge;
    else
        couleur->bleu = 255 - couleur->vert;


}



void detruire_niveau(niveau_informations_t * niveau){

    free(niveau);
}


/**
 * \brief Fonction principale : crée le niveau et l'écrit dans un fichier
 * 
 * \param nom_fichier Nom du fichier de sortie
 * \param nom_planete Nom associé à un niveau unique : il génère la seed
 */
void creer_niveau(const char * nom_fichier, const char * nom_planete){

    //Initialisation de la seed
    unsigned int seed = seed_depuis_mot(nom_planete);
    srand(seed);


    //Création de la map

    niveau_informations_t * niveau = malloc(sizeof(niveau_informations_t));
    init_niveau(niveau->matrice);
    identificationSalles(niveau->matrice);


    //Couleur
    t_couleurRVB * couleur = malloc(sizeof(t_couleurRVB));
    couleur_aleatoire(couleur);
    niveau->rouge = couleur->rouge;
    niveau->vert = couleur->vert;
    niveau->bleu = couleur->bleu;
    free(couleur);

    niveau->hauteur = HAUTEUR_NIVEAU_MAX;
    niveau->longueur = LONGUEUR_NIVEAU_MAX;


}
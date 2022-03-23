/**
 * \file generation_niveau.c
 * 
 * \brief Génération d'un niveau : l'agencement des salles et leurs ids
 *
 * \author Camille REMOUÉ
 *  
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

#include <generation_entites.h>
#include <outils.h>
#include <generation_niveau.h>



/**
 *  
 * \param i Coordonnée i
 * \param j Coordonnée j
 * 
 * \return VRAI seulement si les coordonnées sont à l'intérieur de la matrice
*/
static int coordonnees_valides(int i, int j){

    if(i >= 0 && i < HAUTEUR_NIVEAU_MAX && j >= 0 && j < LONGUEUR_NIVEAU_MAX)
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
static int nb_salles_adjacentes_dispo(int niv[HAUTEUR_NIVEAU_MAX][LONGUEUR_NIVEAU_MAX], int i, int j, int compterDiagonales){

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

        if( (coordonnees_valides(i-1, j-1) && niv[i-1][j-1] == VIDE ))
            cpt_salles++;

        if( (coordonnees_valides(i-1, j+1) && niv[i-1][j+1] == VIDE ))
            cpt_salles++;

        if( (coordonnees_valides(i+1, j-1) && niv[i+1][j-1] == VIDE ))
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
static int ajout_salle_adjacente(int niv[HAUTEUR_NIVEAU_MAX][LONGUEUR_NIVEAU_MAX], int i, int j){
    
    int direction = rand() % 4;

    for(int directionMax = direction + 4; direction < directionMax; direction++){

        if(i != (HAUTEUR_NIVEAU_MAX - 1) && i != 0 && j != (LONGUEUR_NIVEAU_MAX - 1) && j != 0 && 
        niv[ i + (direction % 4 == 0) - (direction % 4 == 1) ][j + (direction % 4 == 2) - (direction % 4 == 3)] == VIDE && 
        nb_salles_adjacentes_dispo(niv, i + (direction % 4 == 0) - (direction % 4 == 1), j + (direction % 4 == 2) - (direction % 4 == 3), 1) > NOMBRE_VOISINES_DISPO_NOUVELLE_SALLE_MIN)
        {
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
static void identificationSalles(int niv[HAUTEUR_NIVEAU_MAX][LONGUEUR_NIVEAU_MAX]){

    int id = 1;

    for(int i = 0; i < HAUTEUR_NIVEAU_MAX; i++){

        for(int j = 0; j < LONGUEUR_NIVEAU_MAX; j++){

            if(niv[i][j] == SALLE){

                //Probable ajout d'une extension de salle depuis la salle du haut 
                if (de(100) < CHANCE_DE_GENERER_EXTENSION_DE_ID_DE_SALLE && coordonnees_valides(i-1, j) && niv[i-1][j] != VIDE)
                    niv[i][j] = niv[i-1][j];

                //Probable ajout d'une extension de salle depuis la salle de gauche
                else if (de(100) < CHANCE_DE_GENERER_EXTENSION_DE_ID_DE_SALLE && coordonnees_valides(i, j-1) && niv[i][j-1] != VIDE)
                    niv[i][j] = niv[i][j-1];

                else 
                    niv[i][j] = id++;

            }


        }

    }
}



/**
 * \brief Attribue à i_fin et j_fin les coordonnées de la salle finale du niveau
 *  
 * \param i_fin
 * \param j_fin 
 *  
 */
static void definir_coordonnees_salle_de_fin(const int niv[HAUTEUR_NIVEAU_MAX][LONGUEUR_NIVEAU_MAX], int * i_fin, int * j_fin){

    *i_fin = HAUTEUR_NIVEAU_MAX/2;
    *j_fin = LONGUEUR_NIVEAU_MAX/2;

    while(*i_fin != HAUTEUR_NIVEAU_MAX/2 && *j_fin != LONGUEUR_NIVEAU_MAX/2 && niv[*i_fin ][*j_fin] == VIDE){

        *i_fin = rand() % HAUTEUR_NIVEAU_MAX;
        *j_fin = rand() % LONGUEUR_NIVEAU_MAX;

    }


}



/**
 * \brief initialise la matrice avec un niveau aléatoirement généré
 * 
 * \param niv La matrice de sortie
 * 
 */
static void init_niveau(int niv[HAUTEUR_NIVEAU_MAX][LONGUEUR_NIVEAU_MAX]){

    for (int i = 0; i < HAUTEUR_NIVEAU_MAX; i++)
        for (int j = 0; j < LONGUEUR_NIVEAU_MAX; j++)
            niv[i][j] = VIDE;

    

    // SALLE DE DÉBUT
    niv[HAUTEUR_NIVEAU_MAX/2][LONGUEUR_NIVEAU_MAX/2] = SALLE;

    int nbMaxSalles = HAUTEUR_NIVEAU_MAX * LONGUEUR_NIVEAU_MAX * POURCENTAGE_DE_SALLES_GLOBAL / 100;
    int nbSalles = 1;

    while(nbSalles < nbMaxSalles){


        int salle = 0;
        int i, j;

        int chancesSalle[9] = {CHANCE_GEN_SALLE_0_VOISINE_LIBRE, CHANCE_GEN_SALLE_1_VOISINE_LIBRE, CHANCE_GEN_SALLE_2_VOISINES_LIBRES, CHANCE_GEN_SALLE_3_VOISINES_LIBRES, CHANCE_GEN_SALLE_4_VOISINES_LIBRES, CHANCE_GEN_SALLE_5_VOISINES_LIBRES, CHANCE_GEN_SALLE_6_VOISINES_LIBRES, CHANCE_GEN_SALLE_7_VOISINES_LIBRES, CHANCE_GEN_SALLE_8_VOISINES_LIBRES};

        while(salle == 0){


            i = rand() % HAUTEUR_NIVEAU_MAX;
            j = rand() % LONGUEUR_NIVEAU_MAX;

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
int seed_depuis_mot(const char * mot){

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
static void couleur_aleatoire(t_couleurRVB * couleur){


    couleur->rouge = rand() % 255;
    couleur->vert = rand() % 255;
    
    if (couleur->rouge % 2)
        couleur->bleu = 255 - couleur->rouge;
    else
        couleur->bleu = 255 - couleur->vert;


}


/**
 * \brief Libère la mémoire allouée à une information de niveau.
 * 
 * \param niveau L'adresse de la structure à libérer
 */
void detruire_niveau_info(niveau_informations_t ** niveau){
    if(*niveau != NULL)
    {
        if((*niveau)->liste_infos_entites != NULL)
        {
            for(int i = 0; i < (*niveau)->nb_infos_entite; i++)
                detruireInfosEntites(&((*niveau)->liste_infos_entites[i]));

            free((*niveau)->liste_infos_entites);
        }
        free(*niveau);
    }
    *niveau = NULL;
}


/**
 * \brief Fonction principale : crée le niveau et l'écrit dans une structure
 * 
 * \param nom_planete Nom associé à un niveau unique : il génère la seed
 */
niveau_informations_t * creer_niveau_info(const char * nom_planete){

    int indice_difficulte = 2; //!!! A CALCULER

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
    

    niveau->i_dep = LONGUEUR_NIVEAU_MAX/2;
    niveau->j_dep = HAUTEUR_NIVEAU_MAX/2;

    definir_coordonnees_salle_de_fin(niveau->matrice, &(niveau->i_dep), &(niveau->j_dep));
    
    for(int i = 0; i < HAUTEUR_NIVEAU_MAX; i++)
    {
        for(int j = 0; j < LONGUEUR_NIVEAU_MAX; j++)
            printf("%3i ", niveau->matrice[i][j]);
        putchar('\n');
    }

    niveau->liste_infos_entites = NULL;
    niveau->nb_infos_entite = 0;
    genererEntites(indice_difficulte, (int*) niveau->matrice, HAUTEUR_NIVEAU_MAX, LONGUEUR_NIVEAU_MAX, &niveau->liste_infos_entites, &niveau->nb_infos_entite);

    return niveau;
}
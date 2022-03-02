#ifndef _JEU_GENERATION_NIVEAU_
#define _JEU_GENERATION_NIVEAU_

/**
 * \file generation_niveau.h
 * 
 * \brief Librairie de generation.c
 *
 * \author Camille REMOUÉ
 *  
 */



#ifndef _JEU_GENERATION_NIVEAU_
#define _JEU_GENERATION_NIVEAU_


#define LONGUEUR_NIVEAU_MAX 25
#define HAUTEUR_NIVEAU_MAX 25

//Cases du niveau
#define VIDE 0
#define SALLE -1

//Pourcentages de génération des salles
#define POURCENTAGE_DE_SALLES_GLOBAL 20


#define CHANCE_GEN_SALLE_8_VOISINES_LIBRES 100
#define CHANCE_GEN_SALLE_7_VOISINES_LIBRES 70
#define CHANCE_GEN_SALLE_6_VOISINES_LIBRES 40
#define CHANCE_GEN_SALLE_5_VOISINES_LIBRES 20
#define CHANCE_GEN_SALLE_4_VOISINES_LIBRES 10
#define CHANCE_GEN_SALLE_3_VOISINES_LIBRES 5
#define CHANCE_GEN_SALLE_2_VOISINES_LIBRES 1
#define CHANCE_GEN_SALLE_1_VOISINE_LIBRE 1
#define CHANCE_GEN_SALLE_0_VOISINE_LIBRE 0

#define NOMBRE_VOISINES_DISPO_NOUVELLE_SALLE_MIN 4


//Probabilité qu'une salle sans id prenne l'id d'une salle adjacente au lieu d'un nouvel id
//En d'autres termes, probabilité de générer une extension de salle au lieu d'une nouvelle salle
#define CHANCE_DE_GENERER_EXTENSION_DE_ID_DE_SALLE 15


/**
 * \struct t_couleurRVB
 * \brief Structure qui stocke une couleur décomposée en RVB. 
 * Chaque int est compris entre 0 et 255 inclus.
*/
typedef struct {

    int rouge;
    int vert;
    int bleu;

} t_couleurRVB;


/**
 * \struct niveau_base_t  
 *
 * \brief Toutes les informations relatives au stockage d'un niveau
 * 
 */
typedef struct {

    int hauteur;
    int longueur;

    int rouge;
    int vert;
    int bleu;

    int matrice[LONGUEUR_NIVEAU_MAX][HAUTEUR_NIVEAU_MAX];



    //Positions des salles

    int i_dep;
    int j_dep;
    int i_fin;
    int j_fin;

} niveau_informations_t;



niveau_informations_t * creer_niveau(const char * nom_planete);
void couleur_aleatoire(t_couleurRVB * couleur);


#endif // _JEU_GENERATION_NIVEAU

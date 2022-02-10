/**
 * \file algo_generation_niveau.c
 * 
 * \brief Test de création de génération aléatoire de niveau (planète)
 *
 * \author camille
 *  
 */



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



void creer_niveau(const char * nom_fichier, const char * nom_planete);


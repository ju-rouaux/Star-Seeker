/**
 * \file generation_niveau.h
 * 
 * \brief Librairie de generation
 *
 * \author Camille Remoué
 *  
 */

#include <generation_entites.h>

#ifndef _JEU_GENERATION_NIVEAU_
#define _JEU_GENERATION_NIVEAU_





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

    int * matrice; /**< La matrice du niveau*/
    int hauteur; /**< La hauteur de la matrice*/
    int longueur; /**< La largeur de la matrice*/

    int rouge; /**< Entier entre 0 et 255 representant la quantité de rouge pour le rendu du niveau */
    int vert; /**< Entier entre 0 et 255 representant la quantité de vert pour le rendu du niveau */
    int bleu; /**< Entier entre 0 et 255 representant la quantité de bleu pour le rendu du niveau */

    t_info_entites ** liste_infos_entites; /**< Liste des entités présentes dans le niveau */
    int nb_infos_entite; /**< Nombre de liste_infos_entites */

    //Positions des salles de départ et de fin

    int i_dep; /**< Coordonnée i (hauteur) de la salle initiale */
    int j_dep; /**< Coordonnée j (longueur) de la salle initiale*/
    int i_fin; /**< Coordonnée i (hauteur) de la salle de fin*/
    int j_fin; /**< Coordonnée j (longueur) de la salle de fin*/

    char * nom_planete;/**< Nom de la planète*/

} niveau_informations_t;


niveau_informations_t * creer_niveau_info(char * nom_planete, int indice_difficulte);
void detruire_niveau_info(niveau_informations_t ** niveau);
int seed_depuis_mot(const char * mot);

#endif // _JEU_GENERATION_NIVEAU

/**
 * \file interaction.h
 * 
 * \brief Entités supportant une interaction par le joueur.
 * 
 * \author Julien Rouaux
 */

#ifndef _JEU_INTERACTION_
#define _JEU_INTERACTION_

#include <entite.h>
#include <joueur.h>
#include <attaque.h>


/**
 * \enum e_type_inter
 * \brief Type des interactions disponibles.
 */
typedef enum
{
    VIE, ARME
} e_type_inter;


/**
 * \union data_inter
 * \brief Donnée sur l'interaction.
 */
typedef union
{
    int nb_pv; /**< Nombre de pv ajoutés au joueur si le type est VIE */
    e_nom_attaque attaque; /**< Attaque équipée au joueur si le type est ARME */
} data_inter;


/**
 * \struct t_interaction
 * \brief Modélise un objet déposé au sol pouvant être récupéré par le joueur
 */
typedef struct
{
    #include <attributs_entites.h>
    e_type_inter type_inter;/**< Coordonnée j (longueur) de la salle de fin*/
    data_inter data;
} t_interaction;


t_interaction * creerInteraction(e_type_inter type, float x, float y, data_inter data);
int interagir(t_interaction * interaction, t_joueur * joueur);


#endif //_JEU_INTERACTION_
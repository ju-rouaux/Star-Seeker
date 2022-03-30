/**
 * \file monstre.h
 * 
 * \brief Module de gestion des monstres.
 * 
 * \author Julien Rouaux
 */


#ifndef _JEU_MONSTRE_
#define _JEU_MONSTRE_

#include <SDL2/SDL.h>
#include <entite.h>
#include <attaque.h>

/**
 * \enum e_deplacement_monstre
 * \brief Type de déplacement pouvant être associé à un monstre, permet de définir
 * son comportement.
 */
typedef enum
{
    STATIQUE, VERS_J
} e_deplacement_monstre;


/**
 * \struct t_joueur
 * \brief Structure modélisant le joueur, hérite des attributs d'entité et de personnage.
 */
typedef struct s_monstre t_monstre;
struct s_monstre
{
    #include <attributs_personnages.h>
    e_deplacement_monstre deplacement;
};


t_monstre * creerMonstre(float x, float y, float vitesse, int pv, float taille, e_nom_attaque type_attaque, e_deplacement_monstre deplacement);


#endif //_JEU_MONSTRE_
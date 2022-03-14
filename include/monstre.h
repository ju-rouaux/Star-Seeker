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

typedef enum
{
    STATIQUE
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


#endif //_JEU_MONSTRE_
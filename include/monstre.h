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


/**
 * \struct t_joueur
 * \brief Structure modélisant le joueur, hérite des attributs d'entité et de personnage.
 */
typedef struct s_monstre t_monstre;
struct s_monstre
{
    #include <attributs_personnages.h>

    //Attaque équipée...

    //Méthode de déplacement équipée
    void (*deplacement)(t_monstre *, float, float);
    int cpt_deplacement; //Compteur pouvant être utilisé par le déplacement
};


#endif //_JEU_MONSTRE_
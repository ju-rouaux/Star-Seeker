/**
 * \file personnage.h
 * 
 * \brief Module 
 * 
 * \author Julien Rouaux
 */

#ifndef _JEU_PERSONNAGE_
#define _JEU_PERSONNAGE_

#include <entite.h>

/**
 * \struct t_personnage
 * \brief Modélise un personnage (joueur ou ennemi).
 */

typedef struct s_personnage t_personnage;
struct s_personnage
{
    #include <attributs_personnages.h>
} ;

#endif //_JEU_PERSONNAGE_
/**
 * \file particules.h
 * 
 * \brief Module de définition de particules
 * 
 * \author Julien Rouaux
 */

#ifndef _JEU_PARTICULES_
#define _JEU_PARTICULES_

#include <entite.h>

/**
 * \enum e_type_particule
 * \brief Les différents types de particules pouvant être générés
 */
typedef enum
{
    P_MORT, P_TOUCHE, P_XP, P_DASH
} e_type_particule;

/**
 * \struct t_particule
 * \brief Modélise une particule.
 */
typedef struct s_particule t_particule;
struct s_particule
{
    #include <attributs_entites.h>
    int duree_de_vie; /**< Temps en milisecondes avant l'auto-destruction de la particule */
    e_type_particule type_particule;/**< Le type de particule */
} ;

t_particule * creerParticule(e_type_particule type, float x, float y, SDL_Texture * texture);

#endif //_JEU_PARTICULES_
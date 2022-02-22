/**
 * \file entite.h
 * 
 * \brief Module de manipulation des entites.
 * 
 * Pour faciliter le développement, ce module permet l'affichage et
 * le déplacement automatique d'une entité selon ses paramètres.
 * 
 * \author Julien Rouaux
 */

#ifndef _JEU_ENTITE_
#define _JEU_ENTITE_

#include <moteur.h>
#include <animation.h> //Pour le champ animation d'attributs entites
//typedef struct s_animation t_animation;


/**
 * \enum e_type_entite
 * \brief Identifiant permettant de reconnaitre la nature d'une entité.
 */
typedef enum
{
    E_JOUEUR, E_MONSTRE, E_PROJECTILE
}e_type_entite;


/**
 * \struct t_entite
 * \brief Modélise une entité.
 */
typedef struct s_entite t_entite;
struct s_entite
{
    #include <attributs_entites.h>
} ;


int dessinerEntite(t_moteur * moteur, t_entite * entite);
int deplacerEntite(const t_moteur * moteur, t_entite * entite);


#endif //_JEU_ENTITE_
#ifndef _JEU_ENTITE_
#define _JEU_ENTITE_

#include <moteur.h>
#include <animation.h> //Pour l'include d'attributs_entites.h

typedef enum
{
    E_JOUEUR, E_MONSTRE, E_PROJECTILE
}e_type_entite;

typedef struct s_entite t_entite;
struct s_entite
{
    #include <attributs_entites.h>
} ;

int dessinerEntite(t_moteur * moteur, t_entite * entite);

#endif
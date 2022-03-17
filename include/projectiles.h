/**
 * \file projectiles.h
 * 
 * \brief Module de définition de projectiles
 * 
 * \author Julien Rouaux
 */

#ifndef _JEU_PROJECTILE_
#define _JEU_PROJECTILE_

#include <SDL2/SDL.h>
#include <entite.h>

typedef enum
{
    P_BALLE, P_BOULE_FEU, P_SNIPER, P_PLS
} e_type_projectile;

/**
 * \struct t_projectile
 * \brief Modélise une entité.
 */
typedef struct s_projectile t_projectile;
struct s_projectile
{
    #include <attributs_entites.h>
    e_type_entite cible; /**< Type d'entité prenant les degats si touché */
    int dommages; /**< Points de dégats infligés */
    int duree_de_vie; /**< Temps en milisecondes avant l'auto-destruction du projectile */
} ;

t_projectile * creerProjectile(e_type_projectile type, float x, float y, float direction_vx, float direction_vy, e_type_entite cible, SDL_Texture * texture);
void detruireProjectile(t_projectile ** projectile);

#endif //_JEU_PROJECTILE_
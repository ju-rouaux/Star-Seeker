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
#include <liste.h>

struct s_joueur;

/**
 * \enum e_type_projectile
 * \brief Les différents types de projectiles pouvant être générés
 */
typedef enum
{
    BALLE, BOULE_FEU, BOULET, SHURIKEN, TOURNER, SABRE
} e_type_projectile;

/**
 * \struct t_projectile
 * \brief Modélise un projectile.
 */
typedef struct s_projectile t_projectile;
struct s_projectile
{
    #include <attributs_entites.h>
    e_type_entite cible; /**< Type d'entité prenant les degats si touché */
    int dommages; /**< Points de dégats infligés */
    int duree_de_vie; /**< Temps en milisecondes avant l'auto-destruction du projectile */
} ;

int faireDegats(t_projectile * projectile, struct s_joueur * joueur, t_liste * liste);
t_projectile * creerProjectile(e_type_projectile type, float x, float y, float direction_vx, float direction_vy, e_type_entite cible, SDL_Texture * texture);
void detruireProjectile(t_projectile ** projectile);

#endif //_JEU_PROJECTILE_
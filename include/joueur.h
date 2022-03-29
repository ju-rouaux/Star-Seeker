/**
 * \file joueur.h
 * 
 * \brief Module de gestion du joueur.
 * 
 * \author Julien Rouaux
 */

#ifndef _JEU_JOUEUR_
#define _JEU_JOUEUR_


#include <SDL2/SDL.h>
#include <entite.h>
#include <personnage.h>
#include <attaque.h>

#define PROPORTION_JOUEUR 1.2 /**< Taille du joueur par rapport à la taille d'une tile */
#define VITESSE_JOUEUR_DEFAULT 6.5 /**< La vitesse du joueur par défaut */
#define PV_JOUEUR_DEFAULT 20 /**< Nombre de points de vie du joueur par défaut */

/**
 * \struct t_joueur_flags
 * \brief Structure contenant les entrées clavier/souris actives du joueur
 */
typedef struct
{
    //Déplacements
    int to_up;
    int to_down;
    int to_left;
    int to_right;
    int dash;

    //Actions
    int shooting;
    int interaction;

    //Overlay
    int map_shown;

} t_joueur_flags;


/**
 * \struct t_joueur
 * \brief Structure modélisant le joueur, hérite des attributs d'entité et de personnage.
 */
typedef struct s_joueur
{
    #include <attributs_personnages.h>
    t_joueur_flags * flags;

    int xp;
    int temps_restant_dash;
    int cooldown_dash;
} t_joueur;


t_joueur * creerJoueur(float x, float y, SDL_Texture * apparence);
void detruireJoueur(t_joueur ** joueur);


#endif //_JEU_JOUEUR_
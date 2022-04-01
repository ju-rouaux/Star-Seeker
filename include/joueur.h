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

    int to_up; /**< Déplacement vers le haut */
    int to_down; /**< Déplacement vers le bas */
    int to_left; /**< Déplacement vers la gauche */
    int to_right; /**< Déplacement vers la droite */
    int dash; /**< Esquive */
 
    //Actions

    int attack_up; /**< Attaque vers le haut */
    int attack_down; /**< Attaque vers le bas */
    int attack_left; /**< Attaque vers la gauche */
    int attack_right; /**< Attaque vers la droite */
    int interaction; /**< Récupération d'un objet au sol */

    //Overlay

    int map_shown; /**< Afficher la carte du niveau */

} t_joueur_flags;


/**
 * \struct t_joueur
 * \brief Structure modélisant le joueur, hérite des attributs d'entité et de personnage.
 */
typedef struct s_joueur
{
    #include <attributs_personnages.h>

    t_joueur_flags * flags; /**< Informations sur l'état du clavier du joueur */
    int xp; /**< Niveau d'expérience du joueur*/
    int temps_restant_dash;/** <Temps restant avant la fin d'une esquive */
    int cooldown_dash; /**< Temps restant avant la possibilité de pouvoir réaliser de nouveau une esquive */
} t_joueur;


t_joueur * creerJoueur(float x, float y, SDL_Texture * apparence);
void detruireJoueur(t_joueur ** joueur);


#endif //_JEU_JOUEUR_
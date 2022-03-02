/*


    EN DEVELOPPEMENT



*/

/**
 * \file attaque.h
 * 
 * \brief Module gérant les attaques des personnages
 * 
 * \author Julien Rouaux
 */

#ifndef _JEU_ATTAQUE_
#define _JEU_ATTAQUE_

#include <projectiles.h>


typedef enum
{
    DEMO
} e_nom_attaque;


/**
 * \struct t_attaque_tir
 * \brief Modélise une arme générant des projectiles.
 */
typedef struct
{
    //Définition de l'attaque de tir

    e_type_projectile type_projectile;
    int cooldown; /** Temps avant de pouvoir réutiliser l'attaque */
    int nb_salves; /** Nombre de salves */
    int nb_proj_salve; /** Nombre de projectiles par salves */
    int tir_interval; /** Temps entre le tir de chaque salve */

    //Variables pour l'exécution

    int nb_salves_restantes; /** Nombre de salves restantes */
    int temps_debut_attaque; /** Temps qu'il était au début de l'exécution de l'attaque */
} t_attaque_tir;


/**
 * \struct t_attaque_corps
 * \brief Modélise une arme de corps à corps.
 */
typedef struct
{
    int cooldown;

    int cooldown_restant;

} t_attaque_corps;

void chargerAttaqueTir(t_attaque_tir * attaque, e_nom_attaque nouvelle_attaque);

#endif //_JEU_ATTAQUE_
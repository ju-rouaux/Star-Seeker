/**
 * \file attaque.h
 * 
 * \brief Module gérant les attaques des personnages
 * 
 * \author Julien Rouaux
 */

#ifndef _JEU_ATTAQUE_
#define _JEU_ATTAQUE_

#include <moteur.h>
#include <projectiles.h>

typedef struct s_personnage t_personnage; //Pour les prototypes de fonction

#define NB_ATTAQUE 8

/**
 * \enum e_nom_attaque 
 * \brief Identifiant pour reconnaitre le type de l'attaque
 */
typedef enum
{
    A_DEFAUT, A_DEFAUT_LARGE, A_FEU_SIMPLE, A_FEU, A_SNIPER, A_SNIPER_3, A_360, A_360_MORE, A_TOURNER, A_SABRE,
} e_nom_attaque;


/**
 * \struct t_attaque_tir
 * \brief Modélise une arme générant des projectiles.
 */
typedef struct
{
    //Définition de l'attaque de tir

    e_type_projectile type_projectile;
    int cooldown; /** Temps en ms avant de pouvoir réutiliser l'attaque */
    int nb_salves; /** Nombre de salves */
    int nb_proj_salve; /** Nombre de projectiles par salves */
    int tir_interval; /** Temps en ms entre le tir de chaque salve */
    float etalement; /** Angle exprimé en radiant représentant le niveau d'étalement d'une salve de projectiles (ignoré lorsqu'une salve ne contient qu'un projectile) */

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
void updateAttaqueTir(t_moteur * moteur, t_personnage * personnage, int attaquer);

#endif //_JEU_ATTAQUE_
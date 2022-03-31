/**
 * \file definitions_attaques_tir.h
 * 
 * \brief Fichier de définition des attaques de tir.
 *
 * 
 * POUR CREER UNE NOUVELLE ATTAQUE :
 *      - Ajouter le nom de votre attaque dans l'enum e_nom_attaque sous la forme NOMATTAQUE dans le fichier attaque.h
 *      - Créer une fonction sous la forme :
 *              static void attaque_tir_NOMATTAQUE(t_attaque_tir * attaque)
 *              {
 *                  attaque->type_projectile = NOM_DU_TYPE_PROJECTILE;
 *                  attaque->cooldown = INT;
 *                  attaque->nb_salves = INT;
 *                  attaque->nb_proj_salve = INT;
 *                  attaque->tir_interval = INT;
 *                  attaque->etalement = FLOAT;
 *              }
 *     - Ajouter la fonction au switch de chargerAttaqueTir :
 *              case NOMATTAQUE:
 *                  attaque_tir_NOMATTAQUE(attaque);
 *                  break;
 * 
 * 
 * \author Julien Rouaux
 */


#ifndef _JEU_DEF_ATTAQUE_TIR_
#define _JEU_DEF_ATTAQUE_TIR_


#include <attaque.h>

#define PI 3.14159265359


/**
 * \brief Attaque par defaut
 * 
 * \param attaque Retour l'attaque
 */
static void attaque_tir_defaut(t_attaque_tir * attaque)
{
    attaque->type_projectile = BALLE;
    attaque->cooldown = 500;
    attaque->nb_salves = 1;
    attaque->nb_proj_salve = 1;
    attaque->tir_interval = 0;
    attaque->etalement = 0;
}

/**
 * \brief Attaque pquit tire une boule de feu
 * 
 * \param attaque Retour l'attaque
 */
static void attaque_tir_feu_simple(t_attaque_tir * attaque)
{
    attaque->type_projectile = BOULE_FEU;
    attaque->cooldown = 1000;
    attaque->nb_salves = 1;
    attaque->nb_proj_salve = 1;
    attaque->tir_interval = 100;
    attaque->etalement = 0;
}

/**
 * \brief Attaque qui tire 2 balle dans un rayon restreint
 * 
 * \param attaque Retour l'attaque
 */
static void attaque_tir_defaut_large(t_attaque_tir * attaque)
{
    attaque->type_projectile = BALLE;
    attaque->cooldown = 1100;
    attaque->nb_salves = 2;
    attaque->nb_proj_salve = 2;
    attaque->tir_interval = 200;
    attaque->etalement = PI/10;
}

/**
 * \brief Attaque pquit tire 3 boules de feu
 * 
 * \param attaque Retour l'attaque
 */
static void attaque_tir_feu(t_attaque_tir * attaque)
{
    attaque->type_projectile = BOULE_FEU;
    attaque->cooldown = 1000;
    attaque->nb_salves = 1;
    attaque->nb_proj_salve = 3;
    attaque->tir_interval = 100;
    attaque->etalement = PI/2;
}

/**
 * \brief Attaque type sniper
 * 
 * \param attaque Retour l'attaque
 */
static void attaque_tir_sniper(t_attaque_tir * attaque)
{
    attaque->type_projectile = BOULET;
    attaque->cooldown = 2000;
    attaque->nb_salves = 1;
    attaque->nb_proj_salve = 1;
    attaque->tir_interval = 100;
    attaque->etalement = 0.349066;
}

/**
 * \brief Attaque type sniper dans 2 directions simultanées
 * 
 * \param attaque Retour l'attaque
 */
static void attaque_tir_sniper_3(t_attaque_tir * attaque)
{
    attaque->type_projectile = BOULET;
    attaque->cooldown = 2000;
    attaque->nb_salves = 1;
    attaque->nb_proj_salve = 3;
    attaque->tir_interval = 0;
    attaque->etalement = PI;
}

/**
 * \brief Attaque qui tir des shuriken a 360 degres
 * 
 * \param attaque Retour l'attaque
 */
static void attaque_tir_360_shuriken(t_attaque_tir * attaque)
{
    attaque->type_projectile = SHURIKEN;
    attaque->cooldown = 2000;
    attaque->nb_salves = 1;
    attaque->nb_proj_salve = 13;
    attaque->tir_interval = 300;
    attaque->etalement = 2*PI;
}

/**
 * \brief Attaque qui tir des shuriken a 360 degres, moins, mais plus de salves
 * 
 * \param attaque Retour l'attaque
 */
static void attaque_tir_360_shuriken_more(t_attaque_tir * attaque)
{
    attaque->type_projectile = SHURIKEN;
    attaque->cooldown = 2000;
    attaque->nb_salves = 3;
    attaque->nb_proj_salve = 5;
    attaque->tir_interval = 200;
    attaque->etalement = PI + PI/2;
}


/**
 * \brief 
 * 
 * \param attaque Retour l'attaque
 */
static void attaque_tir_tourner(t_attaque_tir * attaque)
{
    attaque->type_projectile = TOURNER;
    attaque->cooldown = 2000;
    attaque->nb_salves = 1;
    attaque->nb_proj_salve = 1;
    attaque->tir_interval = 0;
    attaque->etalement = PI;
}

/**
 * \brief Lance un sabre et revient sur le joueur apres x temps ou s'il touche un mur 
 * 
 * \param attaque Retour l'attaque
 */
static void attaque_tir_sabre(t_attaque_tir * attaque)
{
    attaque->type_projectile = SABRE;
    attaque->cooldown = 1500;
    attaque->nb_salves = 1;
    attaque->nb_proj_salve =1;
    attaque->tir_interval = 0;
    attaque->etalement = 0;
}

#endif //JEU_DEF_ATTAQUE_TIR_
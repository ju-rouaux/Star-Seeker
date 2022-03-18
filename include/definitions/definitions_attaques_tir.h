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



static void attaque_tir_demo(t_attaque_tir * attaque)
{
    attaque->type_projectile =P_BALLE;
    attaque->cooldown = 1000;
    attaque->nb_salves = 3;
    attaque->nb_proj_salve = 3;
    attaque->tir_interval = 100;
    attaque->etalement = 0.349066;
}


static void attaque_tir_sniper(t_attaque_tir * attaque)
{
    attaque->type_projectile = P_SNIPER;
    attaque->cooldown = 2000;
    attaque->nb_salves = 1;
    attaque->nb_proj_salve = 1;
    attaque->tir_interval = 100;
    attaque->etalement = 0.349066;
}

static void attaque_tir_pls(t_attaque_tir * attaque)
{
    attaque->type_projectile = P_PLS;
    attaque->cooldown = 2000;
    attaque->nb_salves = 2;
    attaque->nb_proj_salve = 25;
    attaque->tir_interval = 150;
    attaque->etalement = 6.28318530718;
}



#endif //JEU_DEF_ATTAQUE_TIR_
/**
 * \file definitions_attaques_tir.h
 * 
 * \brief Fichier de définition des attaques de tir.
 * 
 * \author Julien Rouaux
 */


/*
    POUR CREER UNE NOUVELLE ATTAQUE :
        - Ajouter le nom de votre attaque dans l'enum e_nom_attaque sous la forme NOMATTAQUE dans le fichier attaque.h
        - Créer une fonction sous la forme :
                static void attaque_tir_NOMATTAQUE(t_attaque_tir * attaque)
                {
                    attaque->type_projectile = NOM_DU_TYPE_PROJECTILE;
                    attaque->cooldown = INT;
                    attaque->nb_salves = INT;
                    attaque->nb_proj_salve = INT;
                    attaque->tir_interval = INT;
                    attaque->etalement = FLOAT;
                }
        - Ajouter la fonction au switch de chargerAttaqueTir :
                case NOMATTAQUE:
                    attaque_tir_NOMATTAQUE(attaque);
                    break;
*/

#ifndef _JEU_DEF_ATTAQUE_TIR_
#define _JEU_DEF_ATTAQUE_TIR_

#include <attaque.h>


static void attaque_tir_demo(t_attaque_tir * attaque)
{
    attaque->type_projectile = BALLE;
    attaque->cooldown = 1000;
    attaque->nb_salves = 3;
    attaque->nb_proj_salve = 3;
    attaque->tir_interval = 100;
    attaque->etalement = 0.349066;
}

/**
 * \brief Actualise les champs de la structure attaque vers les paramètres décrits par le nom de la future attaque.
 * 
 * \param attaque L'attaque à actualiser
 * \param nouvelle_attaque La nouvelle attaque désirée 
 */
void chargerAttaqueTir(t_attaque_tir * attaque, e_nom_attaque nouvelle_attaque)
{
    switch (nouvelle_attaque)
    {


    case DEMO:
        attaque_tir_demo(attaque);
        break;
    

    default:
        break;
    }
    attaque->nb_salves_restantes = 0;
    attaque->temps_debut_attaque = 0;
}

#endif //JEU_DEF_ATTAQUE_TIR_
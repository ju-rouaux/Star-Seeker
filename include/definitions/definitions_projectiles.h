/**
 * \file definitions_attaques_tir.h
 * 
 * \brief Fichier de définition des attaques de tir.
 * 
 * 
 * POUR CREER UN NOUVEAU PROJECTILE :
 *      - Ajouter le nom de votre projectile dans l'enum e_type_projectile sous la forme NOMPROJECTILE dans le fichier projectile.h
 *      - Créer une fonction sous la forme :
 *              static int proj_NOMPROJECTILE(t_projectile * projectile)
 *              {
 *                  projectile->animation = creerAnimation(INT, INT);  //ou NULL si pas d'animation
 *                  if(projectile->animation == NULL)                  //pas nécéssaire si pas d'animation
 *                      return -1;
 *                  
 *                  projectile->id_animation = INT;
 *
 *                  projectile->taille = INT;
 *                  projectile->vitesse = INT;
 *                  projectile->dommages = INT;
 *                  projectile->duree_de_vie = INT;
 *
 *                  //Fonction générique updateProjectile ou une fonction personnelle
 *                  projectile->update = (int (*)(t_moteur *, t_entite *, float, float)) updateProjectile;
 *
 *                  return 0;
 *              }
 *     - Ajouter la fonction au switch de chargerProjectile :
 *              case NOMPROJECTILE:
 *                  return proj_NOMPROJECTILE(projectile);
 * 
 *     - Pour donner au projectile un comportement spécifique, créer une fonction sous la forme :
 *              static int fonction(t_moteur * moteur, t_projectile * projectile)
 *              {
 *                  projectile->duree_de_vie -= moteur->temps - moteur->temps_precedent; //Retirer le temps écoulé à la durée de vie 
 *                  if(projectile->duree_de_vie <= 0)
 *                      return -1;
 * 
 *                  //traitement
 * 
 *                  return deplacerEntite(moteur, (t_entite*) projectile);
 *              }
 *        A la place de traitement, changer les paramètres de vitesse, de direction, de taille... Dans l'idéal ces changements doivent dépendre
 *        de la durée de vie restante.
 *        La fonction doit retourner 0 si tout se passe bien, -1 lorsque le projectile doit être détruit.
 * 
 * \author Julien Rouaux
 */


#ifndef _JEU_DEF_PROJECTILE_
#define _JEU_DEF_PROJECTILE_

#include <projectiles.h>
#include <animation.h>


//--------- Fonctions de comportement ---------

/** 
 * \brief Fonction générique de projectile lui donnant une trajectoire en ligne
 * à vitesse constante.
 * 
 * \param moteur Le moteur du jeu
 * \param projectile Le projectile à actualiser
 * 
 * \return -1 si le projectile doit être détruit, sinon 0.
 */
static int updateProjectile(t_moteur * moteur, t_projectile * projectile)
{
    projectile->duree_de_vie -= moteur->temps - moteur->temps_precedent; //Retirer le temps écoulé à la durée de vie 
    if(projectile->duree_de_vie <= 0)
        return -1;

    return deplacerEntite(moteur, (t_entite*) projectile);
}





//--------- Définitions ---------

/**
 * \brief Rend un projectile de petite taille mais rapide.
 * 
 * \param projectile Le projectile
 * 
 * \return 0 si succès, une valeur négative si echec.
 */
static int proj_balle(t_projectile * projectile)
{
    projectile->animation = NULL; //Pas d'animation
    projectile->id_animation = 0;

    projectile->taille = 0.4;
    projectile->vitesse = 8;
    projectile->dommages = 20;
    projectile->duree_de_vie = 1500;

    projectile->update = (int (*)(t_moteur *, t_entite *, float, float)) updateProjectile;

    return 0;
}


/**
 * \brief Rend un projectile de grande taille mais lent.
 * 
 * \param projectile Le projectile
 * 
 * \return 0 si succès, une valeur négative si echec.
 */
static int proj_boule_feu(t_projectile * projectile)
{
    projectile->animation = creerAnimation(1000, 2);
    if(projectile->animation == NULL)
        return -1;
    projectile->id_animation = 1;

    projectile->taille = 0.7;
    projectile->vitesse = 2;
    projectile->dommages = 30;
    projectile->duree_de_vie = 3000;

    projectile->update = (int (*)(t_moteur *, t_entite *, float, float)) updateProjectile;

    return 0;
}




#endif //_JEU_DEF_PROJECTILE_
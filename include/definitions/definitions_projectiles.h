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
 *                  if(projectile->animation == NULL)                  //pas nécessaire si pas d'animation
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

/**
 * \brief Revient vers le joueur apres un certain temps ou lors d'une collision
 * 
 * \param moteur Le moteur du jeu
 * \param projectile Le projectile à actualiser
 * \param x position du joueur x
 * \param y position du joueur y
 * \return -1 si le projectile doit être détruit, sinon 0.
 */
static int updateProjectile_RetourProj(t_moteur * moteur, t_projectile * projectile, float x, float y)
{
    projectile->duree_de_vie -= moteur->temps - moteur->temps_precedent; //Retirer le temps écoulé à la durée de vie 
    if(projectile->duree_de_vie <= 0)
        return -1;

    if((projectile->x < x+0.4 && projectile->x > x-0.4) && (projectile->y < y+0.4 && projectile->y > y-0.4) && (projectile->duree_de_vie < 1920))
        return -1;

    if(projectile->duree_de_vie < 4*2000/5){
        projectile->direction_vx = x - projectile->x;
        projectile->direction_vy = y - projectile->y;
        projectile->vitesse = 8;
    }

    if(deplacerEntite(moteur, (t_entite*) projectile) == -1){
        projectile->direction_vx = x - projectile->x;
        projectile->direction_vy = y - projectile->y;
    }
    return 0;
}


/**
 * \brief Revient vers le joueur apres un certain temps ou lors d'une collision
 * 
 * \param moteur Le moteur du jeu
 * \param projectile Le projectile à actualiser
 * \param x position du joueur x
 * \param y position du joueur y
 * \return -1 si le projectile doit être détruit, sinon 0.
 */
static int updateProjectile_tourner(t_moteur * moteur, t_projectile * projectile, float x, float y)
{
    projectile->duree_de_vie -= moteur->temps - moteur->temps_precedent; //Retirer le temps écoulé à la durée de vie 
    if(projectile->duree_de_vie <= 0)
        return -1;

    projectile->direction_vx = 1;
    projectile->direction_vy = sin((moteur->temps % 100)/100)*10;

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
    projectile->dommages = 1;
    projectile->duree_de_vie = 1000;

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

    projectile->taille = 0.8;
    projectile->vitesse = 4;
    projectile->dommages = 4;
    projectile->duree_de_vie = 3000;

    projectile->update = (int (*)(t_moteur *, t_entite *, float, float)) updateProjectile;

    return 0;
}


/**
 * \brief Rend un projectile tres rapide, avec une tres longue portée
 * \param projectile Le projectile
 * \return 0 si succès, une valeur négative si echec.
 */
static int proj_boule_metal(t_projectile * projectile)
{
    projectile->animation = NULL; //Pas d'animation
    projectile->id_animation = 3;

    projectile->taille = 0.4;
    projectile->vitesse = 12;
    projectile->dommages = 3;
    projectile->duree_de_vie = 2500;

    projectile->update = (int (*)(t_moteur *, t_entite *, float, float)) updateProjectile;

    return 0;
}

/**
 * \brief Rend un projectile rapide mais avec un tres courte portée
 * \param projectile Le projectile
 * \return 0 si succès, une valeur négative si echec.
 */
static int proj_shuriken(t_projectile * projectile)
{
    projectile->animation = creerAnimation(200, 2);
    if(projectile->animation == NULL)
        return -1;
    projectile->id_animation = 2;

    projectile->taille = 0.6;
    projectile->vitesse = 6;
    projectile->dommages = 1;
    projectile->duree_de_vie = 250;

    projectile->update = (int (*)(t_moteur *, t_entite *, float, float)) updateProjectile;

    return 0;
}


/**
 * \brief Rend un projectile rapide mais avec un tres courte portée
 * \param projectile Le projectile
 * \return 0 si succès, une valeur négative si echec.
 */
static int proj_tourner(t_projectile * projectile)
{
    projectile->animation = NULL; //Pas d'animation
    projectile->id_animation = 5;

    projectile->taille = 0.4;
    projectile->vitesse = 8;
    projectile->dommages = 1;
    projectile->duree_de_vie = 1000;

    projectile->update = (int (*)(t_moteur *, t_entite *, float, float)) updateProjectile_tourner;

    return 0;
}

/**
 * \brief Rend un projectile rapide mais avec un tres courte portée
 * \param projectile Le projectile
 * \return 0 si succès, une valeur négative si echec.
 */
static int proj_sabre(t_projectile * projectile)
{
    projectile->animation = creerAnimation(75, 2);
    if(projectile->animation == NULL)
        return -1;
    projectile->id_animation = 4;

    projectile->taille = 0.8;
    projectile->vitesse = 14;
    projectile->dommages = 2;
    projectile->duree_de_vie = 2000;

    projectile->update = (int (*)(t_moteur *, t_entite *, float, float)) updateProjectile_RetourProj;

    return 0;
}


#endif //_JEU_DEF_PROJECTILE_
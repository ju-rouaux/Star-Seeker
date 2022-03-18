/**
 * \file attaque.h
 * 
 * \brief Module gérant les attaques des personnages
 * 
 * \author Julien Rouaux
 */



#include <moteur.h>
#include <personnage.h>
#include <projectiles.h>
#include <liste.h>
#include <math.h>
#include <attaque.h>



// ----------------------- Définition -----------------------


//Liste des attaques disponibles
#include <definitions/definitions_attaques_tir.h>


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
    case SNIPER:
        attaque_tir_sniper(attaque);
        break;
    case A_360:
        attaque_tir_360_shuriken(attaque);
        break;
    case SABRE_LASER:
        attaque_tir_sabre(attaque);
        break;

    case DEMO:
        attaque_tir_demo(attaque);
        break;
    

    default:
        break;
    }
    attaque->nb_salves_restantes = 0;
    attaque->temps_debut_attaque = 0;
}


// ----------------------- Fonctionnement -----------------------


/**
 * \brief Génère autant de projectiles définis dans l'attaque du personnage.
 * 
 * Si une salve contient plusieurs projectiles, ces derniers seront répartis selon le paramètre d'étalement.
 * 
 * \param moteur Le moteur du jeu
 * \param personnage Le personnage exécutant l'attaque
 */
static void tirer(t_moteur * moteur, t_personnage * personnage)
{
    t_attaque_tir * attaque = &personnage->attaque_tir_equipee;
    t_projectile * projectile = NULL;

    if(attaque->nb_proj_salve > 1)
    {
        float angle_proj;

        //Norme du vecteur direction
        float norme_vect_dirct = sqrt( pow(personnage->direction_vx, 2) + pow(personnage->direction_vy, 2) );

        //Angle en radian du vecteur direction par rapport à l'axe x
        float angle_vect_dirct = acos(personnage->direction_vx / norme_vect_dirct);

        //Une unité, angle d'un projectile par rapport à l'axe x, si nombre de proj impaire : retirer 1 car ce projectile sera placé sur l'axe de direction
        float unit_angle_proj = attaque->etalement / (attaque->nb_proj_salve % 2 ? attaque->nb_proj_salve - 1 : attaque->nb_proj_salve);
        
        //Partie au dessus de l'axe direction
        for(int i = 0; i < attaque->nb_proj_salve / 2; i++)
        { 
            //Se décaler de i fois l'angle unité par rapport au vecteur direction (si il est positif par rapport à y, ajouter la différence avc l'axe x, sinon soustraire)
            angle_proj = (i+1) * unit_angle_proj + (personnage->direction_vy > 0 ? angle_vect_dirct : -angle_vect_dirct);

            projectile = creerProjectile(attaque->type_projectile, 
                                    personnage->x, personnage->y, 
                                    cos(angle_proj), sin(angle_proj), 
                                    !personnage->type, //Le type de personnage opposé à celui actuel
                                    moteur->textures->projectiles);
            ajouterEntiteListe(moteur->liste_entites, (t_entite*) projectile);
            projectile = NULL;
        }

        //Projectile au centre si nombre de proj impaire
        if(attaque->nb_proj_salve % 2)
        {
            projectile = creerProjectile(attaque->type_projectile, 
                                        personnage->x, personnage->y, 
                                        personnage->direction_vx, personnage->direction_vy, 
                                        !personnage->type, //Le type de personnage opposé à celui actuel
                                        moteur->textures->projectiles);
            ajouterEntiteListe(moteur->liste_entites, (t_entite*) projectile);
            projectile = NULL;
        }

        //Partie en dessous de l'axe direction
        for(int i = 0; i < attaque->nb_proj_salve / 2; i++)
        { 
            //Se décaler de i fois l'angle unité par rapport au vecteur direction (si il est positif par rapport à y, ajouter la différence avc l'axe x, sinon soustraire)
            angle_proj = -(i+1) * unit_angle_proj - (personnage->direction_vy < 0 ? angle_vect_dirct : -angle_vect_dirct);

            projectile = creerProjectile(attaque->type_projectile, 
                                    personnage->x, personnage->y, 
                                    cos(angle_proj), sin(angle_proj), 
                                    !personnage->type, //Le type de personnage opposé à celui actuel
                                    moteur->textures->projectiles);
            ajouterEntiteListe(moteur->liste_entites, (t_entite*) projectile);
            projectile = NULL;
        }
    }
    
    else //Simple tir
    {
        projectile = creerProjectile(attaque->type_projectile, 
                                    personnage->x, personnage->y, 
                                    personnage->direction_vx, personnage->direction_vy, 
                                    !personnage->type, //Le type de personnage opposé à celui actuel
                                    moteur->textures->projectiles);
        ajouterEntiteListe(moteur->liste_entites, (t_entite*) projectile);
        projectile = NULL;
    }
}


/**
 * \brief Cette fonction devant être appelée à chaque actualisation d'un personnage permet à une attaque de
 * continuer de s'exécuter si elle dure dans le temps, ou bien de lancer une attaque si "attaquer" est vrai.
 * 
 * Si attaquer est vrai, mais que le cooldown de l'attaque n'est pas terminé, l'attaque ne sera pas réalisée.
 * ATTENTION : La direction de l'attaque est la même que la direction du personnage.
 * 
 * \param moteur Le moteur du jeu
 * \param personnage Le personnage réalisant l'attaque
 * \param attaquer Vrai si le personnage désire lancer une nouvelle attaque
 */
void updateAttaqueTir(t_moteur * moteur, t_personnage * personnage, int attaquer)
{
    /* Execution de l'attaque */
    t_attaque_tir * attaque = &personnage->attaque_tir_equipee;

    //Temps quand l'attaque sera terminée
    int temps_fin = attaque->temps_debut_attaque + attaque->cooldown;
    if(attaquer && temps_fin < moteur->temps) //Permettre l'attaque si autorisé
    {
        attaque->temps_debut_attaque = moteur->temps;
        attaque->nb_salves_restantes = attaque->nb_salves;
    }

    /* Update de l'attaque */
    if(attaque->nb_salves_restantes > 0)
    {
        //Calcul du temps qu'il sera au tir de la prochaine salve
        int temps_next_salve = attaque->temps_debut_attaque + attaque->tir_interval*(attaque->nb_salves - attaque->nb_salves_restantes);
        if(temps_next_salve < moteur->temps)
        {
            (attaque->nb_salves_restantes)--;
            tirer(moteur, personnage);
        }
    }
}
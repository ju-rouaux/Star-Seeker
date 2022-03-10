/*


    EN DEVELOPPEMENT



*/

#include <moteur.h>
#include <personnage.h>
#include <projectiles.h>
#include <attaque.h>
#include <liste.h>
#include <math.h>

static void attaque_tir_demo(t_attaque_tir * attaque)
{
    attaque->type_projectile = BALLE;
    attaque->cooldown = 1000;
    attaque->nb_salves = 3;
    attaque->nb_proj_salve = 3;
    attaque->tir_interval = 100;
    attaque->etalement = 0.349066;
}

static void tirer(t_moteur * moteur, t_personnage * personnage)
{
    t_attaque_tir * attaque = &personnage->attaque_tir_equipee;
    t_projectile * projectile;

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
            ajout_droit(moteur->liste_entites, projectile);
        }

        //Projectile au centre si nombre de proj impaire
        if(attaque->nb_proj_salve % 2)
        {
            projectile = creerProjectile(attaque->type_projectile, 
                                        personnage->x, personnage->y, 
                                        personnage->direction_vx, personnage->direction_vy, 
                                        !personnage->type, //Le type de personnage opposé à celui actuel
                                        moteur->textures->projectiles);
            ajout_droit(moteur->liste_entites, projectile);
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
            ajout_droit(moteur->liste_entites, projectile);
        }
    }
    
    else //Simple tir
    {
        projectile = creerProjectile(attaque->type_projectile, 
                                    personnage->x, personnage->y, 
                                    personnage->direction_vx, personnage->direction_vy, 
                                    !personnage->type, //Le type de personnage opposé à celui actuel
                                    moteur->textures->projectiles);
        ajout_droit(moteur->liste_entites, projectile);
    }

    
}

//Changer le type en personnage quand ce sera pret
//return vrai si l'attaque a pu etre executee
//Nouvelle attaque vrai si le personnage désire attaquer de nouveau
void updateAttaqueTir(t_moteur * moteur, t_personnage * personnage, int attaque_desiree)
{
    /* Execution de l'attaque */
    t_attaque_tir * attaque = &personnage->attaque_tir_equipee;

    //Temps quand l'attaque sera terminée
    int temps_fin = attaque->temps_debut_attaque + attaque->cooldown;
    if(attaque_desiree && temps_fin < moteur->temps) //Permettre l'attaque si autorisé
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
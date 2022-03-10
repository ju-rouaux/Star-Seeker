/*


    EN DEVELOPPEMENT



*/

#include <moteur.h>
#include <personnage.h>
#include <projectiles.h>
#include <attaque.h>
#include <liste.h>

static void attaque_tir_demo(t_attaque_tir * attaque)
{
    attaque->type_projectile = BALLE;
    attaque->cooldown = 1000;
    attaque->nb_salves = 5;
    attaque->nb_proj_salve = 1;
    attaque->tir_interval = 100;
}

static void tirer(t_moteur * moteur, t_personnage * personnage)
{
    t_attaque_tir * attaque = &personnage->attaque_tir_equipee;
    for(int i = 0; i < attaque->nb_proj_salve; i++)
    {
        t_projectile * projectile = creerProjectile(attaque->type_projectile, 
                                    personnage->x, personnage->y, 
                                    personnage->direction_vx, personnage->direction_vy, 
                                    !personnage->type, //Le type de personnage opposé à celui actuel
                                    moteur->textures->projectiles);
        ajout_gauche(moteur->liste_entites, projectile);
        suivant(moteur->liste_entites);
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
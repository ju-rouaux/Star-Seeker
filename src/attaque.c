#include <joueur.h>
#include <projectiles.h>
#include <attaque.h>

//Changer le type en personnage quand ce sera pret
//return vrai si l'attaque a pu etre executee
//Nouvelle attaque vrai si le personnage désire attaquer de nouveau
int executerAttaque(t_joueur * personnage, int temps_ecoule, int nouvelle_attaque)
{

}

static void attaque_tir_demo(t_attaque_tir * attaque)
{
    attaque->type_projectile = BALLE;
    attaque->cooldown = 1;
    attaque->nb_salves = 1;
    attaque->nb_proj_salve = 1;
    attaque->tir_interval = 0;
}


void chargerAttaqueTir(t_attaque_tir * attaque, e_nom_attaque nouvelle_attaque)
{
    switch (nouvelle_attaque)
    {
    case DEMO:
        attaque_demo(attaque);
        break;
    
    default:
        break;
    }
    attaque->nb_salves_restantes = 0;
    attaque->temps_debut_attaque = 0;
}
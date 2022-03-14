/**
 * 
 * 
 *  EN DEVELOPPEMENT
 * 
 */

#include <stdio.h>
#include <monstre.h>
#include <outils.h>

int updateMonstreStatique(t_moteur * moteur, t_monstre * monstre)
{
    if(monstre->pv <= 0)
        return -1;
    updateAttaqueTir(moteur, (t_personnage*) monstre, de(50) == 50);
    return 0;
}

int dessinerMonstre(t_moteur * moteur, t_monstre * monstre)
{
    int id_animation = monstre->id_animation; //Sauvegarde de l'id animation

    monstre->texture = moteur->textures->monstres_bas;
    dessinerEntite(moteur, monstre);

    monstre->id_animation = monstre->deplacement; //Utiliser la valeur de la méthdoe de déplacement pour avoir la bonne animation
    monstre->texture = moteur->textures->monstres_haut;
    dessinerEntite(moteur, monstre);

    monstre->id_animation = id_animation; //Remettre l'id animation de base
    
    return 0;
}

static int (*getDeplacement(e_deplacement_monstre deplacement))(t_moteur*, t_entite*)
{
    switch (deplacement)
    {
    case STATIQUE:
        return updateMonstreStatique;
    
    default:
        return updateMonstreStatique;
    }
}


t_monstre * creerMonstre(float x, float y, float vitesse, int pv, float taille, e_nom_attaque type_attaque, e_deplacement_monstre deplacement)
{
    t_entite * entite = creerEntite(x, y, NULL);
    t_monstre * monstre = realloc(entite, sizeof(t_monstre));
    if(monstre == NULL)
    {
        printf("Impossible d'allouer la mémoire pour monstre\n");
        detruireEntite(&entite);
        return NULL;
    }
    entite = NULL;

    chargerAttaqueTir(&monstre->attaque_tir_equipee, type_attaque);

    monstre->animation = creerAnimation(100, 1);
    if(monstre->animation == NULL)
    {
        printf("Le monstre n'a pas pu être créé\n");
        free(monstre);
        return NULL;
    }

    monstre->id_animation = type_attaque; //Associer à une attaque l'apparence du monstre
    monstre->deplacement = deplacement;

    monstre->type = E_MONSTRE;

    monstre->vitesse = vitesse;
    monstre->taille = taille;
    monstre->pv = pv;

    monstre->update = getDeplacement(deplacement);
    monstre->dessiner = dessinerMonstre;

    return monstre;
}
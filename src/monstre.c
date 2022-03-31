/**
 * \file monstre.h
 * 
 * \brief Module de gestion des monstres.
 * 
 * \author Julien Rouaux
 */


#include <stdio.h>
#include <math.h>
#include <monstre.h>
#include <outils.h>
#include <math.h>

/**
 * \brief Met a jour la direction du vecteur pour que le monstre attaque et se déplace dans la direction du joueur
 * 
 * \param moteur le moteur
 * \param monstre un monstre
 * \param pos_joueur_x coordonées x du joueur
 * \param pos_joueur_y coordonées y du joueur
 * \return 0 si succès, -1 sinon
 */
static int updateMonstreVersJoueur(t_moteur * moteur, t_monstre * monstre, float pos_joueur_x, float pos_joueur_y)
{
    if(monstre->pv <= 0)
        return -1;
    
    monstre->attaque_vx = monstre->direction_vx = pos_joueur_x - monstre->x;
    monstre->attaque_vy = monstre->direction_vy = pos_joueur_y - monstre->y;

    //Ne pas se diriger le monstre vers le joueur s'il est à plus d'une salle et quart du joueur
    float norme = sqrt(pow(monstre->direction_vx, 2) + pow(monstre->direction_vy, 2));
    if(norme < (NB_TILE_LARGEUR + NB_TILE_LARGEUR / 4) && norme > -(NB_TILE_LARGEUR + NB_TILE_LARGEUR / 4))
    {
        updateAttaqueTir(moteur, (t_personnage*) monstre, de(60) == 60);
        if(norme > 0.5 || norme < -0.5)
            deplacerEntite(moteur, (t_entite*) monstre);
    }

    return 0;
}

/**
 * \brief Met a jour le vecteur pour que le monstre attaque dans la direction du joueur
 * 
 * \param moteur le moteur
 * \param monstre un monstre
 * \param pos_joueur_x coordonées x du joueur
 * \param pos_joueur_y coordonées y du joueur
 * \return 0 si succès, -1 sinon 
 */
static int updateMonstreStatique(t_moteur * moteur, t_monstre * monstre, float pos_joueur_x, float pos_joueur_y)
{
    if(monstre->pv <= 0)
        return -1;

    monstre->vitesse = 0;
    
    monstre->attaque_vx = pos_joueur_x - monstre->x;
    monstre->attaque_vy = pos_joueur_y - monstre->y;

    updateAttaqueTir(moteur, (t_personnage*) monstre, de(60) == 60);
    deplacerEntite(moteur, (t_entite*) monstre);

    return 0;
}


/**
 * \brief Fonction d'enscapsulation pour dessiner un monstre car ces derniers utilisent deux textures.
 * 
 * \param moteur Le moteur
 * \param monstre Le monstre à dessiner
 * 
 * \return 0 si succès, sinon une valeur négative (SDL_Error() pour connaitre l'erreur).
 */
int dessinerMonstre(t_moteur * moteur, t_monstre * monstre)
{
    monstre->id_animation = monstre->deplacement; //Utiliser la valeur de la méthode de déplacement pour avoir la bonne animation
    monstre->texture = moteur->textures->monstres_bas;
    dessinerEntite(moteur, (t_entite*) monstre);

    monstre->id_animation = monstre->nom_attaque; //Utiliser la valeur de la méthode d'attaque pour avoir la bonne animation
    monstre->texture = moteur->textures->monstres_haut;
    return dessinerEntite(moteur, (t_entite*) monstre);    
}


/**
 * \brief Retourne un pointeur sur une fonction de déplacement d'un monstre à partir du déplacement spécifié.
 * 
 * \param depacement Le déplacement souhaité
 * 
 * \return Un pointeur sur une fonction retournant un entier et prenant les paramètres (t_moteur *, t_entite *, float, float).
 */
static int (*getDeplacement(e_deplacement_monstre deplacement))(t_moteur *, t_entite *, float, float)
{
    switch (deplacement)
    {
    case VERS_J:
        return (int (*)(t_moteur *, t_entite *, float, float)) updateMonstreVersJoueur;

    case STATIQUE:
        return (int (*)(t_moteur *, t_entite *, float, float)) updateMonstreStatique;
    
    default:
        return (int (*)(t_moteur *, t_entite *, float, float)) updateMonstreStatique;
    }
}


/**
 * \brief Création d'un monstre
 * 
 * \param x La position en x
 * \param y La position en y
 * \param vitesse Sa vitesse en tiles par secondes
 * \param pv Son nombre de points de vie
 * \param taille Sa taille à l'échelle d'une tile
 * \param type_attaque L'attaque équipée
 * \param deplacement La méthode de déplacement équipée
 * 
 * \return Le pointeur projectile (NULL si echec).
 */
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
    monstre->nom_attaque = type_attaque;

    monstre->vitesse = vitesse;
    monstre->taille = taille;
    monstre->pv = pv;

    monstre->attaque_vx = monstre->direction_vx;
    monstre->attaque_vy = monstre->direction_vy;

    monstre->update = getDeplacement(deplacement);
    monstre->dessiner = (int (*)(t_moteur*, t_entite*)) dessinerMonstre;

    return monstre;
}
/**
 * \file joueur.c
 * 
 * \brief Module de gestion du joueur.
 * 
 * \author Julien Rouaux
 */


#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <moteur.h>
#include <niveau.h>
#include <entite.h>
#include <animation.h>
#include <liste.h>
#include <joueur.h>
#include <attaque.h>
#include <monstre.h>

/**
 * \brief Calcule l'animation à joueur selon l'orientation du joueur.
 * 
 * Les codes pour code_animation sont les suivants :
 *      -0 : innactif
 *      -1 : marche
 *      -2 : attaque épée
 *      -3 : projectile
 * 
 * \param vecteur_x Orientation du joueur en x
 * \param vecteur_y Orientation du joueur en y
 * \param code_animation Spécification de l'animation désirée
 * 
 * \return L'identifiant de l'animation à jouer.
 */
static int getIdAnimationJoueur(int vecteur_x, int vecteur_y, int code_animation)
{
    int id_animation;

    //Calculer direction
    if(!vecteur_x && !vecteur_y) //Si vecteur nul, personage idle vers l'avant
        id_animation = 4;
    else
    {
        if(vecteur_x && !vecteur_y) //Droite ou gauche 
            id_animation = vecteur_x > 0 ? 2 : 6;
        else if(!vecteur_x && vecteur_y) //Haut ou bas
            id_animation = vecteur_y > 0 ? 4 : 0;
        else //Diagonales
        {
            if(vecteur_x > 0)
                id_animation = vecteur_y > 0 ? 3 : 1;
            else
                id_animation = vecteur_y > 0 ? 5 : 7;
        }
    }

    //Calculer animation
    id_animation = 2*id_animation + code_animation;
    
    return id_animation;
}


/**
 * \brief Remplissage du vecteur selon l'orientation du joueur donné par ses flags.
 * 
 * \param flags Les flags du joueur
 * \param vecteur_x Retour du vecteur en x
 * \param vecteur_y Retour du vecteur en y
 */
static void getDirectionJoueur(const t_joueur_flags * flags, float * vecteur_x, float * vecteur_y)
{
    //Conversion des flags en vecteur
    int direction_x = flags->to_right == flags->to_left ? 0 : (flags->to_right > flags->to_left ? 1 : -1);
    int direction_y = flags->to_down == flags->to_up ? 0 : (flags->to_down > flags->to_up ? 1 : -1);
    
    //Seulement si le joueur se dirige dans une direction, actualiser les vecteurs.
    //Ainsi le joueur restera dans sa dernière direction s'il ne bouge pas.
    if(direction_x || direction_y)
    {
        if(vecteur_x != NULL)
                *vecteur_x = direction_x;
        if(vecteur_y != NULL)
                *vecteur_y = direction_y;
    }
}


/**
 * \brief Méthode appelée à chaque frame, actualisant le joueur.
 * 
 * Permet de redéfinir les champs de la structure du joueur selon le contexte de la partie.
 * Cette fonction ne dessine pas le joueur.
 * 
 * \param moteur Le moteur du jeu
 * \param joueur Le joueur
 * 
 * \return Un code indiquant un éventuel état du joueur, uniquement 0 pour l'instant.
 */
static int updateJoueur(t_moteur * moteur, t_joueur * joueur)
{
    int etat = 0;
    getDirectionJoueur(joueur->flags, &joueur->direction_vx, &joueur->direction_vy);

    //Déterminer l'état du joueur
    if(joueur->flags->to_down || joueur->flags->to_left || joueur->flags->to_right || joueur->flags->to_up) //Si joueur bouge
    {
        joueur->animation->vitesse = 50;
        deplacerEntite(moteur, (t_entite*) joueur);
        etat = 1;
    }
    else
        joueur->animation->vitesse = 250;
    
    updateAttaqueTir(moteur, (t_personnage*) joueur, joueur->flags->shooting);
    /*
    if(joueur->flags->shooting == 1) //Prétendons que celà signifie une attaque pour la démo
    {
        t_monstre * monstre = creerMonstre(joueur->x, joueur->y, 2, 100, 2, DEMO, STATIQUE);
        en_queue(moteur->liste_entites);
        if(monstre != NULL)
            ajout_droit(moteur->liste_entites, (t_entite*) monstre);
        
    }
    */

    joueur->id_animation = getIdAnimationJoueur((int)joueur->direction_vx, (int)joueur->direction_vy, etat);

    return 0;
}


/**
 * \brief Génère une structure t_joueur_flags.
 * 
 * \return Le pointeur t_joueur_flags, NULL si échec.
 */
static t_joueur_flags * creerJoueurFlags()
{
    t_joueur_flags * flags = malloc(sizeof(t_joueur_flags));
    if(flags == NULL)
    {
        printf("Impossible d'allouer la mémoire pour les flags du joueur\n");
        return NULL;
    }

    flags->to_down = 0;
    flags->to_up = 0;
    flags->to_left = 0;
    flags->to_right = 0;

    flags->shooting = 0; // !!! Temporaire

    return flags;
}


/**
 * \brief Libère la mémoire allouée aux flags et mets le pointeur à NULL.

 * \param flags L'adresse du pointeur flags
 */
static void detruireJoueurFlags(t_joueur_flags ** flags)
{
    if(*flags != NULL)
        free(*flags);
    *flags = NULL;
}


/**
 * \brief Libère la mémoire allouée au joueur et mets son pointeur à NULL.

 * \param joueur L'adresse du pointeur joueur
 */
void detruireJoueur(t_joueur ** joueur)
{
    if(*joueur != NULL)
    {
        detruireJoueurFlags(&(*joueur)->flags);
        detruireEntite((t_entite**) joueur);
    }
    *joueur = NULL;
}


/**
 * \brief Génère une structure joueur.
 * 
 * \param x Position du joueur en x
 * \param y Position du joueur en y
 * \param apparence Texture du joueur
 * 
 * \return Le pointeur joueur, NULL si echec.
 */
t_joueur * creerJoueur(float x, float y, SDL_Texture * apparence)
{
    t_entite * entite = creerEntite(x, y, apparence);
    t_joueur * joueur = realloc(entite, sizeof(t_joueur));
    if(joueur == NULL)
    {
        printf("Impossible d'allouer la mémoire pour joueur\n");
        detruireEntite(&entite);
        return NULL;
    }
    entite = NULL;

    joueur->flags = creerJoueurFlags();
    if(joueur->flags == NULL)
    {
        printf("Le joueur n'a pas pu être créé\n");
        free(joueur);
        return NULL;
    }

    joueur->animation = creerAnimation(50, 4); //Changer les paramètres d'animation si on ajoute des animations
    if(joueur->animation == NULL)
    {
        printf("Le joueur n'a pas pu être créé\n");
        detruireJoueurFlags(&joueur->flags);
        free(joueur);
        return NULL;
    }

    joueur->vitesse = VITESSE_JOUEUR_DEFAULT;
    joueur->type = E_JOUEUR;

    joueur->taille = PROPORTION_JOUEUR;
    joueur->id_animation = 0; //idle

    joueur->update = (int (*)(t_moteur *, t_entite *, float, float)) updateJoueur;
    joueur->detruire = (void (*)(t_entite**)) detruireJoueur;

    joueur->pv = 100;

    chargerAttaqueTir(&joueur->attaque_tir_equipee, LASER_CONTINU);

    return joueur;
}


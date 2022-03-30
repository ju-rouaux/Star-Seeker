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
#include <particules.h>

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
static void getDirectionJoueur(const t_joueur_flags * flags, float * vecteur_x, float * vecteur_y, float * attaque_vx, float * attaque_vy, int * shooting)
{
    //Conversion des flags en vecteur
    int direction_x = flags->to_right == flags->to_left ? 0 : (flags->to_right > flags->to_left ? 1 : -1);
    int direction_y = flags->to_down == flags->to_up ? 0 : (flags->to_down > flags->to_up ? 1 : -1);
    int attaque_x = flags->attack_right == flags->attack_left ? 0 : (flags->attack_right > flags->attack_left ? 1 : -1);
    int attaque_y = flags->attack_down == flags->attack_up ? 0 : (flags->attack_down > flags->attack_up ? 1 : -1);
    
    //Seulement si le joueur se dirige dans une direction, actualiser les vecteurs.
    //Ainsi le joueur restera dans sa dernière direction s'il ne bouge pas.
    if(direction_x || direction_y)
    {
        if(vecteur_x != NULL)
                *vecteur_x = direction_x;
        if(vecteur_y != NULL)
                *vecteur_y = direction_y;
    }
    //Meme chose pour la visée, garder la dernière position
    if(attaque_x || attaque_y)
    {
        *shooting = 1;
        if(attaque_vx != NULL)
                *attaque_vx = attaque_x;
        if(attaque_vy != NULL)
                *attaque_vy = attaque_y;
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
    int shooting = 0;

    // ---- Dash

    //Cooldown du dash
    if(joueur->flags->dash == -2)
    {
        joueur->cooldown_dash -= moteur->temps - moteur->temps_precedent;
        if(joueur->cooldown_dash <= 0) //Fin du cooldown
            joueur->flags->dash = 0;
    }
    else if(joueur->flags->dash == 1)  //Etat dash lancé
    {
        //Bloquer le dash
        joueur->temps_restant_dash = 100 + (moteur->temps - moteur->temps_precedent); //100ms + le temps qu'on va soustraire après
        joueur->flags->dash = -1;
        joueur->vitesse = VITESSE_JOUEUR_DEFAULT + 18;
        ajouterEntiteListe(moteur->liste_entites, (t_entite*) creerParticule(P_DASH, joueur->x, joueur->y, moteur->textures->particules));
        Mix_PlayChannel(1, moteur->bruitages->dash, 0);
    }

    if(joueur->flags->dash == -1) //Etat dash en cours
    {
        joueur->temps_restant_dash -= moteur->temps - moteur->temps_precedent; //Retirer le temps écoulé
        if(joueur->temps_restant_dash <= 0) //Fin du dash
        {
            joueur->cooldown_dash = 500; //500 ms de cooldown
            joueur->flags->dash = -2; //lancer cooldown
        }
    }
    else //Etat aucun dash : ne pas bloquer la direction du joueur
    {
        joueur->vitesse = VITESSE_JOUEUR_DEFAULT;
        getDirectionJoueur(joueur->flags, &joueur->direction_vx, &joueur->direction_vy, &joueur->attaque_vx, &joueur->attaque_vy, &shooting);
    }

    // ---- Fin dash

    //Avancer le joueur s'il se déplace volontairement
    if(joueur->flags->to_down || joueur->flags->to_left || joueur->flags->to_right || joueur->flags->to_up || 
    joueur->flags->dash == -1) //Si joueur bouge, ou dash en cours
    {
        joueur->animation->vitesse = 50;
        deplacerEntite(moteur, (t_entite*) joueur);
        etat = 1;
    }
    else
        joueur->animation->vitesse = 250;
    
    //Tirer ou poursuivre l'attaque
    updateAttaqueTir(moteur, (t_personnage*) joueur, shooting);
    
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
    flags->dash = 0;

    flags->attack_up = 0;
    flags->attack_down = 0;
    flags->attack_left = 0;
    flags->attack_right = 0;
    flags->interaction = 0;

    flags->map_shown = 0;

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

    joueur->pv = PV_JOUEUR_DEFAULT;
    joueur->xp = 0;

    joueur->attaque_vx = joueur->direction_vx;
    joueur->attaque_vy = joueur->direction_vy;

    joueur->nom_attaque = A_DEFAUT;
    chargerAttaqueTir(&joueur->attaque_tir_equipee, A_DEFAUT);

    return joueur;
}


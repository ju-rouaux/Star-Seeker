/**
 * \file moteur.c
 
 * \brief Module de chargement d'une fenêtre, du renderer, des textures, d'une caméra
 * et les retournes dans une structure.
 * 
 * Le moteur contient aussi les collisions 
 * 
 * \author Julien Rouaux
 */


#include <stdio.h>
#include <stdlib.h>
#include <moteur.h>
#include <audio.h>
#include <window.h>
#include <textures.h>
#include <camera.h>
#include <liste.h>
#include <sauvegarde.h>


/**
 * \brief Fonction bloquante destinée à bloquer l'exécution du programme pour qu'il
 * puisse tourner à 60 images par secondes, au maximum.
 *
 * Cette fonction actualise les champs du moteur qui concernent le temps. Elle est
 * destinée à être appelée au début de chaque boucles du jeu.
 * 
 * \param moteur Le moteur
 */
void regulerFPS(t_moteur * moteur)
{
    //Réguler FPS
    int tempsEcoule = tempsEcoule = SDL_GetTicks() - moteur->temps;
    if(TEMPS_POUR_CHAQUE_SECONDE > tempsEcoule)
        SDL_Delay(TEMPS_POUR_CHAQUE_SECONDE - tempsEcoule);
    moteur->temps_precedent = moteur->temps;
    moteur->temps = SDL_GetTicks();
}


/**
 * \brief Initialise les parametres.
 * 
 * \param parametres Paramètres du moteur
 */
static void initialiserParams(t_parametres * parametres)
{
    if(chargerSaveParametres(parametres) != SUCCESS)
    {
        printf("Sauvegarde du moteur réinitialisée\n");
        parametres->key_up = SDL_SCANCODE_W; 
        parametres->key_down = SDL_SCANCODE_S; 
        parametres->key_left = SDL_SCANCODE_A;
        parametres->key_right = SDL_SCANCODE_D;
        parametres->key_interaction = SDL_SCANCODE_E;
        parametres->attack_up = SDL_SCANCODE_UP;
        parametres->attack_down = SDL_SCANCODE_DOWN;
        parametres->attack_left = SDL_SCANCODE_LEFT;
        parametres->attack_right = SDL_SCANCODE_RIGHT;
        parametres->dash = SDL_SCANCODE_SPACE;
        parametres->reset_sauvegarde_joueur = FAUX;
        parametres->volume_audio = MIX_MAX_VOLUME; 
    }
}


/**
 * \brief Charge une fenêtre, un rendu, les textures, et une caméra.
 * Charge les paramètres depuis la sauvegarde.
 * 
 * \param temps le temps actuel du jeu
 * \return Structure moteur, NULL si échec.
 */
t_moteur * chargerMoteur(unsigned int temps)
{
    int retour; //Retour de code erreur

    t_moteur * moteur = malloc(sizeof(t_moteur));
    if(moteur == NULL)
    {
        printf("Impossible d'allouer la mémoire pour la structure moteur\n");
        return NULL;
    }

    retour = creerFenetreEtRendu(&moteur->window, &moteur->renderer);
    if(retour != 0)
    {
        printf("Moteur non chargé\n");
        free(moteur);
        return NULL;
    }

    moteur->textures = chargerTextures(moteur->renderer);
    if(moteur->textures == NULL)
    {
        printf("Moteur non chargé\n");
        detruireFenetreEtRendu(&moteur->window, &moteur->renderer);
        free(moteur);
        return NULL;
    }

    moteur->camera = creerCamera(0, 0);
    if(moteur->camera == NULL)
    {
        printf("Moteur non chargé\n");
        detruireTextures(&moteur->textures);
        detruireFenetreEtRendu(&moteur->window, &moteur->renderer);
        free(moteur);
        return NULL;
    }

    initialiserParams(&moteur->parametres);

    if(chargerAudio(moteur->parametres.volume_audio, &moteur->musiques, &moteur->bruitages) != 0)
    {
        printf("Moteur non chargé\n");
        detruireCamera(&moteur->camera);
        detruireTextures(&moteur->textures);
        detruireFenetreEtRendu(&moteur->window, &moteur->renderer);
        free(moteur);
        return NULL;
    }

    //Allouer la liste des entités "vivantes"
    moteur->liste_entites = malloc(sizeof(t_liste));
    if(moteur->liste_entites == NULL)
    {
        printf("Moteur non chargé\n");
        detruireAudio(&moteur->musiques, &moteur->bruitages);
        detruireCamera(&moteur->camera);
        detruireTextures(&moteur->textures);
        detruireFenetreEtRendu(&moteur->window, &moteur->renderer);
        free(moteur);
        return NULL;
    }

    init_liste(moteur->liste_entites);

    moteur->temps_precedent = temps;
    moteur->temps = temps;

    moteur->echelle = 0;
    updateEchelle(moteur);

    moteur->galaxie = NULL;

    return moteur;
}


/**
 * \brief Libère la mémoire allouée pour la structure moteur et mets son 
 * pointeur à NULL. Sauvegarde aussi les paramètres.
 * 
 * \param moteur L'adresse du pointeur du moteur.
 */
void detruireMoteur(t_moteur ** moteur)
{
    if(*moteur != NULL)
    {
        sauvegarderParametres(&(*moteur)->parametres);
        detruireCamera(&(*moteur)->camera);
        detruireTextures(&(*moteur)->textures);
        detruireFenetreEtRendu(&(*moteur)->window, &(*moteur)->renderer);
        detruireAudio(&(*moteur)->musiques, &(*moteur)->bruitages);
        detruire_liste(&(*moteur)->liste_entites);
    }
    free(*moteur);
    *moteur = NULL;
}


/**
 * \brief Calcule la taille en pixel d'un bloc selon la taille de l'écran et
 * actualise les champs du moteur.
 * 
 * \param moteur La structure moteur du jeu
 */
void updateEchelle(t_moteur * moteur)
{
    int l = 1280;
    int h = 720;

    SDL_GetWindowSize(moteur->window, &l, &h);

    moteur->window_height = h;
    moteur->window_width = l;
    
    if(h < l) //Si la hauteur est petite, on se base sur cette dimension
        moteur->echelle = h / (NB_TILE_HAUTEUR + 3); //On laisse un bloc et demi de vide avec les bordures
    
    else //Si la largeur est petite, on se base sur cette dimension
        moteur->echelle = l / (NB_TILE_LARGEUR + 3);

    //Prévenir une échelle qui vaut 0 pour éviter nombreux problèmes de calculs (notamment des divisions par 0)
    if(moteur->echelle == 0)
        moteur->echelle = 1;
}

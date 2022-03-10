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


/**
 * \brief Charge une fenêtre, un rendu, les textures, et une caméra.
 * 
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

    if(chargerAudio(&moteur->musiques, &moteur->bruitages) != 0)
    {
        printf("Moteur non chargé\n");
        detruireCamera(&moteur->camera);
        detruireTextures(&moteur->textures);
        detruireFenetreEtRendu(&moteur->window, &moteur->renderer);
        free(moteur);
        return NULL;
    }

    moteur->temps_precedent = temps;
    moteur->temps = temps;

    moteur->echelle = 0;
    updateEchelle(moteur);

    return moteur;
}


/**
 * \brief Libère la mémoire allouée pour la structure moteur et mets son 
 * pointeur à NULL. 
 * 
 * \param moteur L'adresse du pointeur du moteur.
 */
void detruireMoteur(t_moteur ** moteur)
{
    if(*moteur != NULL)
    {
        detruireCamera(&(*moteur)->camera);
        detruireTextures(&(*moteur)->textures);
        detruireFenetreEtRendu(&(*moteur)->window, &(*moteur)->renderer);
        detruireAudio(&(*moteur)->musiques, &(*moteur)->bruitages)
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

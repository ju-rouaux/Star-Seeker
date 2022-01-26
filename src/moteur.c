/**
 * \file
 * \brief Module de chargement d'une fenêtre, du renderer, des textures, 
 * et les retournes dans une structure.
 * 
 * \author Julien 
 */

#include <stdio.h>
#include <stdlib.h>
#include <moteur.h>
#include <window.h>
#include <textures.h>


/**
 * \brief Charge une fenêtre, un rendu, et les textures. 
 * 
 * \return Structure contenant le pointeur sur window, sur renderer et des textures,
 * NULL si echec.
 */
t_moteur * chargerMoteur()
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
        detruireTextures(&(*moteur)->textures);
        detruireFenetreEtRendu(&(*moteur)->window, &(*moteur)->renderer);
    }
    free(*moteur);
    *moteur = NULL;
}
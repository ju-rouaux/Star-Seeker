#include <stdlib.h>
#include <moteur.h>
#include <window.h>
#include <textures.h>

t_moteur * chargerMoteur()
{
    int retour; //Retour de code erreur

    t_moteur * moteur = malloc(sizeof(t_moteur));
    if(moteur == NULL)
    {
        print("Impossible d'allouer la mémoire pour la structure moteur\n");
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

//PAs sûr de la validité de la fonction
void detruireMoteur(t_moteur ** moteur)
{
    if(*moteur != NULL)
    {
        detruireTextures(&(*moteur)->textures)
        detruireFenetreEtRendu(&(*moteur)->window, &(*moteur)->renderer);
    }
    *moteur = NULL;
}
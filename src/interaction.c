/**
 * \file interaction.c
 * 
 * \brief Entités supportant une interaction par le joueur
 * 
 * \author Julien Rouaux
 */


#include <stdio.h>
#include <stdlib.h>
#include <moteur.h>
#include <joueur.h>
#include <attaque.h>
#include <interaction.h>

/**
 * \brief Fonction d'encapsulation pour dessiner une interaction et 
 * ainsi lui ajouter la donnée de texture car la fonction de création
 * ne permet d'en ajouter une.
 * 
 * \param moteur Le moteur
 * \param interaction L'interaction à traiter
 * 
 * \return 0 si succès, sinon une valeur négative (SDL_Error() pour connaitre l'erreur).
 */
static int dessinerInteraction(t_moteur * moteur, t_interaction * interaction)
{
    interaction->texture = moteur->textures->collectibles;
    return dessinerEntite(moteur, (t_entite*) interaction);
}


/**
 * \brief Exécute l'interaction sur le joueur si elle est possible et si elle est demandée.
 * 
 * \param interaction L'interaction à exécuter
 * \param joueur Le joueur 
 * 
 * \return 0 si aucune interaction n'a eu lieu, 1 si elle a eu lieu mais -1 si destruction.
 */
int interagir(t_interaction * interaction, t_joueur * joueur)
{
    //Si le joueur est sur l'interaction et presse le bouton d'interaction
    if(joueur->flags->interaction == 1 && SDL_HasIntersection(&interaction->hitbox, &joueur->hitbox))
    {
        joueur->flags->interaction = -1;

        if(interaction->type_inter == VIE)
        {
            joueur->pv += interaction->data.nb_pv;
            return -1;
        }
        else if(interaction->type_inter == ARME)
        {
            //Inverser l'attaque du joueur par la nouvelle
            e_nom_attaque tmp;
            tmp = interaction->data.attaque;
            interaction->data.attaque = joueur->nom_attaque;
            joueur->nom_attaque = tmp;
            chargerAttaqueTir(&joueur->attaque_tir_equipee, joueur->nom_attaque);
            return 1;
        }
        else //Type inconnu, détruire
            return -1;
    }
    return 0;
}


/**
 * \brief Création d'une interaction.
 * 
 * \param type La nature de l'interaction désirée
 * \param x La position en x
 * \param y La position en y
 * \param data La donnée associée à l'interaction
 * 
 * \return Le pointeur interaction (NULL si echec).
 */
t_interaction * creerInteraction(e_type_inter type, float x, float y, data_inter data)
{
    t_entite * entite = creerEntite(x, y, NULL);
    t_interaction * interaction = realloc(entite, sizeof(t_interaction));
    if(interaction == NULL)
    {
        printf("Impossible d'allouer la mémoire pour interaction\n");
        detruireEntite(&entite);
        return NULL;
    }
    entite = NULL;

    interaction->type = E_INTERACTION;
    interaction->type_inter = type;

    if(type == VIE)
    {
        interaction->id_animation = 1;
        interaction->animation = creerAnimation(50, 16);
        interaction->data.nb_pv = data.nb_pv;
    }
    else if(type == ARME)
    {
        interaction->taille = 0.5;
        interaction->id_animation = 0;
        interaction->animation = creerAnimation(100, 4);
        interaction->data.attaque = data.attaque;
    }

    interaction->dessiner = (int (*)(t_moteur*, t_entite*)) dessinerInteraction;

    return interaction;
}
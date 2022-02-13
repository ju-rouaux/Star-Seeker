/**
 * \file
 * \brief Module facilitant la gestion des animations
 * 
 * \author Julien Rouaux
 */

#include <stdio.h>
#include <stdlib.h>
#include <animation.h>

/**
 * \brief Actualise l'animation si nécéssaire
 * 
 * \param animation L'animation à actualiser
 * \param temps Le temps actuel du jeu
 */
void updateAnimation(t_animation * animation, unsigned int temps)
{
    if(animation != NULL)
    {
        if(temps > animation->dernier_update + animation->vitesse) //Si on a avancé de "vitesse" dans le temps, passer à l'image suivante
        {
            (animation->indice_texture)++;
            if(animation->indice_texture >= animation->nb_textures)
                animation->indice_texture = 0;
            animation->dernier_update = temps;
        }
    }
}


/**
 * \brief Génère une structure permettant d'animer un objet.
 * 
 * \param vitesse Temps en milisecondes avant le passage à la frame suivante de l'animation
 * \param nb_textures Nombre de frames différentes d'une animation
 * \param id_max Identifiant de l'animation la plus élevée
 * 
 * \return La structure ou NULL si échec.
 */
t_animation * creerAnimation(int vitesse, int nb_textures, int id_max)
{
    t_animation * animation = malloc(sizeof(t_animation));
    if(animation == NULL)
    {
        printf("Impossible d'allouer la mémoire pour une animation\n");
        return NULL;
    }

    animation->vitesse = vitesse;
    animation->nb_textures = nb_textures;
    animation->id_max = id_max;

    animation->indice_texture = 0;
    animation->dernier_update = 0;

    return animation;
}


/**
 * \brief Détruit une structure animation et mets le pointeur à NULL.
 * 
 * \param animation L'adresse du pointeur animation
 */
void detruireAnimation(t_animation ** animation)
{
    if(*animation != NULL)
    {
        free(*animation);
    }
    *animation = NULL;
}
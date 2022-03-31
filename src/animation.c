/**
 * \file animation.c
 * 
 * \brief Module facilitant la gestion des animations.
 * 
 * Ce module utilise les configurations données dans la structure t_animation pour
 * se charger d'animer une texture avec updateAnimation.
 * 
 * \author Julien Rouaux
 */


#include <stdio.h>
#include <stdlib.h>
#include <animation.h>


/**
 * \brief Actualise l'animation si nécessaire selon la configuration de la structure.
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
            if(animation->indice_texture >= animation->nb_textures) //Reboucler si nécessaire
                animation->indice_texture = 0;
            animation->dernier_update = temps; //Enregistrer le temps 
        }
    }
}


/**
 * \brief Génère une structure permettant d'animer un objet.
 * 
 * Il est possible qu'une entité ne possède pas d'animation (pointeur NULL). Dans ce
 * cas le champ id_animation permet de sélectionner la bonne partie de la texture.
 * 
 * \param vitesse Temps en milisecondes avant le passage à la frame suivante de l'animation
 * \param nb_textures Nombre de frames différentes d'une animation
 * 
 * \return La structure animation ou NULL si échec.
 */
t_animation * creerAnimation(int vitesse, int nb_textures)
{
    t_animation * animation = malloc(sizeof(t_animation));
    if(animation == NULL)
    {
        printf("Impossible d'allouer la mémoire pour une animation\n");
        return NULL;
    }

    animation->vitesse = vitesse;
    animation->nb_textures = nb_textures;

    animation->indice_texture = 0;
    animation->dernier_update = 0;

    return animation;
}


/**
 * \brief Détruit une structure animation et mets son pointeur à NULL.
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
/**
 * \file animation.h
 * 
 * \brief Module facilitant la gestion des animations.
 * 
 * Ce module utilise les configurations données dans la structure t_animation pour
 * se charger d'animer une texture avec updateAnimation.
 * 
 * \author Julien Rouaux
 */

#ifndef _JEU_ANIMATION_
#define _JEU_ANIMATION_


/**
 * \struct t_animation
 * \brief Structure contenant les données nécessaires
 * à la réalisation d'une animation.
 * 
 * Les champs de cette structure ne sont pas destinés à être changés
 * après l'appel de la fonction de création.
 */
typedef struct s_animation
{
    int vitesse; /**< Temps en milisecondes avant le passage à l'image suivante */
    int nb_textures; /** Nombre d'images sur une ligne du tileset */
    int indice_texture; /** Indice de l'image active de l'animation courante */
    unsigned int dernier_update; /**< Temps qu'il était au moment du changement vers la l'image courante */
} t_animation;


void updateAnimation(t_animation * animation, unsigned int temps);
t_animation * creerAnimation(int vitesse, int nb_textures);
void detruireAnimation(t_animation ** animation);

#endif //_JEU_ANIMATION_
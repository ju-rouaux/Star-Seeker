#ifndef _JEU_ANIMATION_
#define _JEU_ANIMATION_

/**
 * \brief Structure contenant les données nécéssaires
 * à la réalisation d'une animation.
 */
typedef struct
{
    int vitesse; /**< Temps en milisecondes avant l'image suivante */
    unsigned int dernier_update; /**< Temps qu'il était au changement de la frame courante */
    int nb_textures; /** Nombre d'images sur une ligne du tileset */
    int indice_texture; /** Indice de l'image active de l'animation courante */
    int id_max; /** Nombre de lignes du tileset (pour des mesures du prévention) */
} t_animation;

t_animation * creerAnimation(int vitesse, int nb_textures, int id_max);
void detruireAnimation(t_animation ** animation);
void updateAnimation(t_animation * animation, unsigned int temps);

#endif
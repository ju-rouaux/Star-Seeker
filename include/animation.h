#ifndef _JEU_ANIMATION_
#define _JEU_ANIMATION_

/**
 * \brief Structure contenant les données nécéssaires
 * à la réalisation d'une animation
 * 
 */
typedef struct
{
    int vitesse; /**< Temps en milisecondes avant l'image suivante */
    unsigned int dernier_update; /**< Temps qu'il était au changement de la frame courante */
    
} t_animation;

t_animation * creerAnimation(int vitesse);
void detruireAnimation(t_animation ** animation);

#endif
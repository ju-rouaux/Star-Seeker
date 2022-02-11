#include <stdio.h>
#include <stdlib.h>
#include <animation.h>

t_animation * creerAnimation(float vitesse)
{
    t_animation * animation = malloc(sizeof(t_animation));
    if(animation == NULL)
    {
        printf("Impossible d'allouer la mémoire pour une animation\n");
        return NULL;
    }

    animation->dernier_update = 0;
    animation->vitesse = vitesse;

    return animation;
}

void detruireAnimation(t_animation ** animation)
{
    if(*animation != NULL)
    {
        free(*animation);
    }
    *animation = NULL;
}
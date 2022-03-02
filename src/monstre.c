/**
 * 
 * 
 *  EN DEVELOPPEMENT
 * 
 */

#include <stdio.h>
#include <monstre.h>


t_monstre * creerMonstre(float x, float y, float taille, SDL_Texture * apparence)
{
    t_entite * entite = creerEntite(x, y, apparence);
    t_monstre * monstre = realloc(entite, sizeof(t_monstre));
    if(monstre == NULL)
    {
        printf("Impossible d'allouer la mémoire pour monstre\n");
        detruireEntite(&entite);
        return NULL;
    }
    entite = NULL;

    monstre->animation = creerAnimation(50, 4, 15); //Changer les paramètres d'animation si on ajoute des animations
    if(monstre->animation == NULL)
    {
        printf("Le monstre n'a pas pu être créé\n");
        free(monstre);
        return NULL;
    }

    monstre->x = x;
    monstre->y = y;
    monstre->direction_vx = 0;
    monstre->direction_vy = 0;
    monstre->vitesse = 1;
    monstre->type = E_MONSTRE;

    monstre->texture = apparence;
    monstre->taille = taille;
    monstre->id_animation = 0; //idle

    monstre->update = (int (*)(t_moteur*, t_entite*)) NULL;
    monstre->detruire = (void (*)(t_entite**)) NULL;

    monstre->pv = 100;

    monstre->hitbox.h = 0;
    monstre->hitbox.w = 0;
    monstre->hitbox.x = 0;
    monstre->hitbox.y = 0;

    return monstre;
}
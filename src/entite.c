#include <SDL2/SDL.h>
#include <moteur.h>
#include <entite.h>
#include <animation.h>

/**
 * \brief Dessine l'entité à ses coordonnées, tout en gérant son animation s'il en possède une
 * 
 * \param moteur Structure moteur du jeu
 * \param entite L'entité à afficher
 * 
 * \return 0 si succès, sinon une valeur négative (SDL_Error() pour connaitre l'erreur)
 */
int dessinerEntite(t_moteur * moteur, t_entite * entite)
{
    SDL_Rect destination;
    SDL_Rect source;

    destination.h = moteur->camera->echelle * entite->taille;
    destination.w = moteur->camera->echelle * entite->taille;
    
    //Ainsi les coordonnées des entités, se situent au centre en bas de l'image
    destination.x = moteur->camera->echelle*(entite->x - moteur->camera->x) - destination.w / 2;
    destination.y = moteur->camera->echelle*(entite->y - moteur->camera->y) - destination.h;

    if(entite->animation != NULL) //Si l'entité est animé
        updateAnimation(entite->animation, moteur->temps);

    splitTexture(&source, entite->animation->indice_texture, entite->id_animation);

    return SDL_RenderCopy(moteur->renderer, entite->texture, &source, &destination);
}

int deplacerEntite(t_moteur * moteur, t_entite * entite)
{
    SDL_Rect hitbox;
    int i;
    int collision = 0; //Faux
    float distance = entite->vitesse * (moteur->temps - moteur->temps_precedent) / 1000;
    float futur_x = entite->x + distance * entite->direction_vx;
    float futur_y = entite->y + distance * entite->direction_vy;

    //Taille de la hitbox
    hitbox.w = entite->taille/3 * moteur->camera->echelle;
    hitbox.h = entite->taille/8 * moteur->camera->echelle;

    //Collision axe x
    hitbox.x = moteur->camera->echelle * (futur_x - moteur->camera->x) - hitbox.w / 2;
    hitbox.y = moteur->camera->echelle * (entite->y - moteur->camera->y) - 3*hitbox.h / 4;
    i = 0;
    while(i < moteur->taille_collisions && !SDL_HasIntersection(&hitbox,&moteur->collisions[i]))
        i++;

    if(i != moteur->taille_collisions)
        collision = 1; //Vrai
    else
        entite->x = futur_x;

    //Collision axe y
    hitbox.x = moteur->camera->echelle * (entite->x - moteur->camera->x) - hitbox.w / 2;
    hitbox.y = moteur->camera->echelle * (futur_y - moteur->camera->y) - 3*hitbox.h /4;
    i = 0;
    while(i < moteur->taille_collisions && !SDL_HasIntersection(&hitbox,&moteur->collisions[i]))
        i++;

    if(i != moteur->taille_collisions)
        collision = 1; //Vrai
    else
        entite->y = futur_y;

    return collision;
}
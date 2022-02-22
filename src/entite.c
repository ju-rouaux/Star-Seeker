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
    
    destination.x = entite->x*moteur->camera->echelle - moteur->camera->x*moteur->camera->echelle - destination.w / 2;
    destination.y = entite->y*moteur->camera->echelle - moteur->camera->y*moteur->camera->echelle - 3*destination.h/ 4;

    if(entite->animation != NULL) //Si l'entité est animé
        updateAnimation(entite->animation, moteur->temps);

    splitTexture(&source, entite->animation->indice_texture, entite->id_animation);

    return SDL_RenderCopy(moteur->renderer, entite->texture, &source, &destination);
}
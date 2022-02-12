#include <SDL2/SDL.h>
#include <moteur.h>
#include <entite.h>

/**
 * \brief Dessine l'entité à ses coordonnées
 * 
 * \param moteur Structure moteur du jeu
 * \param entite L'entité à afficher
 * \param texture_ligne Si désiré, changer la ligne du tileset (sinon mettre 0 par défaut)
 * 
 * \return 0 si succès, sinon une valeur négative (SDL_Error() pour connaitre l'erreur)
 */
int dessinerEntite(t_moteur * moteur, t_entite * entite, int texture_ligne)
{
    SDL_Rect destination;
    SDL_Rect source;

    destination.h = moteur->camera->echelle * entite->taille;
    destination.w = moteur->camera->echelle * entite->taille;
    
    destination.x = entite->x*moteur->camera->echelle - moteur->camera->x - destination.w / 2;
    destination.y = entite->y*moteur->camera->echelle - moteur->camera->y - 3*destination.h/ 4;

    splitTexture(&source, entite->partie_texture_courrante, texture_ligne);

    return SDL_RenderCopy(moteur->renderer, entite->texture, &source, &destination);
}

void textureSuivante(t_entite * entite)
{
    (entite->partie_texture_courrante)++;
    if(entite->partie_texture_courrante >= entite->nb_textures)
        entite->partie_texture_courrante = 0;
}
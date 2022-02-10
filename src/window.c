/**
 * \file
 * \brief Module de création de la fenêtre du jeu et son rendu
 * \author Julien
*/

#include <stdio.h>
#include <SDL2/SDL.h>

/**
 * Génère une fenêtre et son rendu, pour les mettre dans 
 * les pointeurs donnés en paramètre.
 * 
 * \param window L'adresse du pointeur de fenêtre
 * \param renderer L'adresse du pointeur de rendu
 * 
 * \return 0 si tout s'est bien passé, sinon une valeur négative
*/
int creerFenetreEtRendu(SDL_Window ** window, SDL_Renderer ** renderer)
{
    (*window) = SDL_CreateWindow("Star Seeker", 
                    SDL_WINDOWPOS_CENTERED, 
                    SDL_WINDOWPOS_CENTERED,
                    1280,
                    720,
                    SDL_WINDOW_RESIZABLE);
    
    if(*window == NULL)
    {
        printf("Impossible de créer la fenêtre : %s\n", SDL_GetError());
        return -1;
    }

    (*renderer) = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);

    if(*renderer == NULL)
    {
        printf("Impossible de créer le rendu : %s\n", SDL_GetError());
        SDL_DestroyWindow(*window);
        return -2;
    }

    return 0;
}

/**
 * Libère la mémoire allouée pour la fenêtre et son rendu, et met les
 * pointeurs à NULL.
 * 
 * \param window L'adresse du pointeur de fenêtre
 * \param renderer L'adresse du pointeur de rendu
*/
void detruireFenetreEtRendu(SDL_Window ** window, SDL_Renderer ** renderer)
{
    if(*renderer != NULL)
    {
        SDL_DestroyRenderer(*renderer);
        (*renderer) = NULL;
    }

    if(*window != NULL)
    {
        SDL_DestroyWindow(*window);
        (*window) = NULL;
    }
}
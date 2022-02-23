#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <moteur.h>
#include <partie.h>

int main(int argc, char * argv[])
{

    t_moteur * moteur = NULL;

    if(SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        printf("Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    moteur = chargerMoteur(SDL_GetTicks());

    chargerPartie(moteur);

    detruireMoteur(&moteur);

    SDL_Quit();
    return 0;

}

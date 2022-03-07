#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <moteur.h>
#include <partie.h>
#include <generation_niveau.h>
#include <menu.h>

int main(int argc, char * argv[])
{
    
    t_moteur * moteur = NULL;
    t_menu * menu = NULL;

     if(SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        printf("Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    moteur = chargerMoteur(SDL_GetTicks());
    menu = chargerMenu(moteur);
    SDL_Delay(5000);
    chargerPartie(moteur, 1);
    
    

    detruireMoteur(&moteur);

    return 0;

}

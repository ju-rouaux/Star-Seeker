#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <window.h>
#include <generation_niveau.h>
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              
int main(int argc, char * argv[])
{


    
    t_couleurRVB * couleur = malloc(sizeof(t_couleurRVB));

    for (int i = 0; i < 20; i++){
        couleur_aleatoire(couleur);

        printf("%d %d %d \n", couleur->rouge, couleur->vert, couleur->bleu);
    
    }

    
    /*
    char * nom_planete = "ziofefez";

    creer_niveau("test.niv", nom_planete);






    SDL_Window * window = NULL;
    SDL_Renderer * renderer = NULL;
    
    if(SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        printf("Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    
    creerFenetreEtRendu(&window, &renderer);
    SDL_Delay(5000);
    detruireFenetreEtRendu(&window, &renderer);
    
    SDL_Quit();

    */

    return 0;
}
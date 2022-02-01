#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <moteur.h>
#include <niveau.h>
#include <rendu_niveau.h>
#include <event.h>
#include <player.h>
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              
int main(int argc, char * argv[])
{
    t_moteur * moteur = NULL;
    t_camera * camera = NULL;
    SDL_Event event;
    move * player = malloc(sizeof(move));
    player -> x = 0;
    player -> y = 0;
    if(SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        printf("Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    moteur = chargerMoteur();
    camera = creerCamera(moteur->window, 0,0);
    FILE * fichier = fopen("./test/allure_d'un_niveau.txt", "r");
    if(fichier == NULL)
    {
        printf("mince");
        return EXIT_FAILURE;
    }
    t_niveau * niveau = chargerNiveau(fichier);

    while(handleEvents(event) != 1){
        //Logic here
        //deplacer joueur
        //check position par rapport ancien rendu
        //si collision remttre joueur au meme endroit
        //rendu niveau
        //rendu joueur
        move_player( & event, player);
        SDL_RenderClear(moteur->renderer);
        afficherNiveau(moteur, niveau, camera);
        SDL_RenderPresent(moteur->renderer);
        SDL_Delay(10);
    }

    detruireMoteur(&moteur);

    free(player);


    SDL_Quit();
    return 0;

}
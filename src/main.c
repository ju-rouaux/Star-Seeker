#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <moteur.h>
#include <niveau.h>
#include <rendu_niveau.h>
#include <event.h>
#include <joueur.h>
#include <rendu_joueur.h>
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              
int main(int argc, char * argv[])
{
    t_moteur * moteur = NULL;
    t_camera * camera = NULL;
    t_niveau * niveau = NULL;
    t_joueur * joueur = NULL;
    
    int debutBoucle, tempsEcoule;

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
    camera = creerCamera(moteur->window, 0, 0);

    if(lancerNiveau(fichier, moteur, &niveau, &joueur, camera->echelle) != 0) return EXIT_FAILURE;
    updateCamera(camera, niveau->salle_chargee->dimensions, niveau->salle_chargee->dimensions->j*NB_TILE_LARGEUR*camera->echelle, niveau->salle_chargee->dimensions->i*NB_TILE_HAUTEUR*camera->echelle, joueur->position->x, joueur->position->y);

    while(handleEvents(joueur) != 1)
    {
        debutBoucle = SDL_GetTicks();
        //Logic here
        //deplacer joueur
        //check position par rapport ancien rendu
        //si collision remttre joueur au meme endroit
        //rendu niveau
        //rendu joueur
        updatePositionJoueur(joueur, camera->echelle);
        updateNiveau(niveau, joueur, camera->echelle);
        SDL_RenderClear(moteur->renderer);
        afficherNiveau(moteur, niveau, camera, joueur->position->x, joueur->position->y);
        dessinerJoueur(moteur, joueur, camera);
        
        SDL_RenderPresent(moteur->renderer);

        //Réguler FPS
        tempsEcoule = SDL_GetTicks() - debutBoucle;
        if(TEMPS_POUR_CHAQUE_SECONDE > tempsEcoule)
            SDL_Delay(TEMPS_POUR_CHAQUE_SECONDE - tempsEcoule);
        
        // inputs : printf("%i %i %i %i\n", joueur->flags->to_up, joueur->flags->to_down, joueur->flags->to_left, joueur->flags->to_right);
    }

    arreterNiveau(&niveau);
    detruireCamera(&camera);
    detruireMoteur(&moteur);

    SDL_Quit();
    return 0;

}
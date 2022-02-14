#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <moteur.h>
#include <camera.h>
#include <event.h>
#include <niveau.h>
#include <joueur.h>
#include <rendu_niveau.h>
#include <entite.h>
//#include <rendu_joueur.h>
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              
int main(int argc, char * argv[])
{
    t_moteur * moteur = NULL;
    t_niveau * niveau = NULL;
    t_joueur * joueur = NULL;
    
    int tempsEcoule;

    if(SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        printf("Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    moteur = chargerMoteur(SDL_GetTicks());
    FILE * fichier = fopen("./test/allure_d'un_niveau.txt", "r");
    if(fichier == NULL)
    {
        printf("mince");
        return EXIT_FAILURE;
    }

    if(lancerNiveau(fichier, moteur, &niveau) != 0) return EXIT_FAILURE;
    joueur = creerJoueur(niveau->salle_chargee->dimensions->j*NB_TILE_LARGEUR, niveau->salle_chargee->dimensions->i*NB_TILE_HAUTEUR, moteur->textures->player);
    if(joueur == NULL)
    {
        printf("Le niveau n'a pas pu être lancé\n");
        return -1;
    }
    updateCamera(moteur->camera, niveau->salle_chargee->dimensions->largeur, niveau->salle_chargee->dimensions->hauteur, niveau->salle_chargee->dimensions->j*NB_TILE_LARGEUR*moteur->camera->echelle, niveau->salle_chargee->dimensions->i*NB_TILE_HAUTEUR*moteur->camera->echelle, joueur->x, joueur->y);
    int id_salle_courante;
    while(handleEvents(joueur) != 1)
    {
        moteur->temps_precedent = moteur->temps;
        moteur->temps = SDL_GetTicks();
        SDL_RenderClear(moteur->renderer);
        
        //Logic here
        //Actualiser joueur (et tester collisions)
        joueur->update(moteur, (t_entite*) joueur);
        //Actualiser liste entités
        ///...
        //Actualiser niveau
        id_salle_courante = niveau->salle_chargee->id_salle;
        updateNiveau(niveau, joueur->x, joueur->y,moteur->camera->echelle);
        
        //Actualiser caméra
        updateCamera(moteur->camera, niveau->salle_chargee->dimensions->largeur, niveau->salle_chargee->dimensions->hauteur, niveau->salle_chargee->dimensions->j*NB_TILE_LARGEUR*moteur->camera->echelle, niveau->salle_chargee->dimensions->i*NB_TILE_HAUTEUR*moteur->camera->echelle, joueur->x, joueur->y);
        
        //Rendu niveau
        afficherNiveau(moteur, niveau, joueur->x, joueur->y);
        //rendu joueur
        joueur->dessiner(moteur, (t_entite*) joueur);
        //Rendu entités
        //...

        //Afficher frame
        SDL_RenderPresent(moteur->renderer);

        //Réguler FPS
        tempsEcoule = SDL_GetTicks() - moteur->temps;
        if(TEMPS_POUR_CHAQUE_SECONDE > tempsEcoule)
            SDL_Delay(TEMPS_POUR_CHAQUE_SECONDE - tempsEcoule);
    }

    arreterNiveau(&niveau);
    detruireMoteur(&moteur);

    SDL_Quit();
    return 0;

}
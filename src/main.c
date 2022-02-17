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
    joueur = creerJoueur(niveau->salle_chargee->dimensions->j*NB_TILE_LARGEUR + 5, niveau->salle_chargee->dimensions->i*NB_TILE_HAUTEUR + 3, moteur->textures->player);
    if(joueur == NULL)
    {
        printf("Le niveau n'a pas pu être lancé\n");
        return -1;
    }
    updateCamera(moteur->camera, niveau->salle_chargee->dimensions->largeur, niveau->salle_chargee->dimensions->hauteur, niveau->salle_chargee->dimensions->j, niveau->salle_chargee->dimensions->i, joueur->x, joueur->y);
    int id_salle_courante;
    while(handleEvents(joueur) != 1)
    {
        moteur->temps_precedent = moteur->temps;
        moteur->temps = SDL_GetTicks();
        SDL_RenderClear(moteur->renderer);
        updateScale(moteur->window, moteur->camera);
        //Logic here
        //Actualiser joueur (et tester collisions)
        joueur->update(moteur, (t_entite*) joueur);
        //Actualiser liste entités
        ///...
        //Actualiser niveau
        id_salle_courante = niveau->salle_chargee->id_salle;
        updateNiveau(niveau, joueur->x, joueur->y,moteur->camera->echelle);
        
        //Si on change de niveau -> animation
        if(id_salle_courante != niveau->salle_chargee->id_salle) //Animation changement de salle à mettre dans une fonction à l'avenir
        {
            int direction_x, direction_y;

            //Sauvegarder et détruire entités ici

            //Charger nouvelles entités ici

            //Detruire anciennes collisions
            if(moteur->collisions != NULL)
            {
                free(moteur->collisions);
                moteur->collisions = NULL;
                moteur->taille_collisions = 0;
            }

            //Caluler future position
            updateFutureCamera(moteur->camera, niveau->salle_chargee->dimensions->largeur, niveau->salle_chargee->dimensions->hauteur, niveau->salle_chargee->dimensions->j, niveau->salle_chargee->dimensions->i, joueur->x, joueur->y);
        
            //Animer
            while(moteur->camera->x != moteur->camera->futur_x || moteur->camera->y != moteur->camera->futur_y)
            {
                moteur->temps = SDL_GetTicks();

                //Calcul position caméra
                direction_x = moteur->camera->x == moteur->camera->futur_x ? 0 : (moteur->camera->x < moteur->camera->futur_x ? 1 : -1); //Sens où se diriger
                direction_y = moteur->camera->y == moteur->camera->futur_y ? 0 : (moteur->camera->y < moteur->camera->futur_y ? 1 : -1);

                //C'est ici qu'on peut changer la vitesse
                moteur->camera->x += 0.85 * direction_x; //Environ deux fois plus rapide car une salle est environ 2 fois plus grande en largeur qu'en hauteur
                moteur->camera->y += 0.5 * direction_y;

                if(abs(moteur->camera->futur_x - moteur->camera->x) <= 0.5)
                    moteur->camera->x = moteur->camera->futur_x;

                if(abs(moteur->camera->futur_y - moteur->camera->y) <= 0.5)
                    moteur->camera->y = moteur->camera->futur_y;


                //Rafraichir rendu
                SDL_RenderClear(moteur->renderer);
                afficherNiveau(moteur, niveau, joueur->x, joueur->y);
               
                dessinerEntite(moteur, (t_entite*) joueur);
                //Dessiner entités ici

                SDL_RenderPresent(moteur->renderer);

                //Réguler FPS
                tempsEcoule = SDL_GetTicks() - moteur->temps;
                if(TEMPS_POUR_CHAQUE_SECONDE > tempsEcoule)
                    SDL_Delay(TEMPS_POUR_CHAQUE_SECONDE - tempsEcoule);
            }
            
            //Reset la future position
            moteur->camera->futur_x = 0;
            moteur->camera->futur_y = 0;
        }     
        
        //Actualiser caméra
        updateCamera(moteur->camera, niveau->salle_chargee->dimensions->largeur, niveau->salle_chargee->dimensions->hauteur, niveau->salle_chargee->dimensions->j, niveau->salle_chargee->dimensions->i, joueur->x, joueur->y);
        
        //Rendu niveau
        afficherNiveau(moteur, niveau, joueur->x, joueur->y);


        //Afficher collisions DEBUG
        
        if(moteur->collisions!=NULL)
            for(int b = 0; b < moteur->taille_collisions; b++)
                SDL_RenderDrawRect(moteur->renderer, &(moteur->collisions[b]));
        

        //rendu joueur
        dessinerEntite(moteur, (t_entite*) joueur);
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
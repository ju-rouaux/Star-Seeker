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
    updateCamera(moteur->camera, niveau->salle_chargee->dimensions->largeur, niveau->salle_chargee->dimensions->hauteur, niveau->salle_chargee->dimensions->j, niveau->salle_chargee->dimensions->i, joueur->x, joueur->y);
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
        
        if(id_salle_courante != niveau->salle_chargee->id_salle) //Animation changement de salle
        {
            //Sauvegarder et détruire entités ici

            //Charger nouvelles entités ici


            //Caluler future position
            updateFutureCamera(moteur->camera, niveau->salle_chargee->dimensions->largeur, niveau->salle_chargee->dimensions->hauteur, niveau->salle_chargee->dimensions->j, niveau->salle_chargee->dimensions->i, joueur->x, joueur->y);
            
            while(moteur->camera->x != moteur->camera->futur_x || moteur->camera->y != moteur->camera->futur_y)
            {
                moteur->temps = SDL_GetTicks();
                int direction_x = moteur->camera->x == moteur->camera->futur_x ? 0 : (moteur->camera->x < moteur->camera->futur_x ? 1 : -1);
                int direction_y = moteur->camera->y == moteur->camera->futur_y ? 0 : (moteur->camera->y < moteur->camera->futur_y ? 1 : -1);

                moteur->camera->x += 3*moteur->camera->echelle * direction_x;
                moteur->camera->y += 3*moteur->camera->echelle * direction_y;

                if(abs(moteur->camera->futur_x) < abs(moteur->camera->x))
                    moteur->camera->x = moteur->camera->futur_x;

                if(abs(moteur->camera->futur_y) < abs(moteur->camera->y))
                    moteur->camera->y = moteur->camera->futur_y;

                SDL_RenderClear(moteur->renderer);
                afficherNiveau(moteur, niveau, joueur->x, joueur->y);
                joueur->id_animation = 0; //Réinitialiser l'animation courante pour éviter de voir le joueur se déplacer dans le vide
                joueur->dessiner(moteur, (t_entite*) joueur);
                //Dessiner entités ici

                SDL_RenderPresent(moteur->renderer);

                //Réguler FPS
                tempsEcoule = SDL_GetTicks() - moteur->temps;
                if(TEMPS_POUR_CHAQUE_SECONDE > tempsEcoule)
                    SDL_Delay(TEMPS_POUR_CHAQUE_SECONDE - tempsEcoule);
            }
        }

            /*
            int debutBoucleT = SDL_GetTicks();
            int debutBoucle;
            float distance = (float)VITESSE_TRANSITION * (moteur->temps - debutBoucleT) / 1000;
            printf("\n%f %f | %f %f\n", moteur->camera->x, moteur->camera->y, moteur->camera->futur_x, moteur->camera->futur_y);
            while(moteur->camera->x != moteur->camera->futur_x || moteur->camera->y != moteur->camera->futur_y)
            {
                debutBoucle = SDL_GetTicks();
                distance = (float)VITESSE_TRANSITION * (moteur->temps - debutBoucleT) / 1000;
                int direction_x = moteur->camera->futur_x < moteur->camera->x ? 1 : -1;
                int direction_y = moteur->camera->futur_y < moteur->camera->y ? 1 : -1;
                printf("%i %i %i\n", direction_x, direction_y);
                moteur->camera->x += distance * direction_x;
                moteur->camera->y += distance * direction_y; 

                if(abs(moteur->camera->futur_x) < abs(moteur->camera->x))
                {
                    moteur->camera->x = moteur->camera->futur_x;
                    //printf("o");
                }
                if(abs(moteur->camera->futur_y) < abs(moteur->camera->y))
                {
                    moteur->camera->y = moteur->camera->futur_y;
                    //printf("a");
                }
                //printf("e");

                SDL_RenderClear(moteur->renderer);
                afficherNiveau(moteur, niveau, joueur->x, joueur->y);
                joueur->dessiner(moteur, (t_entite*) joueur);
                //Dessiner entités ici

                SDL_RenderPresent(moteur->renderer);

                //Réguler FPS
                tempsEcoule = SDL_GetTicks() - debutBoucle;
                if(TEMPS_POUR_CHAQUE_SECONDE > tempsEcoule)
                    SDL_Delay(TEMPS_POUR_CHAQUE_SECONDE - tempsEcoule);

                debutBoucle = SDL_GetTicks();
            }

            moteur->camera->futur_x = 0;
            moteur->camera->futur_y = 0;
        }

            

                Calculer combien dois-je avoir avancé depuis le début de la frame

                Jusqu'à la fin du temps donné

            
            





            
            //Déplacer
            int debutBoucle = SDL_GetTicks();

            int avancer_x = (moteur->camera->futur_x - moteur->camera->x) / 40;
            int avancer_y = (moteur->camera->futur_y - moteur->camera->y) / 40;

            while(moteur->camera->x != moteur->camera->futur_x || moteur->camera->y != moteur->camera->futur_y)
            ;
            while(moteur->temps + DUREE_ANIMATION_CHANGEMENT_SALLE < debutBoucle)
            {
                int tempsRestant = moteur->temps + DUREE_ANIMATION_CHANGEMENT_SALLE - debutBoucle
                int distanceRestante_x = moteur->camera->futur_x - moteur->camera->x;
                int distanceRestante_y = moteur->camera->futur_y - moteur->camera->y;
                
                moteur->camera->x += avancer_x;
                moteur->camera->y += avancer_y;
                
                if(abs(moteur->camera->futur_x) < abs(moteur->camera->x) || abs(moteur->camera->futur_y) < abs(moteur->camera->y))
                {
                    moteur->camera->x = moteur->camera->futur_x;
                    moteur->camera->y = moteur->camera->futur_y;
                    moteur->camera->futur_x = 0;
                    moteur->camera->futur_y = 0;
                }

                SDL_RenderClear(moteur->renderer);
                afficherNiveau(moteur, niveau, joueur->x, joueur->y);
                joueur->dessiner(moteur, (t_entite*) joueur);
                //Dessiner entités ici

                SDL_RenderPresent(moteur->renderer);

                //Réguler FPS
                tempsEcoule = SDL_GetTicks() - debutBoucle;
                if(TEMPS_POUR_CHAQUE_SECONDE > tempsEcoule)
                    SDL_Delay(TEMPS_POUR_CHAQUE_SECONDE - tempsEcoule);

                debutBoucle = SDL_GetTicks();
            }*/
        
        
        //Actualiser caméra
        updateCamera(moteur->camera, niveau->salle_chargee->dimensions->largeur, niveau->salle_chargee->dimensions->hauteur, niveau->salle_chargee->dimensions->j, niveau->salle_chargee->dimensions->i, joueur->x, joueur->y);
        
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
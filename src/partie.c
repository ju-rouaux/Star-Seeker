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
#include <liste.h>

//debug
#include <projectiles.h>
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               
static int jouerNiveau(t_moteur * moteur, t_joueur * joueur)
{
    t_niveau * niveau = moteur->niveau_charge;
    t_liste * liste_entites = niveau->liste_entites;
    t_entite * entite_courante;
    
    int tempsEcoule;
    int id_salle_courante;

    //t_projectile * proj = creerProjectile(BALLE, 0, 0, 0, 0, E_MONSTRE, moteur->textures->projectiles);
    //ajout_droit(liste_entites, (t_entite*) proj);
    //printf("cible : %i, x : %f, y : %f, vx : %f, vy : %f, dureevie : %i, vitesse : %f", proj->cible, proj->x, proj->y, proj->direction_vx, proj->direction_vy, proj->duree_de_vie, proj->vitesse);
    //detruireProjectile(&proj);
    
    while(handleEvents(joueur) != 1)
    {
        moteur->temps_precedent = moteur->temps;
        moteur->temps = SDL_GetTicks();
        SDL_RenderClear(moteur->renderer);
        updateEchelle(moteur);

        //Actualiser l'état des entités
        joueur->update(moteur, (t_entite*) joueur); //Joueur
        if(!liste_vide(liste_entites)) //Liste
        {
            en_tete(liste_entites);
            while(!hors_liste(liste_entites))
            {
                valeur_elt(liste_entites, &entite_courante);
                if(entite_courante != NULL)
                {
                    if(entite_courante->update(moteur, entite_courante) == -1)
                    {
                        entite_courante->detruire((t_entite**) &entite_courante);
                        oter_elt(liste_entites);
                    }
                }
                else
                    oter_elt(liste_entites);
                suivant(liste_entites);
                entite_courante = NULL;
            }
        }

        //Faire subir les dégâts 
        ///...


        //Actualiser niveau
        id_salle_courante = niveau->salle_chargee->id_salle;
        updateNiveau(niveau, joueur->x, joueur->y, moteur->echelle);
        
        //Si on change de niveau -> animation
        if(id_salle_courante != niveau->salle_chargee->id_salle) //Animation changement de salle à mettre dans une fonction à l'avenir
        {
            int direction_x, direction_y;

            //Actualiser la liste des entités vivantes
            en_queue(liste_entites);
            while(!liste_vide(liste_entites))    //Destruction
                oter_elt(liste_entites);

            //Chargement des nouvelles
            for(int i = 0; i < NB_TILE_HAUTEUR; i++)
                for(int j = 0; j < NB_TILE_LARGEUR; j++)
                    if(niveau->salle_chargee->entites[i][j] != NULL)
                        ajout_droit(liste_entites, niveau->salle_chargee->entites[i][j]);

            //Detruire anciennes collisions
            if(moteur->niveau_charge->collisions != NULL)
            {
                free(moteur->niveau_charge->collisions);
                moteur->niveau_charge->collisions = NULL;
                moteur->niveau_charge->taille_collisions = 0;
            }

            //Caluler future position
            updateFutureCamera(moteur, niveau->salle_chargee->dimensions->largeur, niveau->salle_chargee->dimensions->hauteur, niveau->salle_chargee->dimensions->j, niveau->salle_chargee->dimensions->i, joueur->x, joueur->y);
        
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
                afficherNiveau(moteur, joueur->x, joueur->y);
               
                //Dessiner entités
                dessinerEntite(moteur, (t_entite*) joueur);
                if(!liste_vide(liste_entites))
                {
                    en_tete(liste_entites);
                    while(!hors_liste(liste_entites))
                    {
                        valeur_elt(liste_entites, &entite_courante);
                        if(entite_courante != NULL)
                            dessinerEntite(moteur, entite_courante);
                        else
                            oter_elt(liste_entites);
                        suivant(liste_entites);
                        entite_courante = NULL;
                    }
                }

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
        updateCamera(moteur, niveau->salle_chargee->dimensions->largeur, niveau->salle_chargee->dimensions->hauteur, niveau->salle_chargee->dimensions->j, niveau->salle_chargee->dimensions->i, joueur->x, joueur->y);
        
        //Rendu niveau
        afficherNiveau(moteur, joueur->x, joueur->y);


        //Afficher collisions DEBUG
        /*
        if(moteur->niveau_charge->collisions!=NULL)
            for(int b = 0; b < moteur->niveau_charge->taille_collisions; b++)
                SDL_RenderDrawRect(moteur->renderer, &(moteur->niveau_charge->collisions[b]));
        */

        //rendu joueur
        dessinerEntite(moteur, (t_entite*) joueur);
        //Dessiner entités
        if(!liste_vide(liste_entites))
        {
            en_tete(liste_entites);
            while(!hors_liste(liste_entites))
            {
                valeur_elt(liste_entites, &entite_courante);
                if(entite_courante != NULL)
                    dessinerEntite(moteur, entite_courante);
                else
                    oter_elt(liste_entites);
                suivant(liste_entites);
                entite_courante = NULL;
            }
        }
        

        //Afficher frame
        SDL_RenderPresent(moteur->renderer);

        //Réguler FPS
        tempsEcoule = SDL_GetTicks() - moteur->temps;
        if(TEMPS_POUR_CHAQUE_SECONDE > tempsEcoule)
            SDL_Delay(TEMPS_POUR_CHAQUE_SECONDE - tempsEcoule);
    }


    return 0;
}


int nouvellePartie()
{

    return 0;
}

//Negatif si erreur
int chargerPartie(t_moteur * moteur)
{
    t_niveau * niveau;
    t_joueur * joueur, * tmp = malloc(sizeof(t_joueur));


    /** Ici reposera le module de chargement de guillaume*/
    FILE * fichier = fopen("./test/allure_d'un_niveau.txt", "r");
    if(fichier == NULL)
    {
        printf("mince");
        return -1;
    }
    if(lancerNiveau(fichier, moteur) != 0)
        return -1;

    niveau = moteur->niveau_charge;
    joueur = creerJoueur(niveau->salle_chargee->dimensions->j*NB_TILE_LARGEUR + 5, niveau->salle_chargee->dimensions->i*NB_TILE_HAUTEUR + 3, moteur->textures->player);
    if(joueur == NULL)
            {
                printf("Le niveau n'a pas pu être lancé\n");
                return -1;
            }
    
    if(file_empty("save") == 0){
        printf("\nFile empty");
            
    }else{
        printf("\nFile not empty -- loading player");
        read_file_player("save",joueur);
    }

    //print_struct_player(joueur);
    updateCamera(moteur, niveau->salle_chargee->dimensions->largeur, niveau->salle_chargee->dimensions->hauteur, niveau->salle_chargee->dimensions->j, niveau->salle_chargee->dimensions->i, joueur->x, joueur->y);

    jouerNiveau(moteur, joueur);

    write_file_player("save",joueur);

    arreterNiveau(&moteur->niveau_charge);
    moteur->niveau_charge = NULL;
    return 0;
}
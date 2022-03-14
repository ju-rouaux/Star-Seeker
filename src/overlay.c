
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <textures.h> 
#include <joueur.h>
#include <moteur.h>
#include <generation_niveau.h>
#include <overlay.h>



#define AUCUN 0


void tileMap(SDL_Rect * rectangle, t_tile_map_type type){


    switch (type){

        case SALLE:
            splitTexture(rectangle, 0,0);
            break;

        case SALLE_COURANTE:
            splitTexture(rectangle, 1,0);
            break;

        default: //texture par défaut
            splitTexture(rectangle, 0,0);
            break;

    }



}



void dessiner_tile_map(t_moteur * moteur, t_tile_map_type type, float x, float y){
        
    SDL_Rect source; //Partie de du tileset à affiche
    SDL_Rect destination; //Position dans la fenetre où afficher
    
    destination.h = moteur->echelle / 2;
    destination.w = moteur->echelle / 2;
    destination.x = (x * moteur->echelle) / 2;
    destination.y = (y * moteur->echelle) / 2;
    
    tileMap(&source, type);

    SDL_RenderCopy(moteur->renderer, moteur->textures->overlay, &source, &destination);



}

void dessiner_map(t_moteur * moteur, niveau_informations_t * infosNiveau, int idSalle){

    for (int i = 0; i < HAUTEUR_NIVEAU_MAX; i++){

        for(int j = 0; j < LONGUEUR_NIVEAU_MAX; j++){

            if(infosNiveau->matrice[i][j] != VIDE){

               if(infosNiveau->matrice[i][j] == idSalle){
                   dessiner_tile_map(moteur, SALLE_COURANTE, 0.5, 0.5);
               }


            }


        }

    }

}
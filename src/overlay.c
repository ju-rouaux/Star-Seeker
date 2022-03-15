
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <textures.h> 
#include <joueur.h>
#include <moteur.h>
#include <generation_niveau.h>
#include <overlay.h>


void tileMap(SDL_Rect * rectangle, t_tile_map_type type){


    switch (type){

        case SALLE_COURANTE:
            splitTexture(rectangle, 0,0);
            break;

        case SALLE:
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
    
    destination.h = moteur->echelle;
    destination.w = moteur->echelle;
    destination.x = moteur->window_width/2 + x * 13 * moteur->echelle/16;
    destination.y = moteur->window_height/2 + y * 7 * moteur->echelle/16;
    
    
     


    tileMap(&source, type);

    SDL_RenderCopy(moteur->renderer, moteur->textures->overlay, &source, &destination);



}

void dessiner_map(t_moteur * moteur, niveau_informations_t * infosNiveau, int idSalle){

    for (int i = 0; i < LONGUEUR_NIVEAU_MAX; i++){

        for(int j = 0; j < HAUTEUR_NIVEAU_MAX; j++){

            if(infosNiveau->matrice[j][i] != VIDE){

               if(infosNiveau->matrice[j][i] == idSalle){
                    dessiner_tile_map(moteur, SALLE_COURANTE, i - LONGUEUR_NIVEAU_MAX/2, j - HAUTEUR_NIVEAU_MAX/2);
               }

               else
                    dessiner_tile_map(moteur, SALLE, i - LONGUEUR_NIVEAU_MAX/2, j - HAUTEUR_NIVEAU_MAX/2);


            }


        }

    }

}
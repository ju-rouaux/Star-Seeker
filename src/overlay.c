
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <textures.h> 
#include <joueur.h>
#include <moteur.h>
#include <generation_niveau.h>
#include <overlay.h>


void tileMap(SDL_Rect * rectangle, int type){


    splitTexture(rectangle, type,0, NB_TILE_HAUTEUR, NB_TILE_LARGEUR, 16,16);
}



void dessiner_tile_map(t_moteur * moteur, int type, float x, float y){
        
    SDL_Rect source; //Partie de du tileset à affiche
    SDL_Rect destination; //Position dans la fenetre où afficher
    
    destination.h = 7 * moteur->echelle/16;
    destination.w = 13 * moteur->echelle/16;
    destination.y = moteur->window_height/2 + y * destination.h;
    destination.x = moteur->window_width/2 + x * destination.w;
  


    tileMap(&source, type);

    SDL_RenderCopy(moteur->renderer, moteur->textures->overlay, &source, &destination);



}


int type_salle_map(int matrice[LONGUEUR_NIVEAU_MAX][HAUTEUR_NIVEAU_MAX], int x, int y){

    int type = 15;
    
    if(y-1 >= 0 && matrice[x][y] == matrice[x][y-1])
        type -= 8;

    if(x+1 < LONGUEUR_NIVEAU_MAX && matrice[x][y] == matrice[x+1][y])
        type -= 4;

    if(y+1 < HAUTEUR_NIVEAU_MAX && matrice[x][y] == matrice[x][y+1])
        type -= 2;

    if(x-1 >= 0 && matrice[x][y] == matrice[x-1][y])
        type -= 1;

        
    return type;
}


void dessiner_map(t_moteur * moteur, niveau_informations_t * infosNiveau, int idSalle){

    SDL_SetTextureColorMod(moteur->textures->overlay, (infosNiveau->rouge/4) - 32 + 100,  (infosNiveau->vert/4) - 32 + 100, (infosNiveau->bleu/4) - 32 + 100);

    for (int i = 0; i < LONGUEUR_NIVEAU_MAX; i++){

        for(int j = 0; j < HAUTEUR_NIVEAU_MAX; j++){

            if(infosNiveau->matrice[j][i] != VIDE){


                if(infosNiveau->matrice[j][i] == idSalle){
                    SDL_SetTextureColorMod(moteur->textures->overlay, 255, 255, 255);
                }

                int type = type_salle_map(infosNiveau->matrice, j, i);
                dessiner_tile_map(moteur, type, i - LONGUEUR_NIVEAU_MAX/2, j - HAUTEUR_NIVEAU_MAX/2);

                if(infosNiveau->matrice[j][i] == idSalle){
                    SDL_SetTextureColorMod(moteur->textures->overlay, (infosNiveau->rouge/4) - 32 + 100,  (infosNiveau->vert/4) - 32 + 100, (infosNiveau->bleu/4) - 32 + 100);
                }

            }


        }

    }

}
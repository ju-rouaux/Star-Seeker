/**
 * \file overlay.c
 * 
 * \brief Module de gestion de l'interface utilisateur in-game
 * 
 * 
 * \author Camille Remoué
 */

#include <overlay.h>



/**
 * \brief Dessine une tile de map à la position voulue
 *  
 * \param moteur nécessaire pour dessiner sur l'écran
 * \param type Type de salle, voir la fonction type_salle_map()
 * \param x Coordonnée de la salle à dessiner
 * \param y Coordonnée de la salle à dessiner
 *
 *  
 * \return un id de tile entre 0 et 15 
 */
static void dessiner_tile_map(t_moteur * moteur, int type, float x, float y){
        
    SDL_Rect source; //Partie de du tileset à affiche
    SDL_Rect destination; //Position dans la fenetre où afficher
    
    destination.h = 7 * moteur->echelle/16;
    destination.w = 13 * moteur->echelle/16;
    destination.y = moteur->window_height/2 + y * destination.h;
    destination.x = moteur->window_width/2 + x * destination.w;
  


    splitTexture(&source, type,0, NB_TILE_HAUTEUR, NB_TILE_LARGEUR, 16,16);

    SDL_RenderCopy(moteur->renderer, moteur->textures->overlay, &source, &destination);



}


/**
 * \brief Attribue un id de tile à chaque salle pour la map : est-ce une salle simple ? Une salle reliée en haut et à gauche ? 
 *  
 * \param matrice Matrice des IDs des salles du niveau
 * \param x Coordonnée de la salle dont le type doit être déterminé 
 * \param y Coordonnée de la salle dont le type doit être déterminé 
 *
 *  
 * \return un id de tile entre 0 et 15 
 */
static int type_salle_map(int matrice[LONGUEUR_NIVEAU_MAX][HAUTEUR_NIVEAU_MAX], int x, int y){

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

/**
 * \brief Dessine toute la map à l'écran
 *  
 * \param moteur Informations d'échelle et de taille d'écran
 * \param infosNiveau Matrice du niveau et couleurs du niveau
 * \param idSalle ID de la salle actuelle
 *  
 */
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
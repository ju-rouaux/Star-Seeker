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
    destination.x = moteur->window_width/2 + x * destination.w;
    destination.y = moteur->window_height/2 + y * destination.h;
  


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
static int type_salle_map(int * matrice, int hauteur, int longueur, int x, int y){

    int type = 15;
    
    if(y >= 0 && matrice[x*longueur + y] == matrice[x*longueur + (y-1)])
        type -= 8;

    if(x+1 < hauteur && matrice[x*longueur + y] == matrice[(x+1) * longueur + y])
        type -= 4;

    if(y+1 < longueur && matrice[x*longueur + y] == matrice[x*longueur + (y+1)])
        type -= 2;

    if(x-1 >= 0 && matrice[x*longueur + y] == matrice[(x-1)*longueur + y])
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

    int hauteur = infosNiveau->hauteur;
    int longueur = infosNiveau->longueur;
    SDL_SetTextureColorMod(moteur->textures->overlay, (infosNiveau->rouge/4) - 32 + 100,  (infosNiveau->vert/4) - 32 + 100, (infosNiveau->bleu/4) - 32 + 100);

    for (int i = 0; i < hauteur; i++){

        for(int j = 0; j < longueur; j++){

            if(infosNiveau->matrice[i*longueur + j] != VIDE){


                if(infosNiveau->matrice[i*longueur + j] == idSalle){
                    SDL_SetTextureColorMod(moteur->textures->overlay, 255, 255, 255);
                }

                int type = type_salle_map(infosNiveau->matrice, hauteur, longueur, i, j);
                dessiner_tile_map(moteur, type, j - longueur/2, i - hauteur/2);

                if(infosNiveau->matrice[i*longueur + j] == idSalle){
                    SDL_SetTextureColorMod(moteur->textures->overlay, (infosNiveau->rouge/4) - 32 + 100,  (infosNiveau->vert/4) - 32 + 100, (infosNiveau->bleu/4) - 32 + 100);
                }

            }


        }

    }

}






/**
 * \brief Dessine le HUD
 *  
 * \param moteur Informations d'échelle et de taille d'écran
 * \param joueur Points de vie
 *  
 */
void dessiner_hud(t_moteur * moteur, t_joueur * joueur){
   
   
    SDL_SetTextureColorMod(moteur->textures->overlay, 255, 255, 255);

    SDL_Rect source; //Partie de du tileset à affiche
    SDL_Rect destination; //Position dans la fenetre où afficher



    //Points de vie
    destination.h = moteur->echelle/2;
    destination.w = moteur->echelle/2;
    destination.y = 16;
  

    for(int i = 0; i < joueur->pv; i += 2){

        destination.x = i*moteur->echelle/4;

        splitTexture(&source, (joueur->pv - i) == 1, 1, 16, 16, 16,16);
        SDL_RenderCopy(moteur->renderer, moteur->textures->overlay, &source, &destination);

    }


}

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <niveau.h>
#include <rendu_niveau.h>

//Retourne la taille en pixel d'un bloc selon la taille de l'écran
//Il faudra probablement déplacer cette fonction dans un autre module
int getScale(SDL_Window * window)
{
    int l, h;
    SDL_GetWindowSize(window, &l, &h);
    
    if(h < l) //Si la hauteur est petite, on se base sur cette dimension
        return h / (NB_TILE_HAUTEUR + 1); //On laisse un demi bloc de vide avec les bordures
    
    else //Si la largeur est petite, on se base sur cette dimension
        return l / (NB_TILE_LARGEUR + 1);
}

int afficherSalle(t_moteur * moteur, t_salle * salle, int x, int y)
{
    //Afficher sol
    SDL_Texture * 

    //Afficher murs

    return 0;
}

int afficherNiveau(t_moteur * moteur, t_niveau * niveau)
{
    int resultat;
    for(int i = 0; i < niveau->h; i++)
    {
        for(int j = 0; j < niveau->l; j++)
        {
            resultat = afficherSalle(niveau->salles[i*niveau->l + j], i, j);
            if(resultat != 0)
                return -1;

            
        }
    }
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <moteur.h>
#include <partie.h>

int main(int argc, char * argv[])
{

    t_moteur * moteur = NULL;

<<<<<<< HEAD
=======
    
    t_couleurRVB * couleur = malloc(sizeof(t_couleurRVB));

    for (int i = 0; i < 20; i++){
        couleur_aleatoire(couleur);

        printf("%d %d %d \n", couleur->rouge, couleur->vert, couleur->bleu);
    
    }

    
    /*
    char * nom_planete = "ziofefez";

    creer_niveau("test.niv", nom_planete);






    SDL_Window * window = NULL;
    SDL_Renderer * renderer = NULL;
    
>>>>>>> 4b3923e60360e4e54b6f1b9ec8d33f87927a2635
    if(SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        printf("Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

<<<<<<< HEAD
    moteur = chargerMoteur(SDL_GetTicks());

    chargerPartie(moteur);

    detruireMoteur(&moteur);
=======
    
    creerFenetreEtRendu(&window, &renderer);
    SDL_Delay(5000);
    detruireFenetreEtRendu(&window, &renderer);
    
    SDL_Quit();

    */
>>>>>>> 4b3923e60360e4e54b6f1b9ec8d33f87927a2635

    return 0;

}

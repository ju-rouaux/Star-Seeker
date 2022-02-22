#include <stdlib.h>

#include <stdio.h>
<<<<<<< HEAD

#include "liste.h"


int main() {


    t_liste * liste = malloc(sizeof(t_liste));

    init_liste(liste);

    ajout_droit(liste, "test1");
    ajout_droit(liste, "test2");
    ajout_gauche(liste,"-test1");
    ajout_gauche(liste,"-test2");
    ajout_droit(liste,"test3");
    // en_tete(liste);
    // oter_elt(liste);

    // en_queue(liste);
    // oter_elt(liste);

    affichage_liste(liste);

=======
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <window.h>
#include <generation_niveau.h>
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              
int main(int argc, char * argv[])
{


    
    char * nom_planete = "bloblop";
    creer_niveau("test15.niv", nom_planete);







    SDL_Window * window = NULL;
    SDL_Renderer * renderer = NULL;
    
    if(SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        printf("Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }


    creerFenetreEtRendu(&window, &renderer);
    SDL_Delay(5000);
    detruireFenetreEtRendu(&window, &renderer);


    SDL_Quit();
>>>>>>> bae4312dad1b27397a5e9a7f6b7f0757aa4364bb
    return 0;
}

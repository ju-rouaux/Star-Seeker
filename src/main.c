#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <moteur.h>
#include <partie.h>
#include <generation_niveau.h>


/**
 * \brief Indique au module de sauvegarde d'écraser la sauvegarde du joueur pour recommencer
 * sa partie.
 * 
 * \param moteur Le moteur du jeu
 */
void resetSauvegardeJoueur(t_moteur * moteur)
{
    //Afficher un menu d'avertissement
    moteur->parametres.reset_sauvegarde_joueur = VRAI;
}

int main(int argc, char * argv[])
{
    int param = 1;
    t_moteur * moteur = NULL;

     if(SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        printf("Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    moteur = chargerMoteur(SDL_GetTicks());
    if(argc == 2)
        param = argv[1];
    chargerPartie(moteur, param);

    detruireMoteur(&moteur);

    return 0;

}

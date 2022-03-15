#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL.h>
#include <moteur.h>
#include <audio.h>
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
    t_moteur * moteur = NULL;

    if(SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        printf("Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }


    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1)
        printf("WARNING : Erreur d'initialisation de SDL MIXER : %s\n", Mix_GetError());


    moteur = chargerMoteur(SDL_GetTicks());
    moteur->parametres.reset_sauvegarde_joueur = FAUX;

    nouvellePartie(moteur, 2);
    //chargerPartie(moteur);

    detruireMoteur(&moteur);
    
    Mix_CloseAudio();
    SDL_Quit();
    return 0;

}

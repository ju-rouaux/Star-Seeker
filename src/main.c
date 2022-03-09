#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL.h>
#include <moteur.h>
#include <audio.h>
#include <partie.h>
#include <generation_niveau.h>

int main(int argc, char * argv[])
{
    
    t_moteur * moteur = NULL;

     if(SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        printf("Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1){

        printf("Erreur d'initialisation de SDL MIXER : %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }


    chargerAudio();

    moteur = chargerMoteur(SDL_GetTicks());

    chargerPartie(moteur, 1);

    detruireMoteur(&moteur);


    detruireAudio(musiques, bruitages);

    return 0;

}

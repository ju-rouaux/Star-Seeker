#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <moteur.h>
#include <audio.h>
#include <partie.h>
#include <generation_niveau.h>
#include <menu.h>
#include <menu_options.h>
#include <menu_options_keymap.h>
#include <main.h>

int main(int argc, char * argv[])
{
    t_moteur * moteur = NULL;
    e_code_main code = 1;

    if(SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        printf("Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }


    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1)
        printf("WARNING : Erreur d'initialisation de SDL MIXER : %s\n", Mix_GetError());

    if(TTF_Init()==-1) {
        printf("TTF_Init: %s\n", TTF_GetError());
        return EXIT_FAILURE;
    }

    moteur = chargerMoteur(SDL_GetTicks());

    Mix_PlayMusic(moteur->musiques->menu_principal, -1);

    while(code != JEU_QUITTER){
        switch(code)
        {
            case M_PRINCIPAL : code = chargerMenu(moteur); break;
            case M_JEU : 
                Mix_PlayChannel(4, moteur->bruitages->menu_selection, 0);
                code = nouvellePartie(moteur, 8);
                if(code != JEU_QUITTER)
                    Mix_PlayMusic(moteur->musiques->menu_principal, -1); //Lancer la musique au retour sur le menu, sauf si on quitte le programme
                break;
            case M_CHARGER : 
                Mix_PlayChannel(4, moteur->bruitages->menu_selection, 0);
                code = chargerPartie(moteur); 
                if(code != JEU_QUITTER)
                    Mix_PlayMusic(moteur->musiques->menu_principal, -1); //Lancer la musique au retour sur le menu, sauf si on quitte le programme
                break;
            case M_OPTIONS : code = chargerMenu_Options(moteur); break;
            case M_KEYMAP : code = chargerMenu_Options_keymap(moteur); break;

            default : 
                printf("Erreur menu (code %i)\n", code);
                code = JEU_QUITTER;
        }
    }

    detruireMoteur(&moteur);
    
    Mix_CloseAudio();
    TTF_Quit();
    SDL_Quit();

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <moteur.h>
#include <partie.h>
#include <generation_niveau.h>
#include <menu.h>
#include <menu_options.h>
#include <menu_options_keymap.h>

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
    e_menu code = 1;

    if(SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        printf("Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    if(TTF_Init()==-1) {
        printf("TTF_Init: %s\n", TTF_GetError());
        return EXIT_FAILURE;
    }

    moteur = chargerMoteur(SDL_GetTicks());
    moteur->parametres.reset_sauvegarde_joueur = VRAI;

    while(code != M_QUITTER){
        switch(code){
            case M_PRINCIPAL : code = chargerMenu(moteur);break;
            case M_JEU : code = nouvellePartie(moteur, 5); break;
            case M_CHARGER : code = chargerPartie(moteur);break;
            case M_OPTIONS : code = chargerMenu_Options(moteur);break;
            case M_KEYMAP : code = chargerMenu_Options_keymap(moteur); break;
           // case M_QUITTER : code =
            case ERROR_MENU : return ERROR_MENU; break;
            case ERROR_MENU_TEXTURE : return ERROR_MENU_TEXTURE;break;
            default : return ERROR_MENU;
        }
    }
    // nouvellePartie(moteur, 5);
    //chargerPartie(moteur);


    detruireMoteur(&moteur);

    TTF_Quit();
    SDL_Quit();
    return 0;

}

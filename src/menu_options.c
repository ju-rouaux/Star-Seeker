#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <window.h>
#include <moteur.h>
#include <menu.h>
#include <menu_options.h>
#include <menu_options_keymap.h>


/**
 * \brief Gere tout les evenements liées au boutons danns le sous menu options
 * 
 * \param moteur structure moteur
 * \param volume structure pour le bouton "volume"
 * \param keymap structure pour le bouton "keymap"
 * \param retour structure pour le bouton "retour"
 * \return int 0 si succes, 1 si l'utilisateur ferme la fenetre, autre chiffre positif selon le bouton appuyé
 */
static int handleEvents_options(t_moteur * moteur, t_bouton * volume, t_bouton * keymap, t_bouton * retour){

    int mouse_x, mouse_y;
    SDL_Event e;

    while(SDL_PollEvent(&e)){
        mouse_x = e.button.x, mouse_y = e.button.y;
        switch (e.type){
            case SDL_QUIT:
                return 1;
            case SDL_MOUSEBUTTONDOWN :
                switch (e.button.button)
                {
                    case SDL_BUTTON_LEFT: /**Bouton gauche*/
                        if(((mouse_x >= volume->rect.x) && (mouse_x <= (volume->rect.x + moteur->echelle * (strlen(B_VOLUME)/2.5))))&&((mouse_y >= volume->rect.y) && mouse_y <= (volume->rect.y + moteur->echelle * 2)))
                            return 2;
                        if(((mouse_x >= keymap->rect.x) && (mouse_x <= (keymap->rect.x + moteur->echelle * (strlen(B_KEYMAP)/2.5))))&&((mouse_y >= keymap->rect.y) && (mouse_y <= (keymap->rect.y + moteur->echelle * 2))))
                            return 3;
                        if(((mouse_x >= retour->rect.x) && (mouse_x <= (retour->rect.x + moteur->echelle * (strlen(B_RETOUR)/2.5))))&&((mouse_y >= retour->rect.y) && mouse_y <= (retour->rect.y + moteur->echelle * 2)))
                            return 4;
                        break;
                    default: return -1; break;
                };
                break;
        case SDL_MOUSEMOTION :

            if(((mouse_x >= volume->rect.x) && (mouse_x <= (volume->rect.x + moteur->echelle * (strlen(B_RETOUR)/2.5))))&&((mouse_y >= volume->rect.y) && (mouse_y <= (volume->rect.y + moteur->echelle * 2))))
                SDL_SetTextureColorMod(volume->texture,255,0,0);
            else SDL_SetTextureColorMod(volume->texture,0,0,255);

            if(((mouse_x >= keymap->rect.x) && (mouse_x <= (keymap->rect.x + moteur->echelle * (strlen(B_KEYMAP)/2.5))))&&((mouse_y >= keymap->rect.y) && (mouse_y <= (keymap->rect.y + moteur->echelle * 2))))
                SDL_SetTextureColorMod(keymap->texture,255,0,0);
            else SDL_SetTextureColorMod(keymap->texture,0,0,255);

            if(((mouse_x >= retour->rect.x) && (mouse_x <= (retour->rect.x + moteur->echelle * (strlen(B_RETOUR)/2.5))))&&((mouse_y >= retour->rect.y) && mouse_y <= (retour->rect.y + moteur->echelle * 2)))
                SDL_SetTextureColorMod(retour->texture,255,0,0);
            else SDL_SetTextureColorMod(retour->texture,0,0,255);

        break;
        }
    }
    return 0;
}


/**
 * \brief Charge tout les boutons / fonctionnalités du sous menu pour les options
 * 
 * \param moteur structure moteur
 * \return int 0 si succes, negatif si echec 
 */
int charger_menuOptions(t_moteur * moteur){

    t_bouton * volume = NULL;
    t_bouton * keymap = NULL;
    t_bouton * retour = NULL;

    volume = initialiserBouton(moteur,B_VOLUME);
    keymap = initialiserBouton(moteur,B_KEYMAP);
    retour = initialiserBouton(moteur,B_RETOUR);

    int temp = 0;


    while(temp == 0){
        if(SDL_SetRenderDrawColor(moteur->renderer,0,0,0,255) !=0){
            printf("Erreur lors du SDL_SetRenderDrawColor dans le menu");
            return -1;
        }
        if(SDL_RenderClear(moteur->renderer)!=0){
            printf("Erreur lors du SDL_RenderClear dans le menu");
            return -1;
        }
        if(update_texture(moteur,volume,moteur->window_width /4 ,moteur->window_height *0.15, B_VOLUME ) != 0){
            printf("Erreur lors de la mise a jour des textures pour le bouton \"Volume\" dans le menu_options\n");
            return -1;
        }
        if(update_texture(moteur,keymap,moteur->window_width /4 ,moteur->window_height *0.42, B_KEYMAP) != 0){
            printf("Erreur lors de la mise a jour des textures pour le bouton \"Keymap\" dans le menu_options\n");
            return -1;
        }
        if(update_texture(moteur,retour,moteur->window_width /4 ,moteur->window_height *0.7, B_RETOUR) != 0){
            printf("Erreur lors de la mise a jour des textures pour le bouton \"Retour\" dans le menu_options\n");
            return -1;
        }
        updateEchelle(moteur);
        SDL_RenderPresent(moteur->renderer);
        temp = handleEvents_options(moteur,volume,keymap,retour);


        switch(temp){
            case 0 : break;
            case 1 : 
            case -1 : {
                printf("Erreur (default)");
                detruireBouton(&volume);
                detruireBouton(&keymap);
                detruireBouton(&retour);
                return -1;
            }
            case 4 : {
                printf("Retour");
                detruireBouton(&volume);
                detruireBouton(&keymap);
                detruireBouton(&retour);
                chargerMenu(moteur);
                break;
            }
            case 2 : printf("Muet (on/off)\n");temp = 0;break;
            case 3 : {
                printf("Keymap");
                detruireBouton(&volume);
                detruireBouton(&keymap);
                detruireBouton(&retour);
                charger_menuOptions_keymap(moteur);
                break;
            }
            default :{
                printf("Erreur, menu inconnu");
                detruireBouton(&volume);
                detruireBouton(&keymap);
                detruireBouton(&retour);
                return -1;
            }
    }

    }

    
    return 0;
}

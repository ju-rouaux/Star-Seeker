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
 * \brief Initalise un bouton en allouant la memoire et en initialisant ses données
 * 
 * \param moteur structure du moteur
 * \param bouton strcture d'un bouton
 * \return t_bouton* la structure du bouton initialisé
 */
static t_bouton ** initialiserBoutonsOptions(t_moteur * moteur){

    t_bouton ** boutons = malloc(sizeof(t_bouton*) * NB_B_MENU_OPTIONS);
    char nom[NB_B_MENU_OPTIONS][12] = {B_VOLUME,B_KEYMAP,B_RETOUR};

    if(*boutons == NULL){
        printf("Impossible d'allouer la mémoire pour le tableau de boutonl\n");
        return NULL;
    }


    for(int i =0; i < NB_B_MENU_OPTIONS;i++){
        boutons[i] = malloc(sizeof(t_bouton));

        if(boutons[i] == NULL){
            printf("Impossible d'allouer la mémoire pour le bouton[%d] dans le menu principal\n", i);
            while(i >= 0){

            }
            return NULL;
        }

        SDL_Surface *surface;
        SDL_Color textColor = {255, 255, 255, 0};

        TTF_Font *font = TTF_OpenFont("./PressStart2P-Regular.ttf", 1000);

        if (font == NULL) {
            fprintf(stderr, "error: font not found\n");
            return NULL;
        }

        boutons[i]->rect.x = 0;
        boutons[i]->rect.y = 0;
        boutons[i]->rect.h = 0;
        boutons[i]->rect.w = 0;

        surface = TTF_RenderText_Solid(font, nom[i], textColor);
        boutons[i]->texture = SDL_CreateTextureFromSurface(moteur->renderer, surface);
        SDL_FreeSurface(surface);
        SDL_SetTextureColorMod(boutons[i]->texture,0,0,255);

        TTF_CloseFont(font);
    }


    return boutons;
}




static int handleEvents_options(t_moteur * moteur, t_bouton ** boutons_options){

    int mouse_x, mouse_y;
    SDL_Event e;

    while(SDL_PollEvent(&e)){
        mouse_x = e.button.x, mouse_y = e.button.y;
        switch (e.type){
            case SDL_QUIT:
                return 1;
            case SDL_MOUSEBUTTONDOWN : /**Si un des boutons de la souris est relaché*/
                switch (e.button.button)
                {
                    case SDL_BUTTON_LEFT: /**Bouton gauche*/
                        if(((mouse_x >= boutons_options[0]->rect.x) && (mouse_x <= (boutons_options[0]->rect.x + moteur->echelle * (strlen(B_VOLUME)/2.5))))&&((mouse_y >= boutons_options[0]->rect.y) && mouse_y <= (boutons_options[0]->rect.y + moteur->echelle * 2))){
                            printf("Muet (on/off)");
                        }
                        if(((mouse_x >= boutons_options[1]->rect.x) && (mouse_x <= (boutons_options[1]->rect.x + moteur->echelle * (strlen(B_KEYMAP)/2.5))))&&((mouse_y >= boutons_options[1]->rect.y) && (mouse_y <= (boutons_options[1]->rect.y + moteur->echelle * 2)))){
                                printf("Keymap");
                                charger_menuOptions_keymap(moteur);
                        }
                        // if(((mouse_x >= options->rect.x )&& (mouse_x <= (options->rect.x + moteur->echelle * 4.5)))&&((mouse_y >= options->rect.y) && (mouse_y <= (options->rect.y + moteur->echelle * 2)))){
                        //     printf("Options");
                        // }
                         if(((mouse_x >= boutons_options[2]->rect.x) && (mouse_x <= (boutons_options[2]->rect.x + moteur->echelle * (strlen(B_RETOUR)/2.5))))&&((mouse_y >= boutons_options[2]->rect.y) && mouse_y <= (boutons_options[2]->rect.y + moteur->echelle * 2))){
                            chargerMenu(moteur);
                        return 1;
                        }
                        break;
                    default:break;
                };
                break;
        case SDL_MOUSEMOTION :

            if(((mouse_x >= boutons_options[0]->rect.x) && (mouse_x <= (boutons_options[0]->rect.x + moteur->echelle * (strlen(B_RETOUR)/2.5))))&&((mouse_y >= boutons_options[0]->rect.y) && (mouse_y <= (boutons_options[0]->rect.y + moteur->echelle * 2))))
                SDL_SetTextureColorMod(boutons_options[0]->texture,255,0,0);
            else SDL_SetTextureColorMod(boutons_options[0]->texture,0,0,255);

            if(((mouse_x >= boutons_options[1]->rect.x) && (mouse_x <= (boutons_options[1]->rect.x + moteur->echelle * (strlen(B_RETOUR)/2.5))))&&((mouse_y >= boutons_options[1]->rect.y) && (mouse_y <= (boutons_options[1]->rect.y + moteur->echelle * 2))))
                SDL_SetTextureColorMod(boutons_options[1]->texture,255,0,0);
            else SDL_SetTextureColorMod(boutons_options[1]->texture,0,0,255);

            // if(((mouse_x >= options->rect.x )&& (mouse_x <= (options->rect.x + moteur->echelle * 4.5)))&&((mouse_y >= options->rect.y) && (mouse_y <= (options->rect.y + moteur->echelle * 2))))
            //     SDL_SetTextureColorMod(options->texture,255,0,0);
            // else SDL_SetTextureColorMod(options->texture,0,0,255);

            if(((mouse_x >= boutons_options[2]->rect.x) && (mouse_x <= (boutons_options[2]->rect.x + moteur->echelle * (strlen(B_RETOUR)/2.5))))&&((mouse_y >= boutons_options[2]->rect.y) && mouse_y <= (boutons_options[2]->rect.y + moteur->echelle * 2)))
                SDL_SetTextureColorMod(boutons_options[2]->texture,255,0,0);
            else SDL_SetTextureColorMod(boutons_options[2]->texture,0,0,255);

        break;
        }
    }
    return 0;
}



int charger_menuOptions(t_moteur * moteur){

    t_bouton ** boutons_options = NULL;

    boutons_options = initialiserBoutonsOptions(moteur);



    while(handleEvents_options(moteur,boutons_options)==0){
        if(SDL_SetRenderDrawColor(moteur->renderer,0,0,0,255) !=0){
            printf("Erreur lors du SDL_SetRenderDrawColor dans le menu");
            return -1;
        }
        if(SDL_RenderClear(moteur->renderer)!=0){
            printf("Erreur lors du SDL_RenderClear dans le menu");
            return -1;
        }
        if(update_texture(moteur,boutons_options[0],moteur->window_width /4 ,moteur->window_height *0.15, B_VOLUME ) != 0){
            printf("Erreur lors de la mise a jour des textures pour le bouton \"Nouvelle Partie\" dans le menu\n");
            return -1;
        }
        if(update_texture(moteur,boutons_options[1],moteur->window_width /4 ,moteur->window_height *0.42, B_KEYMAP) != 0){
            printf("Erreur lors de la mise a jour des textures pour le bouton \"Charger Partie\" dans le menu\n");
            return -1;
        }
        if(update_texture(moteur,boutons_options[2],moteur->window_width /4 ,moteur->window_height *0.7, B_RETOUR) != 0){
            printf("Erreur lors de la mise a jour des textures pour le bouton \"Options\" dans le menu\n");
            return -1;
        }
        // if(update_texture(moteur,quitter,moteur->window_width /4 ,moteur->window_height *0.75,B_QUITTER) != 0){
        //     printf("Erreur lors de la mise a jour des textures pour le bouton \"Quitter\" dans le menu\n");
        //     return -1;
        // }
        updateEchelle(moteur);
        SDL_RenderPresent(moteur->renderer);

    }
    detruireBoutons(&boutons_options,NB_B_MENU_OPTIONS);
    return 0;
}

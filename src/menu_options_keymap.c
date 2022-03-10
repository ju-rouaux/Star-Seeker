/**
 * \file menu_options_keymap.c
 * \author Guillaume
 * \brief Sous menu pour le mapping des touches
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <window.h>
#include <moteur.h>
#include <menu.h>


/**
 * \brief Fonction d'appel pour la mise a jour des differentes textures
 * 
 * \param moteur moteur du jeu
 * \param boutons tableau de bouton
 * \return 0 si succès; negatif si echec
 */
static int update_MenuOptions_keymap(t_moteur * moteur, t_bouton ** boutons){

    if(SDL_SetRenderDrawColor(moteur->renderer,0,0,0,255) !=0){
            printf("Erreur lors du SDL_SetRenderDrawColor dans le menu_options_keymap");
            return -1;
        }
        if(SDL_RenderClear(moteur->renderer)!=0){
            printf("Erreur lors du SDL_RenderClear dans le menu_options_keymap");
            return -1;
        }

        if(update_texture(moteur,boutons[0],moteur->window_width /5 ,moteur->window_height *0.1) != 0){
            printf("Erreur lors de la mise a jour des textures pour le bouton \"haut\" dans le menu_options_keymap\n");
            return -1;
        }

        if(update_texture(moteur,boutons[1],moteur->window_width /5 ,moteur->window_height *0.4) != 0){
            printf("Erreur lors de la mise a jour des textures pour le bouton \"bas\" dans le menu_options_keymap\n");
            return -1;
        }

        if(update_texture(moteur,boutons[2],moteur->window_width /5 ,moteur->window_height *0.7) != 0){
            printf("Erreur lors de la mise a jour des textures pour le bouton \"droite\" dans le menu_options_keymap\n");
            return -1;
        }

        if(update_texture(moteur,boutons[3],moteur->window_width /2 ,moteur->window_height *0.1) != 0){
            printf("Erreur lors de la mise a jour des textures pour le bouton \"gauche\" dans le menu_options_keymap\n");
            return -1;
        }

        if(update_texture(moteur,boutons[4],moteur->window_width /2 ,moteur->window_height *0.4) != 0){
            printf("Erreur lors de la mise a jour des textures pour le bouton \"projectile\" dans le menu_options_keymap\n");
            return -1;
        }

        if(update_texture(moteur,boutons[5],moteur->window_width /2 ,moteur->window_height *0.7) != 0){
            printf("Erreur lors de la mise a jour des textures pour le bouton \"Retour\" dans le menu_options_keymap\n");
            // return -1;
        }
        updateEchelle(moteur);
        SDL_RenderPresent(moteur->renderer);
    return 0;
}

/**
 * \brief Gere tout les evenements liées au boutons danns le sous menu keymap
 * 
 * \param moteur structure moteur
 * \param boutons tableau de boutons des options
 * \return 0 si succes, 1 si l'utilisateur ferme la fenetre, autre chiffre positif selon le bouton appuyé
 */
static int handleEvents_options_keymap(t_moteur * moteur, t_bouton ** boutons){

    int mouse_x, mouse_y;
    SDL_Event e;
    SDL_Scancode key;

    while(SDL_PollEvent(&e)){
        mouse_x = e.button.x, mouse_y = e.button.y;
        update_MenuOptions_keymap(moteur,boutons);
        switch (e.type){

            case SDL_QUIT:
                return 1;

            case SDL_MOUSEBUTTONDOWN : /**Si un des boutons de la souris est relaché*/
                switch (e.button.button)
                {
                    case SDL_BUTTON_LEFT: /**Bouton gauche*/

                    for(int i = 0; i < NB_B_MENU_OPTIONS_KEYMAP ; i++){
                        if(i != NB_B_MENU_OPTIONS_KEYMAP - 1){ // Cas particulier pour le bouton retour
                            if(((mouse_x >= boutons[i]->rect.x) && (mouse_x <= (boutons[i]->rect.x  + moteur->echelle * (boutons[i]->longueur/2.5))))&&((mouse_y >= boutons[i]->rect.y) && (mouse_y <= (boutons[i]->rect.y + moteur->echelle * 2)))){
                                while(SDL_WaitEvent(&e) && e.type != SDL_KEYDOWN){
                                    key = e.key.keysym.scancode;
                                    update_MenuOptions_keymap(moteur,boutons);
                                }
                                SDL_SetTextureColorMod(boutons[i]->texture,8,125,0);
                                return (i + 2);
                            }
                        }else return i + 2;
                        }break;
                    default:return -1;break;
                };
                break;

            case SDL_MOUSEMOTION :
                for(int  i = 0; i < NB_B_MENU_OPTIONS_KEYMAP ; i++){
                        if(((mouse_x >= boutons[i]->rect.x) && (mouse_x <= (boutons[i]->rect.x  + moteur->echelle * (boutons[i]->longueur/2.5))))&&((mouse_y >= boutons[i]->rect.y) && (mouse_y <= (boutons[i]->rect.y + moteur->echelle * 2))))
                            SDL_SetTextureColorMod(boutons[i]->texture,255,0,0);
                        else SDL_SetTextureColorMod(boutons[i]->texture,0,0,255);
                    }
            break;
        }
    }
    return 0;
}


/**
 * \brief Charge tout les boutons / fonctionnalités du sous menu pour les keymap
 * 
 * \param moteur structure moteur
 * \return int 0 si succes, negatif si echec
 */
int chargerMenu_Options_keymap(t_moteur * moteur){

    t_bouton ** boutons = NULL;
    char nom_boutons[NB_B_MENU_OPTIONS_KEYMAP][TAILLE_MAX] = NOMS_B_MENU_OPTIONS_KEYMAP;

    boutons = initialiserBoutons(moteur,NB_B_MENU_OPTIONS_KEYMAP,nom_boutons);

    if(boutons == NULL){
        printf("Erreur allocation memoire boutons menu keymap\n");
        return -1;
    }

    int temp = 0;

    while(temp==0){

        if(update_MenuOptions_keymap(moteur,boutons)!=0){
            printf("Erreur lors de l'update dans le menu options keymap");
            return -1;
        }

        temp = handleEvents_options_keymap(moteur,boutons);

        switch(temp){
            case 0 : break;
            case 1 : 
            case -1 : {
                printf("Erreur (default)\n");
                detruireBoutons(&boutons,NB_B_MENU_OPTIONS_KEYMAP);
                return -1;
            }
            case 2 : printf("Map up\n");temp = 0;break;
            case 3 : printf("Map down\n");temp = 0;break;
            case 4 : printf("Map right\n");temp = 0;break;
            case 5 : printf("Map left\n");temp = 0;break;
            case 6 : printf("Map projectile\n");temp = 0;break;
            case 7 : {
                printf("Retour\n");
                detruireBoutons(&boutons,NB_B_MENU_OPTIONS_KEYMAP);
                chargerMenu_Options(moteur);
                break;
            }
            default :{
                printf("Erreur, menu inconnu\n");
                detruireBoutons(&boutons,NB_B_MENU_OPTIONS_KEYMAP);
                return -1;
            }
        }
    }
    return 0;
}



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
static t_bouton ** initialiserBoutonsOptionsKeymap(t_moteur * moteur){

    t_bouton ** boutons = malloc(sizeof(t_bouton*) * NB_B_MENU_OPTIONS_KEYMAP);
    char nom[NB_B_MENU_OPTIONS_KEYMAP][12] = {B_UP,B_DOWN,B_RIGHT,B_LEFT,B_PROJECTILE,B_RETOUR};

    if(*boutons == NULL){
        printf("Impossible d'allouer la mémoire pour le tableau de boutonl\n");
        return NULL;
    }


    for(int i =0; i < NB_B_MENU_OPTIONS_KEYMAP;i++){
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


static int update_menu_options_keymap(t_moteur * moteur,t_bouton ** boutons_options_keymap){
    if(SDL_SetRenderDrawColor(moteur->renderer,0,0,0,255) !=0){
            printf("Erreur lors du SDL_SetRenderDrawColor dans le menu_options_keymap");
            return -1;
        }
        if(SDL_RenderClear(moteur->renderer)!=0){
            printf("Erreur lors du SDL_RenderClear dans le menu_options_keymap");
            return -1;
        }

        if(update_texture(moteur,boutons_options_keymap[0],moteur->window_width /5 ,moteur->window_height *0.1, B_DOWN ) != 0){
            printf("Erreur lors de la mise a jour des textures pour le bouton \"haut\" dans le menu_options_keymap\n");
            return -1;
        }

        if(update_texture(moteur,boutons_options_keymap[1],moteur->window_width /5 ,moteur->window_height *0.4, B_UP) != 0){
            printf("Erreur lors de la mise a jour des textures pour le bouton \"bas\" dans le menu_options_keymap\n");
            return -1;
        }

        if(update_texture(moteur,boutons_options_keymap[2],moteur->window_width /5 ,moteur->window_height *0.7, B_RIGHT ) != 0){
            printf("Erreur lors de la mise a jour des textures pour le bouton \"droite\" dans le menu_options_keymap\n");
            return -1;
        }

        if(update_texture(moteur,boutons_options_keymap[3],moteur->window_width /2 ,moteur->window_height *0.1, B_LEFT) != 0){
            printf("Erreur lors de la mise a jour des textures pour le bouton \"gauche\" dans le menu_options_keymap\n");
            return -1;
        }

        if(update_texture(moteur,boutons_options_keymap[4],moteur->window_width /2 ,moteur->window_height *0.4, B_PROJECTILE) != 0){
            printf("Erreur lors de la mise a jour des textures pour le bouton \"projectile\" dans le menu_options_keymap\n");
            return -1;
        }

        if(update_texture(moteur,boutons_options_keymap[5],moteur->window_width /2 ,moteur->window_height *0.7,B_RETOUR) != 0){
            printf("Erreur lors de la mise a jour des textures pour le bouton \"Retour\" dans le menu_options_keymap\n");
            return -1;
        }
        updateEchelle(moteur);
        SDL_RenderPresent(moteur->renderer);
        return 0;
}










/**
 * \brief Gere tout les evenements liées au boutons danns le sous menu keymap
 * 
 * \param moteur strcture moteur
 * \param haut structure pour le bouton "haut"
 * \param bas structure pour le bouton "bas"
 * \param droite structure pour le bouton "droite"
 * \param gauche structure pour le bouton "gauche"
 * \param projectile structure pour le bouton "projectile"
 * \param retour structure pour le bouton "retour"
 * \return int 0 si succes, 1 si l'utilisateur ferme la fenetre, autre chiffre positif selon le bouton appuyé
 */
static int handleEvents_options_keymap(t_moteur * moteur, t_bouton ** boutons_options_keymap){

    int mouse_x, mouse_y;
    SDL_Event e;
    SDL_Scancode key;

    while(SDL_PollEvent(&e)){
        mouse_x = e.button.x, mouse_y = e.button.y;
        update_menu_options_keymap(moteur,boutons_options_keymap);
        switch (e.type){
            case SDL_QUIT:
                return 1;
            case SDL_MOUSEBUTTONDOWN : /**Si un des boutons de la souris est relaché*/
                switch (e.button.button)
                {
                    case SDL_BUTTON_LEFT: /**Bouton gauche*/
                        if(((mouse_x >= boutons_options_keymap[0]->rect.x) && (mouse_x <= (boutons_options_keymap[0]->rect.x + moteur->echelle * (strlen(B_UP)/2.5))))&&((mouse_y >= boutons_options_keymap[0]->rect.y) && mouse_y <= (boutons_options_keymap[0]->rect.y + moteur->echelle * 2))){
            
                                while(SDL_WaitEvent(&e) && e.type != SDL_KEYDOWN){
                                        key = e.key.keysym.scancode;
                                        SDL_SetTextureColorMod(boutons_options_keymap[0]->texture,8,125,0);
                                        update_menu_options_keymap(moteur,boutons_options_keymap);
                                }
                            return 2;
                        }
                        if(((mouse_x >= boutons_options_keymap[1]->rect.x) && (mouse_x <= (boutons_options_keymap[1]->rect.x + moteur->echelle * (strlen(B_DOWN)/2.5))))&&((mouse_y >= boutons_options_keymap[1]->rect.y) && (mouse_y <= (boutons_options_keymap[1]->rect.y + moteur->echelle * 2))))
                            return 3;
                        if(((mouse_x >= boutons_options_keymap[2]->rect.x )&& (mouse_x <= (boutons_options_keymap[2]->rect.x + moteur->echelle * (strlen(B_RIGHT)/2.5))))&&((mouse_y >= boutons_options_keymap[2]->rect.y) && (mouse_y <= (boutons_options_keymap[2]->rect.y + moteur->echelle * 2))))
                            return 4;
                        if(((mouse_x >= boutons_options_keymap[3]->rect.x) && (mouse_x <= (boutons_options_keymap[3]->rect.x + moteur->echelle * (strlen(B_LEFT)/2.5))))&&((mouse_y >= boutons_options_keymap[3]->rect.y) && (mouse_y <= (boutons_options_keymap[3]->rect.y + moteur->echelle * 2))))
                                return 5;
                        if(((mouse_x >= boutons_options_keymap[4]->rect.x )&& (mouse_x <= (boutons_options_keymap[4]->rect.x + moteur->echelle * (strlen(B_PROJECTILE)/2.5))))&&((mouse_y >= boutons_options_keymap[4]->rect.y) && (mouse_y <= (boutons_options_keymap[4]->rect.y + moteur->echelle * 2))))
                            return 6;
                         if(((mouse_x >= boutons_options_keymap[5]->rect.x) && (mouse_x <= (boutons_options_keymap[5]->rect.x + moteur->echelle * (strlen(B_RETOUR)/2.5))))&&((mouse_y >= boutons_options_keymap[5]->rect.y) && mouse_y <= (boutons_options_keymap[5]->rect.y + moteur->echelle * 2)))
                        return 7;
                        break;
                    default:return -1;break;
                };
                break;
        case SDL_MOUSEMOTION :

            if(((mouse_x >= boutons_options_keymap[0]->rect.x) && (mouse_x <= (boutons_options_keymap[0]->rect.x + moteur->echelle * (strlen(B_UP)/2.5))))&&((mouse_y >= boutons_options_keymap[0]->rect.y) && (mouse_y <= (boutons_options_keymap[0]->rect.y + moteur->echelle * 2))))
                SDL_SetTextureColorMod(boutons_options_keymap[0]->texture,255,0,0);
            else SDL_SetTextureColorMod(boutons_options_keymap[0]->texture,0,0,255);

            if(((mouse_x >= boutons_options_keymap[1]->rect.x) && (mouse_x <= (boutons_options_keymap[1]->rect.x + moteur->echelle * (strlen(B_DOWN)/2.5))))&&((mouse_y >= boutons_options_keymap[1]->rect.y) && (mouse_y <= (boutons_options_keymap[1]->rect.y + moteur->echelle * 2))))
                SDL_SetTextureColorMod(boutons_options_keymap[1]->texture,255,0,0);
            else SDL_SetTextureColorMod(boutons_options_keymap[1]->texture,0,0,255);

            if(((mouse_x >= boutons_options_keymap[2]->rect.x) && (mouse_x <= (boutons_options_keymap[2]->rect.x + moteur->echelle * (strlen(B_RIGHT)/2.5))))&&((mouse_y >= boutons_options_keymap[2]->rect.y) && (mouse_y <= (boutons_options_keymap[2]->rect.y + moteur->echelle * 2))))
                SDL_SetTextureColorMod(boutons_options_keymap[2]->texture,255,0,0);
            else SDL_SetTextureColorMod(boutons_options_keymap[2]->texture,0,0,255);

            if(((mouse_x >= boutons_options_keymap[3]->rect.x) && (mouse_x <= (boutons_options_keymap[3]->rect.x + moteur->echelle * (strlen(B_LEFT)/2.5))))&&((mouse_y >= boutons_options_keymap[3]->rect.y) && (mouse_y <= (boutons_options_keymap[3]->rect.y + moteur->echelle * 2))))
                SDL_SetTextureColorMod(boutons_options_keymap[3]->texture,255,0,0);
            else SDL_SetTextureColorMod(boutons_options_keymap[3]->texture,0,0,255);

            if(((mouse_x >= boutons_options_keymap[4]->rect.x) && (mouse_x <= (boutons_options_keymap[4]->rect.x + moteur->echelle * (strlen(B_PROJECTILE)/2.5))))&&((mouse_y >= boutons_options_keymap[4]->rect.y) && (mouse_y <= (boutons_options_keymap[4]->rect.y + moteur->echelle * 2))))
                SDL_SetTextureColorMod(boutons_options_keymap[4]->texture,255,0,0);
            else SDL_SetTextureColorMod(boutons_options_keymap[4]->texture,0,0,255);

            if(((mouse_x >= boutons_options_keymap[5]->rect.x) && (mouse_x <= (boutons_options_keymap[5]->rect.x + moteur->echelle * (strlen(B_RETOUR)/2.5))))&&((mouse_y >= boutons_options_keymap[5]->rect.y) && (mouse_y <= (boutons_options_keymap[5]->rect.y + moteur->echelle * 2))))
                SDL_SetTextureColorMod(boutons_options_keymap[5]->texture,255,0,0);
            else SDL_SetTextureColorMod(boutons_options_keymap[5]->texture,0,0,255);

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
int charger_menuOptions_keymap(t_moteur * moteur){

    int temp = 0;

    t_bouton ** boutons_options_keymap = NULL;

    boutons_options_keymap = initialiserBoutonsOptionsKeymap(moteur);


    while(temp==0){

        // update_menu_options_keymap(moteur,haut,bas,droite,gauche,projectile,retour);

        temp = handleEvents_options_keymap(moteur,boutons_options_keymap);

        switch(temp){
            case 0 : break;
            case 1 : 
            case -1 : {
                printf("Erreur (default)\n");
                detruireBoutons(&boutons_options_keymap,NB_B_MENU_OPTIONS_KEYMAP);
                return -1;
            }
            case 7 : {
                printf("Retour\n");
                detruireBoutons(&boutons_options_keymap,NB_B_MENU_OPTIONS_KEYMAP);
                charger_menuOptions(moteur);
                break;
            }
            case 2 : printf("Map up\n");temp = 0;break;
            case 3 : printf("Map down\n");temp = 0;break;
            case 4 : printf("Map right\n");temp = 0;break;
            case 5 : printf("Map left\n");temp = 0;break;
            case 6 : printf("Map projectile\n");temp = 0;break;
            default :{
                printf("Erreur, menu inconnu\n");
                detruireBoutons(&boutons_options_keymap,NB_B_MENU_OPTIONS_KEYMAP);
                return -1;
            }
        }

    }

    return 0;
}



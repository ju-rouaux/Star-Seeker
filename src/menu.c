#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <window.h>
#include <moteur.h>
#include <menu.h>
#include <menu_options.h>

/**
 * \brief Met a jour la texture d'un bouton
 * 
 * \param moteur structure du moteur
 * \param bouton structure d'un bouton
 * \param rect_x coordonées x en haut a gauche du rectangle (origine du rectangle en x)
 * \param rect_y coordonées y en haut a gauche du rectangle (origine du rectangle en y)
 * \param char_bouton Nom du bouton
 * \return int 0 si succès, negatif si echec
 */
int update_texture(t_moteur * moteur, t_bouton * bouton,int rect_x, int rect_y, const char * char_bouton){

    bouton->rect.x = rect_x - (strlen(char_bouton)*10);
    bouton->rect.y = rect_y;
    bouton->rect.w = moteur->echelle * (strlen(char_bouton)/2.5);
    bouton->rect.h = moteur->echelle * 2;

    if(SDL_RenderDrawRect(moteur->renderer,&bouton->rect)!=0){
        printf("Erreur lors de l'affichage d'un bouton\n");
        return -1;
    }

    if(SDL_RenderCopy(moteur->renderer, bouton->texture, NULL, &bouton->rect)!=0){
        printf("Erreur du SDL_RenderCopy dans le menu\n");
        return -1;
    }

    return 0;
}


/**
 * \brief Initalise un bouton en allouant la memoire et en initialisant ses données
 * 
 * \param moteur structure du moteur
 * \param bouton strcture d'un bouton
 * \return t_bouton* la structure du bouton initialisé
 */
static t_bouton ** initialiserBoutons(t_moteur * moteur){

    t_bouton ** boutons = malloc(sizeof(t_bouton*) * NB_B_MENU);
    char nom[NB_B_MENU][17] = {B_NOUVELLE_PARTIE,B_CHARGER_PARTIE,B_OPTIONS,B_QUITTER};

    if(*boutons == NULL){
        printf("Impossible d'allouer la mémoire pour le tableau de boutonl\n");
        return NULL;
    }


    for(int i =0; i < NB_B_MENU;i++){
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


/**
 * \brief Libère la memoire allouée par la structure d'un boutons, met son pointeur a NULL et libere la texture du bouton
 * 
 * \param menu adresse de la structure d'un bouton
 */
void detruireBoutons(t_bouton *** boutons, int nb_boutons){

    if(*boutons != NULL)
    {
        for(int i=0; i < nb_boutons;i++){
            if((*boutons)[i]!=NULL){
                SDL_DestroyTexture((*boutons)[i]->texture);
                free((*boutons)[i]);
            }
        }
        free(*boutons);
    }
    *boutons = NULL;
}


/**
 * \brief Gere les evenements pour le menu
 * Gestion de la position de la souris et des clics
 * 
 * \param moteur strcture moteur
 * \param nouvelle_partie structure pour le bouton nouvelle_partie
 * \param charger_partie structure pour le bouton charger_partie
 * \param options structure pour le bouton options
 * \param quitter structure pour le bouton quitter
 * \return int 0 si succes, 1 si l'utilisateur ferme la fenetre, autre chiffre positif selon le bouton appuyé
 */
static int handleEvents_menu(t_moteur * moteur, t_bouton ** boutons){

    int mouse_x, mouse_y; /**Coordonnées du curseur*/
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
                        if(((mouse_x >= boutons[0]->rect.x) && (mouse_x <= (boutons[0]->rect.x  + moteur->echelle * (strlen(B_NOUVELLE_PARTIE)/2.5))))&&((mouse_y >= boutons[0]->rect.y) && (mouse_y <= (boutons[0]->rect.y + moteur->echelle * 2))))
                            return 2;
                        if(((mouse_x >= boutons[1]->rect.x) && (mouse_x <= (boutons[1]->rect.x + moteur->echelle * (strlen(B_CHARGER_PARTIE)/2.5))))&&((mouse_y >= boutons[1]->rect.y) && (mouse_y <= (boutons[1]->rect.y + moteur->echelle * 2))))
                            return 3;
                        if(((mouse_x >= boutons[2]->rect.x)&& (mouse_x <= (boutons[2]->rect.x + moteur->echelle * (strlen(B_OPTIONS)/2.5))))&&((mouse_y >= boutons[2]->rect.y) && (mouse_y <= (boutons[2]->rect.y + moteur->echelle * 2))))
                            return 4;
                        if(((mouse_x >= boutons[3]->rect.x) && (mouse_x <= (boutons[3]->rect.x + moteur->echelle * (strlen(B_QUITTER)/2.5))))&&((mouse_y >= boutons[3]->rect.y) && mouse_y <= (boutons[3]->rect.y + moteur->echelle * 2)))
                        return 5;
                        break;
                    default:return -1;
                };
                break;
        case SDL_MOUSEMOTION :
            /**Recupere les coordonées x et y relative a la fenetre*/
            // printf("\nMouse has moved : Mouse coordinates relative to window : x = %d, y = %d", mouse_x, mouse_y);

             if(((mouse_x >= boutons[0]->rect.x) && (mouse_x <= (boutons[0]->rect.x  + moteur->echelle * (strlen(B_NOUVELLE_PARTIE)/2.5))))&&((mouse_y >= boutons[0]->rect.y) && (mouse_y <= (boutons[0]->rect.y + moteur->echelle * 2))))
                SDL_SetTextureColorMod(boutons[0]->texture,255,0,0);
            else SDL_SetTextureColorMod(boutons[0]->texture,0,0,255);

            if(((mouse_x >= boutons[1]->rect.x) && (mouse_x <= (boutons[1]->rect.x + moteur->echelle * (strlen(B_CHARGER_PARTIE)/2.5))))&&((mouse_y >= boutons[1]->rect.y) && (mouse_y <= (boutons[1]->rect.y + moteur->echelle * 2))))
                SDL_SetTextureColorMod(boutons[1]->texture,255,0,0);
            else SDL_SetTextureColorMod(boutons[1]->texture,0,0,255);

            if(((mouse_x >= boutons[2]->rect.x)&& (mouse_x <= (boutons[2]->rect.x + moteur->echelle * (strlen(B_OPTIONS)/2.5))))&&((mouse_y >= boutons[2]->rect.y) && (mouse_y <= (boutons[2]->rect.y + moteur->echelle * 2))))
                SDL_SetTextureColorMod(boutons[2]->texture,255,0,0);
            else SDL_SetTextureColorMod(boutons[2]->texture,0,0,255);

            if(((mouse_x >= boutons[3]->rect.x) && (mouse_x <= (boutons[3]->rect.x + moteur->echelle * (strlen(B_QUITTER)/2.5))))&&((mouse_y >= boutons[3]->rect.y) && mouse_y <= (boutons[3]->rect.y + moteur->echelle * 2)))
                SDL_SetTextureColorMod(boutons[3]->texture,255,0,0);
            else SDL_SetTextureColorMod(boutons[3]->texture,0,0,255);

        break;
        }
    }
    return 0;
}

/**
 * \brief Charge le menu (Rectangles, police)
 * 
 * \param moteur Structure du moteur
 * \return int 0 si succès, negatif si echec
 */
int chargerMenu(t_moteur * moteur){

    t_bouton ** boutons = NULL;

    boutons = initialiserBoutons(moteur);

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
        if(update_texture(moteur,boutons[0],moteur->window_width /4 ,moteur->window_height *0.08,B_NOUVELLE_PARTIE ) != 0){
            printf("Erreur lors de la mise a jour des textures pour le bouton \"Nouvelle Partie\" dans le menu\n");
            return -1;
        }
        if(update_texture(moteur,boutons[1],moteur->window_width /4 ,moteur->window_height *0.30,B_CHARGER_PARTIE) != 0){
            printf("Erreur lors de la mise a jour des textures pour le bouton \"Charger Partie\" dans le menu\n");
            return -1;
        }
        if(update_texture(moteur,boutons[2],moteur->window_width /4 ,moteur->window_height *0.53,B_OPTIONS) != 0){
            printf("Erreur lors de la mise a jour des textures pour le bouton \"Options\" dans le menu\n");
            return -1;
        }
        if(update_texture(moteur,boutons[3],moteur->window_width /4 ,moteur->window_height *0.75,B_QUITTER) != 0){
            printf("Erreur lors de la mise a jour des textures pour le bouton \"Quitter\" dans le menu\n");
            return -1;
        }
        updateEchelle(moteur);
        SDL_RenderPresent(moteur->renderer);
        temp = handleEvents_menu(moteur,boutons);



        switch(temp){
            case 0 : break;
            case 1 :
            case -1 : {
                printf("Erreur (default)");
                detruireBoutons(&boutons,NB_B_MENU);
                return -1;
            }
            case 5 : {
                printf("Quitter");
              detruireBoutons(&boutons,NB_B_MENU);
                break;
            }
            case 2 : printf("Nouvelle Partie\n");break;
            case 3 : printf("Charger Partie\n");break;
            case 4 :{
                printf("Options\n");
                detruireBoutons(&boutons,NB_B_MENU);
                charger_menuOptions(moteur);
                break;
            }
            default :{
                printf("Erreur, menu inconnu");
                detruireBoutons(&boutons,NB_B_MENU);
                return -1;
            }
        }

    }
    return 0;
}

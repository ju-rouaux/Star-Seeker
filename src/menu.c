#include <stdio.h>
#include <stdlib.h>
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
t_bouton * initialiserBouton(t_moteur * moteur, char * bouton){

    t_bouton * menu = malloc(sizeof(t_bouton));
    if(menu == NULL){
        printf("Impossible d'allouer la mémoire pour la strcture menu (Nouvelle Partie)\n");
        return NULL;
    }

    SDL_Surface *surface;
    SDL_Color textColor = {255, 255, 255, 0};

    TTF_Font *font = TTF_OpenFont("./PressStart2P-Regular.ttf", 1000);

    if (font == NULL) {
        fprintf(stderr, "error: font not found\n");
        return NULL;
    }

    menu->rect.x = 0;
    menu->rect.y = 0;
    menu->rect.h = 0;
    menu->rect.w = 0;

    surface = TTF_RenderText_Solid(font, bouton, textColor);
    menu->texture = SDL_CreateTextureFromSurface(moteur->renderer, surface);
    SDL_FreeSurface(surface);
    SDL_SetTextureColorMod(menu->texture,0,0,255);

    TTF_CloseFont(font);

    return menu;
}


/**
 * \brief Libère la memoire allouée par la structure d'un boutons, met son pointeur a NULL et libere la texture du bouton
 * 
 * \param menu adresse de la structure d'un bouton
 */
void detruireBouton(t_bouton ** menu){
    SDL_DestroyTexture((*menu)->texture);
    free(*menu);
    *menu = NULL;
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
 * \return int vrai si l'utilisateur ferme la fenetre avec la croix, par defaut 0
 */
static int handleEvents_menu(t_moteur * moteur, t_bouton * nouvelle_partie, t_bouton * charger_partie, t_bouton * options,t_bouton * quitter){

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
                        if(((mouse_x >= nouvelle_partie->rect.x) && (mouse_x <= (nouvelle_partie->rect.x  + moteur->echelle * (strlen(B_NOUVELLE_PARTIE)/2.5))))&&((mouse_y >= nouvelle_partie->rect.y) && (mouse_y <= (nouvelle_partie->rect.y + moteur->echelle * 2)))){
                            printf("Nouvelle Partie\n");
                        }
                        if(((mouse_x >= charger_partie->rect.x) && (mouse_x <= (charger_partie->rect.x + moteur->echelle * (strlen(B_CHARGER_PARTIE)/2.5))))&&((mouse_y >= charger_partie->rect.y) && (mouse_y <= (charger_partie->rect.y + moteur->echelle * 2)))){
                            printf("Charger Partie");
                        }
                        if(((mouse_x >= options->rect.x)&& (mouse_x <= (options->rect.x + moteur->echelle * (strlen(B_OPTIONS)/2.5))))&&((mouse_y >= options->rect.y) && (mouse_y <= (options->rect.y + moteur->echelle * 2)))){
                            printf("Options");
                            charger_menuOptions(moteur);
                        }
                        if(((mouse_x >= quitter->rect.x) && (mouse_x <= (quitter->rect.x + moteur->echelle * (strlen(B_QUITTER)/2.5))))&&((mouse_y >= quitter->rect.y) && mouse_y <= (quitter->rect.y + moteur->echelle * 2))){
                            printf("Quitter");
                        return 1;
                        }
                        break;
                    default:printf("Erreur souris\n");
                };
                break;
        case SDL_MOUSEMOTION :
            /**Recupere les coordonées x et y relative a la fenetre*/
            // printf("\nMouse has moved : Mouse coordinates relative to window : x = %d, y = %d", mouse_x, mouse_y);

             if(((mouse_x >= nouvelle_partie->rect.x) && (mouse_x <= (nouvelle_partie->rect.x  + moteur->echelle * (strlen(B_NOUVELLE_PARTIE)/2.5))))&&((mouse_y >= nouvelle_partie->rect.y) && (mouse_y <= (nouvelle_partie->rect.y + moteur->echelle * 2))))
                SDL_SetTextureColorMod(nouvelle_partie->texture,255,0,0);
            else SDL_SetTextureColorMod(nouvelle_partie->texture,0,0,255);

            if(((mouse_x >= charger_partie->rect.x) && (mouse_x <= (charger_partie->rect.x + moteur->echelle * (strlen(B_CHARGER_PARTIE)/2.5))))&&((mouse_y >= charger_partie->rect.y) && (mouse_y <= (charger_partie->rect.y + moteur->echelle * 2))))
                SDL_SetTextureColorMod(charger_partie->texture,255,0,0);
            else SDL_SetTextureColorMod(charger_partie->texture,0,0,255);

            if(((mouse_x >= options->rect.x)&& (mouse_x <= (options->rect.x + moteur->echelle * (strlen(B_OPTIONS)/2.5))))&&((mouse_y >= options->rect.y) && (mouse_y <= (options->rect.y + moteur->echelle * 2))))
                SDL_SetTextureColorMod(options->texture,255,0,0);
            else SDL_SetTextureColorMod(options->texture,0,0,255);

            if(((mouse_x >= quitter->rect.x) && (mouse_x <= (quitter->rect.x + moteur->echelle * (strlen(B_QUITTER)/2.5))))&&((mouse_y >= quitter->rect.y) && mouse_y <= (quitter->rect.y + moteur->echelle * 2)))
                SDL_SetTextureColorMod(quitter->texture,255,0,0);
            else SDL_SetTextureColorMod(quitter->texture,0,0,255);

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

    t_bouton * nouvelle_partie = NULL;
    t_bouton * charger_partie = NULL;
    t_bouton * options = NULL;
    t_bouton * quitter = NULL;

    nouvelle_partie = initialiserBouton(moteur,B_NOUVELLE_PARTIE);
    charger_partie = initialiserBouton(moteur,B_CHARGER_PARTIE);
    options = initialiserBouton(moteur,B_OPTIONS);
    quitter = initialiserBouton(moteur,B_QUITTER);


    while(handleEvents_menu(moteur,nouvelle_partie,charger_partie,options,quitter)==0){
        if(SDL_SetRenderDrawColor(moteur->renderer,0,0,0,255) !=0){
            printf("Erreur lors du SDL_SetRenderDrawColor dans le menu");
            return -1;
        }
        if(SDL_RenderClear(moteur->renderer)!=0){
            printf("Erreur lors du SDL_RenderClear dans le menu");
            return -1;
        }
        if(update_texture(moteur,nouvelle_partie,moteur->window_width /4 ,moteur->window_height *0.08,B_NOUVELLE_PARTIE ) != 0){
            printf("Erreur lors de la mise a jour des textures pour le bouton \"Nouvelle Partie\" dans le menu\n");
            return -1;
        }
        if(update_texture(moteur,charger_partie,moteur->window_width /4 ,moteur->window_height *0.30,B_CHARGER_PARTIE) != 0){
            printf("Erreur lors de la mise a jour des textures pour le bouton \"Charger Partie\" dans le menu\n");
            return -1;
        }
        if(update_texture(moteur,options,moteur->window_width /4 ,moteur->window_height *0.53,B_OPTIONS) != 0){
            printf("Erreur lors de la mise a jour des textures pour le bouton \"Options\" dans le menu\n");
            return -1;
        }
        if(update_texture(moteur,quitter,moteur->window_width /4 ,moteur->window_height *0.75,B_QUITTER) != 0){
            printf("Erreur lors de la mise a jour des textures pour le bouton \"Quitter\" dans le menu\n");
            return -1;
        }
        updateEchelle(moteur);
        SDL_RenderPresent(moteur->renderer);

    }
    detruireBouton(&nouvelle_partie);
    detruireBouton(&charger_partie);
    detruireBouton(&options);
    detruireBouton(&quitter);
    return 0;
}
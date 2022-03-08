#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <window.h>
#include <moteur.h>
#include <menu.h>


static int update_texture(t_moteur * moteur, t_menu * bouton,int rect_x, int rect_y){
    
    bouton->rect.x = rect_x;
    bouton->rect.y = rect_y;
    bouton->rect.w = moteur->echelle * 4.5;
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



static t_menu * initialiserMenu(t_moteur * moteur, char * bouton){

    t_menu * menu = malloc(sizeof(t_menu));
    if(menu == NULL){
        printf("Impossible d'allouer la mémoire pour la strcture menu (Nouvelle Partie)\n");
        return NULL;
    }

    SDL_Surface *surface;
    SDL_Color textColor = {25, 45, 200, 0};

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

    return menu;
}



static void detruireMenu(t_menu ** nouvelle_partie, t_menu ** charger_partie, t_menu ** options,t_menu ** quitter){

    SDL_DestroyTexture((*nouvelle_partie)->texture);
    SDL_DestroyTexture((*charger_partie)->texture);
    SDL_DestroyTexture((*options)->texture);
    SDL_DestroyTexture((*quitter)->texture);

    free(*nouvelle_partie);
    free(*charger_partie);
    free(*options);
    free(*quitter);
    *nouvelle_partie = NULL;
    *charger_partie = NULL;
    *options = NULL;
    *quitter = NULL;

}


/**
 * \brief 
 * 
 * \param structure moteur 
 * \return int 1 si l'utilisateur ferme la fenetre avec la croix, par defaut 0
 */
static int handleEvents_menu(t_moteur * moteur){
    //const char * key_code, * key_name; /**nom de la touche azerty, qwerty*/
    int mouse_x, mouse_y; /**Coordonnées du curseur*/
    SDL_Event e;
    while(SDL_PollEvent(&e))
    {
        switch (e.type)
        {
            case SDL_QUIT:
                return 1;
            /**Si un des boutons de la souris est relaché*/
            case SDL_MOUSEBUTTONDOWN :
                switch (e.button.button)
                {
                    case SDL_BUTTON_LEFT: /**Bouton gauche*/
                        printf("Mouse click");
                         if((mouse_x >= moteur->window_width /6 && mouse_x < (moteur->window_width / 6) +moteur->echelle * 4.5)&&(mouse_y >= moteur->window_height *0.08 && mouse_y < moteur->window_height *0.27))
                        printf("Nouvelle partie");
                            if((mouse_x >= moteur->window_width /6 && mouse_x < (moteur->window_width / 6) +moteur->echelle * 4.5)&&(mouse_y >= moteur->window_height *0.30 && mouse_y < moteur->window_height *0.50))
                        printf("Charger Partie");
                            if((mouse_x >= moteur->window_width /6 && mouse_x < (moteur->window_width / 6) +moteur->echelle * 4.5)&&(mouse_y >= moteur->window_height *0.53 && mouse_y < moteur->window_height *0.72))
                        printf("Options");
                            if((mouse_x >= moteur->window_width /6 && mouse_x < (moteur->window_width / 6) +moteur->echelle * 4.5)&&(mouse_y >= moteur->window_height *0.75 && mouse_y < moteur->window_height *0.9)){
                        printf("Quitter");
                        return 1;
                    }
                        break;
                    case SDL_BUTTON_MIDDLE: /**Molette*/
                        //printf("\nMouse scroll button released");
                        break;
                    case SDL_BUTTON_RIGHT: /**Bouton droit*/
                        printf("\nMouse right button released");
                        break;
                    default:
                        //printf("\nMouse got unknown event");
                        break;
                };
                break;
            case SDL_MOUSEMOTION:
                mouse_x = e.button.x, mouse_y = e.button.y;
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

    t_menu * nouvelle_partie = NULL;
    t_menu * charger_partie = NULL;
    t_menu * options = NULL;
    t_menu * quitter = NULL;

    nouvelle_partie = initialiserMenu(moteur,"Nouvelle Partie");

    charger_partie = initialiserMenu(moteur,"Continuer");

    options = initialiserMenu(moteur,"Options");

    quitter = initialiserMenu(moteur,"Quitter");


    while(handleEvents_menu(moteur)==0){
        if(SDL_SetRenderDrawColor(moteur->renderer,0,0,0,255) !=0){
            printf("Erreur lors du SDL_SetRenderDrawColor dans le menu");
            return -1;
        }
        if(SDL_RenderClear(moteur->renderer)!=0){
            printf("Erreur lors du SDL_RenderClear dans le menu");
            return -1;
        }
        if(update_texture(moteur,nouvelle_partie,moteur->window_width /6 ,moteur->window_height *0.08) != 0){
            printf("Erreur lors de la mise a jour des textures pour le bouton \"Nouvelle Partie\" dans le menu\n");
            return -1;
        }
        if(update_texture(moteur,charger_partie,moteur->window_width /6 ,moteur->window_height *0.30) != 0){
            printf("Erreur lors de la mise a jour des textures pour le bouton \"Charger Partie\" dans le menu\n");
            return -1;
        }
        if(update_texture(moteur,options,moteur->window_width /6 ,moteur->window_height *0.53) != 0){
            printf("Erreur lors de la mise a jour des textures pour le bouton \"Options\" dans le menu\n");
            return -1;
        }
        if(update_texture(moteur,quitter,moteur->window_width /6 ,moteur->window_height *0.75) != 0){
            printf("Erreur lors de la mise a jour des textures pour le bouton \"Quitter\" dans le menu\n");
            return -1;
        }
        updateEchelle(moteur);
        SDL_RenderPresent(moteur->renderer);

    }
    detruireMenu(&nouvelle_partie,&charger_partie,&options,&quitter);
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <window.h>
#include <moteur.h>
#include <menu.h>

/**
 * \brief Creer les boutons
 * 
 * \param moteur strcture moteur
 * \param text Texte a affiche dans le "bouton"
 * \param font Police d'ecriture
 * \param texture Texture du rectangle
 */
static void create_rectangle(t_moteur * moteur,char *text, TTF_Font *font, SDL_Texture **texture){

    SDL_Surface *surface;
    SDL_Color textColor = {25, 45, 200, 0};

    surface = TTF_RenderText_Solid(font, text, textColor);
    *texture = SDL_CreateTextureFromSurface(moteur->renderer, surface);
    SDL_FreeSurface(surface);

}
/**
 * \brief Met a jour les etxtures des boutons
 * 
 * \param moteur structure du moteur
 * \param rect rectangle
 * \param texture texture du rectangle
 * \param rect_x coordonnées x du sommet en haut a gauche du rectangle
 * \param rect_y coordonnées y du sommet en haut a gauche du rectangle
 * \return int 0 si succès, negatif si echec 
 */
static int update_texture(t_moteur * moteur, SDL_Rect * rect, SDL_Texture * texture, int rect_x, int rect_y){
    
    rect->x = rect_x;
    rect->y = rect_y;
    rect->w = moteur->echelle * 4.5;
    rect->h = moteur->echelle * 2;

    if(SDL_RenderDrawRect(moteur->renderer,rect)!=0){
        printf("Erreur lors de l'affichage d'un bouton\n");
        return -1;
    }

    if(SDL_RenderCopy(moteur->renderer, texture, NULL, rect)!=0){
        printf("Erreur du SDL_RenderCopy dans le menu\n");
        return -1;
    }

    return 0;
}


/**
 * \brief Initalise le menu
 * 
 * \param moteur structure du moteur
 * \param nouvelle_partie Rectangle pour le bouton "Nouvelle Partie"
 * \param continuer Rectangle pour le bouton "Continuer"
 * \param options Rectangle pour le bouton "Options"
 * \param quitter Rectangle pour le bouton "Quitter"
 * \param texture_nouvelle_partie Texture pour le bouton "Nouvelle Partie"
 * \param texture_continuer Texture pour le bouton "Continuer"
 * \param texture_options Texture pour le bouton "Options"
 * \param texture_quitter Texture pour le bouton "Quitter"
 * \return int 0 si succès, negatif si echec
 */
static int initialiserMenu(t_moteur * moteur, SDL_Rect nouvelle_partie,SDL_Rect continuer,SDL_Rect options,SDL_Rect quitter,SDL_Texture **texture_nouvelle_partie,SDL_Texture**texture_continuer,SDL_Texture**texture_options,SDL_Texture**texture_quitter){

    TTF_Font *font = TTF_OpenFont("./PressStart2P-Regular.ttf", 1000);

    if (font == NULL) {
        fprintf(stderr, "error: font not found\n");
        return -1;
    }

    create_rectangle(moteur,"Nouvelle Partie", font, texture_nouvelle_partie);
    create_rectangle(moteur,"Continuer", font, texture_continuer);
    create_rectangle(moteur,"Options", font, texture_options);
    create_rectangle(moteur,"Quitter", font, texture_quitter);

    return 0;
}




/**
 * \brief detruit les textures des boutons
 * 
 * \param texture_nouvelle_partie Texture pour le bouton "Nouvelle Partie"
 * \param texture_continuer Texture pour le bouton "Continuer"
 * \param texture_options Texture pour le bouton "Options"
 * \param texture_quitter Texture pour le bouton "Quitter"
 */
static void detruireMenu(SDL_Texture *texture_nouvelle_partie,SDL_Texture*texture_continuer,SDL_Texture*texture_options,SDL_Texture*texture_quitter){

    SDL_DestroyTexture(texture_nouvelle_partie);
    SDL_DestroyTexture(texture_continuer);
    SDL_DestroyTexture(texture_options);
    SDL_DestroyTexture(texture_quitter);

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
            case SDL_MOUSEBUTTONUP:
                switch (e.button.button)
                {
                    case SDL_BUTTON_LEFT: /**Bouton gauche*/
                        //printf("\nMouse left button released");
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

    SDL_Rect nouvelle_partie,continuer,options,quitter;
    SDL_Texture *texture_nouvelle_partie = NULL,*texture_continuer = NULL,*texture_options = NULL,*texture_quitter = NULL;

    initialiserMenu(moteur,nouvelle_partie,continuer,options,quitter,&texture_nouvelle_partie,&texture_continuer,&texture_options,&texture_quitter);
    while(handleEvents_menu(moteur)==0){
        if(SDL_SetRenderDrawColor(moteur->renderer,0,0,0,255) !=0){
            printf("Erreur lors du SDL_SetRenderDrawColor dans le menu");
            return -1;
        }
        if(SDL_RenderClear(moteur->renderer)!=0){
            printf("Erreur lors du SDL_RenderClear dans le menu");
            return -1;
        }
        if(update_texture(moteur,&nouvelle_partie,texture_nouvelle_partie,moteur->window_width /6 ,moteur->window_height *0.08) != 0){
            printf("Erreur lors de la mise a jour des textures pour le bouton \"Nouvelle Partie\" dans le menu\n");
            return -1;
        }
        if(update_texture(moteur,&continuer,texture_continuer,moteur->window_width /6 ,moteur->window_height *0.30) != 0){
            printf("Erreur lors de la mise a jour des textures pour le bouton \"Charger Partie\" dans le menu\n");
            return -1;
        }
        if(update_texture(moteur,&options,texture_options,moteur->window_width /6 ,moteur->window_height *0.53) != 0){
            printf("Erreur lors de la mise a jour des textures pour le bouton \"Options\" dans le menu\n");
            return -1;
        }
        if(update_texture(moteur,&quitter,texture_quitter,moteur->window_width /6 ,moteur->window_height *0.75) != 0){
            printf("Erreur lors de la mise a jour des textures pour le bouton \"Quitter\" dans le menu\n");
            return -1;
        }
        updateEchelle(moteur);
        SDL_RenderPresent(moteur->renderer);

    }
    detruireMenu(texture_nouvelle_partie,texture_continuer,texture_options,texture_quitter);
    return 0;
}
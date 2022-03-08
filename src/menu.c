#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <window.h>
#include <moteur.h>
#include <menu.h>

/**
 * \brief Get the text and rect object
 * 
 * \param moteur 
 * \param x 
 * \param y 
 * \param text 
 * \param font 
 * \param texture 
 * \param rect 
 * \param rect_y 
 * \return int 
 */
static void create_rectangle(t_moteur * moteur,char *text, TTF_Font *font, SDL_Texture **texture){

    SDL_Surface *surface;
    SDL_Color textColor = {255, 255, 255, 0};

    surface = TTF_RenderText_Solid(font, text, textColor);
    *texture = SDL_CreateTextureFromSurface(moteur->renderer, surface);
    SDL_FreeSurface(surface);
}

static int update_texture(t_moteur * moteur, SDL_Rect * rect, SDL_Texture * texture, int rect_x, int rect_y){
    rect->x = rect_x;
    rect->y = rect_y;
    rect->w = moteur->echelle * 1.5;
    rect->h = moteur->echelle * 1.5;

    if(SDL_SetRenderDrawColor(moteur->renderer,187,255,75,255)==1){
        printf("Erreur lors de la mise en couleur d'un bouton\n");
        return -1;
    }
    if(SDL_RenderDrawRect(moteur->renderer,rect)==1){
        printf("Erreur lors de l'affichage d'un bouton\n");
        return -1;
    }

    SDL_RenderCopy(moteur->renderer, texture, NULL, rect);
    
    return 0;
}




/**
 * \brief 
 * 
 * \param moteur 
 * \param nouvelle_partie 
 * \param continuer 
 * \param options 
 * \param quitter 
 * \param texture_nouvelle_partie 
 * \param texture_continuer 
 * \param texture_options 
 * \param texture_quitter 
 * \return int 
 */
static int initialiserMenu(t_moteur * moteur, SDL_Rect nouvelle_partie,SDL_Rect continuer,SDL_Rect options,SDL_Rect quitter,SDL_Texture *texture_nouvelle_partie,SDL_Texture*texture_continuer,SDL_Texture*texture_options,SDL_Texture*texture_quitter){

    TTF_Font *font = TTF_OpenFont("/info/etu/l2info/s204416/Bureau/Star-Seeker/OpenSans-Regular.ttf", 20);

    if (font == NULL) {
        fprintf(stderr, "error: font not found\n");
        return -1;
    }

    create_rectangle(moteur,"Nouvelle Partie", font, &texture_nouvelle_partie);
    create_rectangle(moteur,"Continuer", font, &texture_continuer);
    create_rectangle(moteur,"Options", font, &texture_options);
    create_rectangle(moteur,"Quitter", font, &texture_quitter);

    return 0;
}




/**
 * \brief
 *
 * \param texture_nouvelle_partie
 * \param texture_continuer
 * \param texture_options
 * \param texture_quitter
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
 * \param e 
 * \return int 
 */
static int handleEvents_menu(){
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
                    if(mouse_x == 50 && mouse_y == 50)
                        printf("happy");
                /**Recupere les coordonées x et y relative a la fenetre*/
                //printf("\nMouse has moved : Mouse coordinates relative to window : x = %d, y = %d", mouse_x, mouse_y);
                break;
        }
    }
    return 0;
}

/**
 * \brief 
 * 
 * \param moteur 
 * \return int 
 */
int chargerMenu(t_moteur * moteur){

    SDL_Rect nouvelle_partie,continuer,options,quitter;
    SDL_Texture *texture_nouvelle_partie = NULL,*texture_continuer = NULL,*texture_options = NULL,*texture_quitter = NULL;

    initialiserMenu(moteur,nouvelle_partie,continuer,options,quitter,texture_nouvelle_partie,texture_continuer,texture_options,texture_quitter);
    while(handleEvents_menu()==0){
        SDL_RenderClear(moteur->renderer);
        update_texture(moteur,&nouvelle_partie,texture_nouvelle_partie,moteur->window_width /4 ,moteur->window_height *0.20);
        update_texture(moteur,&continuer,texture_continuer,moteur->window_width /4 ,moteur->window_height *0.4);
        update_texture(moteur,&options,texture_options,moteur->window_width /4 ,moteur->window_height *0.6);
        update_texture(moteur,&quitter,texture_quitter,moteur->window_width /4 ,moteur->window_height *.8);
        updateEchelle(moteur);
        SDL_RenderPresent(moteur->renderer);

    }
    detruireMenu(texture_nouvelle_partie,texture_continuer,texture_options,texture_quitter);
    return 0;
}

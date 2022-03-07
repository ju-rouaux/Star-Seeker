#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <window.h>
#include <moteur.h>
#include <menu.h>


/*
- x, y: upper left corner.
- texture, rect: outputs.
*/
void get_text_and_rect(t_moteur * moteur, int x, int y, char *text,
        TTF_Font *font, SDL_Texture **texture, SDL_Rect *rect, int rect_y) {
    SDL_Surface *surface;
    SDL_Color textColor = {255, 255, 255, 0};
    surface = TTF_RenderText_Solid(font, text, textColor);
    *texture = SDL_CreateTextureFromSurface(moteur->renderer, surface);
    SDL_FreeSurface(surface);
    rect->x = 100;
    rect->y = rect_y;
    rect->w = moteur->echelle * 1.2;
    rect->h = moteur->echelle * 1.2;
    SDL_SetRenderDrawColor(moteur->renderer,187,255,75,255);
    SDL_RenderDrawRect(moteur->renderer,rect);
}
int charger_bouton(SDl_Rect * nouvelle_partie, SDL_Rect * continuer, SDL_Rect * options, SDL_Rect * quitter){
get_text_and_rect(moteur, 20, 50, "Nouvelle Partie", font, &texture_nouvelle_partie, &nouvelle_partie, moteur->window_height * 0.01);
    updateEchelle(moteur);
    get_text_and_rect(moteur, 20, 100, "Continuer", font, &texture_continuer, &continuer,moteur->window_height *0.25);
    updateEchelle(moteur);
    get_text_and_rect(moteur, 20, 200, "Options", font, &texture_options, &options, moteur->window_height *0.5);
    updateEchelle(moteur);
    get_text_and_rect(moteur, 20, 400, "Quitter", font, &texture_quitter, &quitter,moteur->window_height * 0.75);
    updateEchelle(moteur);
        /* Use TTF textures. */
        SDL_RenderCopy(moteur->renderer, texture_nouvelle_partie, NULL, &nouvelle_partie);
        updateEchelle(moteur);
        SDL_RenderCopy(moteur->renderer, texture_continuer, NULL, &continuer);
        updateEchelle(moteur);
        SDL_RenderCopy(moteur->renderer, texture_options, NULL, &options);
        updateEchelle(moteur);
        SDL_RenderCopy(moteur->renderer, texture_quitter, NULL, &quitter);
        updateEchelle(moteur);
}

int chargerMenu(t_moteur * moteur){
    SDL_Rect nouvelle_partie,continuer,options,quitter;
    SDL_Texture *texture_nouvelle_partie,*texture_continuer,*texture_options,*texture_quitter;
    SDL_event event;


    TTF_Init();
    TTF_Font *font = TTF_OpenFont("./OpenSans-Regular.ttf", 20);
    if (font == NULL) {
        fprintf(stderr, "error: font not found\n");
        exit(EXIT_FAILURE);
    }

    charger_bouton(nouvelle_partie,continuer,options,quitter);

    SDL_RenderPresent(moteur->renderer);
    updateEchelle(moteur);

    while(handleEvents_menu(&event)){


    }

    SDL_DestroyTexture(texture_nouvelle_partie);
    SDL_DestroyTexture(texture_continuer);
    SDL_DestroyTexture(texture_options);
    SDL_DestroyTexture(texture_quitter);
    TTF_Quit();

    return 0;
}

int handleEvents(SQL_Event event) {

    //const char * key_code, * key_name; /**nom de la touche azerty, qwerty*/
    //int mouse_x, mouse_y; /**Coordonnées du curseur*/
    int scrolling; /**Boléen, 1 si on scrolle vers le haut, 0 si on scrolle vers le bas*/
    while(SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT:
                return 1;
             /**Si un des boutons de la souris est relaché*/
            case SDL_MOUSEBUTTONUP:
                switch (event.button.button)
                {
                    case SDL_BUTTON_LEFT: /**Bouton gauche*/
                        case SD
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
                //mouse_x = event.button.x, mouse_y = event.button.y;
                /**Recupere les coordonées x et y relative a la fenetre*/
                //printf("\nMouse has moved : Mouse coordinates relative to window : x = %d, y = %d", mouse_x, mouse_y);
                break;
            case SDL_MOUSEWHEEL:
                scrolling = event.wheel.y; /**Recupere la valeur de la molette, 1 si on scrolle vers le haut, 0 si on scrolle vers le bas */
                if (scrolling < 0)
                    //printf("\nScrolling down");
                if (scrolling > 0)
                    //printf("\nScrolling up");

                break;


            //Gestion du clavier
            case SDL_KEYDOWN:
                switch (event.key.keysym.scancode)
                {
                    case SDL_SCANCODE_W: //Z
                        joueur->flags->to_up = joueur->flags->to_down + 1;
                        break;
                    case SDL_SCANCODE_A: //Q
                        joueur->flags->to_left = joueur->flags->to_right + 1;
                        break;
                    case SDL_SCANCODE_S: //S
                        joueur->flags->to_down = joueur->flags->to_up + 1;
                        break;
                    case SDL_SCANCODE_D: //D
                        joueur->flags->to_right = joueur->flags->to_left + 1;
                        break;
                    
                    case SDL_SCANCODE_L: //L !!! Temporaire
                        joueur->flags->shooting = 1;
                    
                    default:
                        break;
                }
                break;
            case SDL_KEYUP: /**touche relachée*/
                switch (event.key.keysym.scancode)
                {
                    case SDL_SCANCODE_W: //Z
                        joueur->flags->to_up = 0;
                        break;
                    case SDL_SCANCODE_A: //Q
                        joueur->flags->to_left = 0;
                        break;
                    case SDL_SCANCODE_S: //S
                        joueur->flags->to_down = 0;
                        break;
                    case SDL_SCANCODE_D: //D
                        joueur->flags->to_right = 0;

                    case SDL_SCANCODE_L: //L !!! Temporaire
                        joueur->flags->shooting = 0;
                        break;
                    
                    default:
                        break;
                }
                break;



            //Gestion de la fenetre
            case SDL_WINDOWEVENT:
                switch (event.window.event)
                {
                    case SDL_WINDOWEVENT_SHOWN: /**Fenetre montrée*/
                        printf("\nWindow shown");
                        break;
                    case SDL_WINDOWEVENT_HIDDEN: /**Fenetre cachée*/
                        printf("\nWindow hidden");
                        break;
                    case SDL_WINDOWEVENT_MAXIMIZED: /**Fenetre maximisée*/
                        printf("\nWindow maximized");
                        break;
                    case SDL_WINDOWEVENT_MINIMIZED: /**Fenetre minimisée*/
                        printf("\nWindow minimized");
                        break;
                }
                break;
        }
    }
    return 0;
}

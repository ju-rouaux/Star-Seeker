/**
 * \file events.c
 * \author Guillaume
 * \brief Module de gestion des evenements (souris/clavier/fenetre)
 */

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <joueur.h>
#include <menu.h>
#include <moteur.h>

/**
 * \brief Gere tout les evenements liés a la souris, au clavier et a la fenetre
 * 
 * \return Boleen, vrai si l'utilisateur ferme la fenetre avec la croix, par defaut 0
 */

int handleEvents(t_joueur * joueur, t_moteur * moteur) {

    //const char * key_code, * key_name; /*nom de la touche azerty, qwerty*/
    //int mouse_x, mouse_y; /*Coordonnées du curseur*/
    int scrolling; /*Boléen, 1 si on scrolle vers le haut, 0 si on scrolle vers le bas*/

    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT:
                return -1;
            
            /*gestion de la souris*/
            /*Si un des boutons de la souris est appuyé*/
            case SDL_MOUSEBUTTONDOWN:
                switch (event.button.button)
                {
                    case SDL_BUTTON_LEFT: /**Bouton gauche*/
                        //printf("\nMouse left button pressed");
                        break;
                    case SDL_BUTTON_MIDDLE: /**Molette*/
                        //printf("\nMouse scroll button pressed");
                        break;
                    case SDL_BUTTON_RIGHT: /**Bouton droit*/
                        //printf("\nMouse right button pressed");
                        break;
                    default: /**Cas d'erreur*/
                        //printf("\nMouse got unknown event");
                        break;
                };
                switch (event.button.clicks)
                { /*Nombre de clics*/
                    case 1: /*Clic simple*/
                        //printf("\nSimple click");
                        break;
                    case 2: /*Double clic*/
                        //printf("\nDouble click");
                        break;
                    default: /*Si plus qu'un double clic*/
                        printf("\nClicked too many times hahaha");
                        break;
                };
                break;

             /*Si un des boutons de la souris est relaché*/
            case SDL_MOUSEBUTTONUP:
                switch (event.button.button)
                {
                    case SDL_BUTTON_LEFT: /*Bouton gauche*/
                        //printf("\nMouse left button released");
                        break;
                    case SDL_BUTTON_MIDDLE: /*Molette*/
                        //printf("\nMouse scroll button released");
                        break;
                    case SDL_BUTTON_RIGHT: /*Bouton droit*/
                        printf("\nMouse right button released");
                        break;
                    default:
                        //printf("\nMouse got unknown event");
                        break;
                };
                break;
            case SDL_MOUSEMOTION:
                //mouse_x = event.button.x, mouse_y = event.button.y;
                /*Recupere les coordonées x et y relative a la fenetre*/
                //printf("\nMouse has moved : Mouse coordinates relative to window : x = %d, y = %d", mouse_x, mouse_y);
                break;
            case SDL_MOUSEWHEEL:
                scrolling = event.wheel.y; /*Recupere la valeur de la molette, 1 si on scrolle vers le haut, 0 si on scrolle vers le bas */
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
                    case SDL_SCANCODE_ESCAPE: //ESC
                        chargerMenu(moteur);
                        break;
                    case SDL_SCANCODE_O: //O !!! Temporaire
                        return -88;
                        break;
                    case SDL_SCANCODE_P: //P !!! Temporaire
                        return -99;
                        break;
                    default:
                        break;
                }
                break;
            case SDL_KEYUP: /*touche relachée*/
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
                    case SDL_WINDOWEVENT_SHOWN: /*Fenetre montrée*/
                        printf("\nWindow shown");
                        break;
                    case SDL_WINDOWEVENT_HIDDEN: /*Fenetre cachée*/
                        printf("\nWindow hidden");
                        break;
                    case SDL_WINDOWEVENT_MAXIMIZED: /*Fenetre maximisée*/
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
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
#include <event.h>
#include <main.h>

/**
 * \brief Gere tout les evenements liés a la souris, au clavier et a la fenetre
 * 
 * \return Boleen, vrai si l'utilisateur ferme la fenetre avec la croix, par defaut 0
 */

e_code_main handleEvents(t_joueur * joueur, t_parametres * parametres) {

    //const char * key_code, * key_name; /*nom de la touche azerty, qwerty*/
    //int mouse_x, mouse_y; /*Coordonnées du curseur*/
    int scrolling; /*Boléen, 1 si on scrolle vers le haut, 0 si on scrolle vers le bas*/

    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT:
                return JEU_QUITTER;
            
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

                if(parametres->key_up == event.key.keysym.scancode)
                    joueur->flags->to_up = joueur->flags->to_down + 1;
                else if(parametres->key_left == event.key.keysym.scancode)
                    joueur->flags->to_left = joueur->flags->to_right + 1;
                else if (parametres->key_down == event.key.keysym.scancode)
                    joueur->flags->to_down = joueur->flags->to_up + 1;
                else if  (parametres->key_right == event.key.keysym.scancode)
                    joueur->flags->to_right = joueur->flags->to_left + 1;
                else if  (parametres->key_projectile == event.key.keysym.scancode)
                    joueur->flags->shooting = 1;
                else if  (parametres->key_interaction == event.key.keysym.scancode)
                {
                    if(joueur->flags->interaction == 0)
                        joueur->flags->interaction = 1;
                    else    //Passer le flag à -1 si la touche est maintenue
                        joueur->flags->interaction = -1;
                }
                else switch (event.key.keysym.scancode)
                {
                   /* A comment. */
                    case SDL_SCANCODE_ESCAPE: //ESC
                        return M_PRINCIPAL;
                        break;
                    case SDL_SCANCODE_O: //O !!! Temporaire
                        return NIVEAU_PRECEDENT;
                        break;
                    case SDL_SCANCODE_P: //P !!! Temporaire
                        return NIVEAU_SUIVANT;
                        break;
                    case SDL_SCANCODE_TAB: //TAB
                        joueur->flags->map_showing = 1;
                        break;
                    default:
                        break;
                }
                break;

            case SDL_KEYUP: /*touche relachée*/

                if(parametres->key_up == event.key.keysym.scancode)
                    joueur->flags->to_up = 0;
                else if(parametres->key_left == event.key.keysym.scancode)
                    joueur->flags->to_left = 0;
                else if (parametres->key_down == event.key.keysym.scancode)
                    joueur->flags->to_down = 0;
                else if (parametres->key_right == event.key.keysym.scancode)
                    joueur->flags->to_right = 0;
                else if (parametres->key_projectile == event.key.keysym.scancode)
                    joueur->flags->shooting = 0;
                else if  (parametres->key_interaction == event.key.keysym.scancode)
                    joueur->flags->interaction = 0;
                else switch (event.key.keysym.scancode)
                {
                    case SDL_SCANCODE_TAB: //TAB
                        joueur->flags->map_showing = 0;
                        break;
                    default:
                        break;
                }


            //Gestion de la fenetre
            case SDL_WINDOWEVENT:
                switch (event.window.event)
                {
                    case SDL_WINDOWEVENT_SHOWN: /*Fenetre montrée*/
                        printf("Window shown\n");
                        break;
                    case SDL_WINDOWEVENT_HIDDEN: /*Fenetre cachée*/
                        printf("Window hidden\n");
                        break;
                    case SDL_WINDOWEVENT_MAXIMIZED: /*Fenetre maximisée*/
                        printf("Window maximized\n");
                        break;
                    case SDL_WINDOWEVENT_MINIMIZED: /**Fenetre minimisée*/
                        printf("Window minimized\n");
                        break;
                }
                break;
        }
    }
    return NIVEAU_CONTINUER;
}
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

e_code_main handleEvents(t_joueur * joueur, t_parametres * parametres)
{
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT:
                return JEU_QUITTER;

            // -- Gestion du clavier --
            //Appui
            case SDL_KEYDOWN:
                //Avancer vers le haut
                if(parametres->key_up == event.key.keysym.scancode)
                    joueur->flags->to_up = joueur->flags->to_down + 1;

                //Avancer vers la gauche
                else if(parametres->key_left == event.key.keysym.scancode)
                    joueur->flags->to_left = joueur->flags->to_right + 1;

                //Avancer vers le bas
                else if (parametres->key_down == event.key.keysym.scancode)
                    joueur->flags->to_down = joueur->flags->to_up + 1;
                
                //Avancer vers la droite
                else if  (parametres->key_right == event.key.keysym.scancode)
                    joueur->flags->to_right = joueur->flags->to_left + 1;
               
                //Interaction
                else if  (parametres->key_interaction == event.key.keysym.scancode)
                {
                    if(joueur->flags->interaction == 0)
                        joueur->flags->interaction = 1;
                    else    //Passer le flag à -1 si la touche est maintenue
                        joueur->flags->interaction = -1;
                }
                
                //Autres touches
                else switch (event.key.keysym.scancode)
                {
                    case SDL_SCANCODE_ESCAPE: //ESC
                        return M_NIVEAU;
                        break;
                    case SDL_SCANCODE_TAB: //TAB
                        joueur->flags->map_shown = 1;
                        break;

                    case SDL_SCANCODE_UP:
                        joueur->flags->attack_up = joueur->flags->attack_down + 1;
                        break;

                    case SDL_SCANCODE_DOWN:
                        joueur->flags->attack_down = joueur->flags->attack_up + 1;
                        break;

                    case SDL_SCANCODE_LEFT:
                        joueur->flags->attack_left = joueur->flags->attack_right + 1;
                        break;

                    case SDL_SCANCODE_RIGHT:
                        joueur->flags->attack_right = joueur->flags->attack_left + 1;
                        break;

                    case SDL_SCANCODE_SPACE:
                        if(joueur->flags->dash == 0)
                            joueur->flags->dash = 1;
                        break;
                    
                    default:
                        break;
                }
                break;

            //Relachement
            case SDL_KEYUP:
                if(parametres->key_up == event.key.keysym.scancode)
                    joueur->flags->to_up = 0;

                else if(parametres->key_left == event.key.keysym.scancode)
                    joueur->flags->to_left = 0;
                
                else if (parametres->key_down == event.key.keysym.scancode)
                    joueur->flags->to_down = 0; 
                
                else if (parametres->key_right == event.key.keysym.scancode)
                    joueur->flags->to_right = 0;
                
                else if  (parametres->key_interaction == event.key.keysym.scancode)
                    joueur->flags->interaction = 0;
                
                else switch (event.key.keysym.scancode)
                {
                    case SDL_SCANCODE_TAB: //TAB
                        joueur->flags->map_shown = 0;
                        break;

                    case SDL_SCANCODE_UP:
                        joueur->flags->attack_up = 0;
                        break;

                    case SDL_SCANCODE_DOWN:
                        joueur->flags->attack_down = 0;
                        break;

                    case SDL_SCANCODE_LEFT:
                        joueur->flags->attack_left = 0;
                        break;

                    case SDL_SCANCODE_RIGHT:
                        joueur->flags->attack_right = 0;
                        break;

                    default:
                        break;
                }
                break;
        }
    }
    return NIVEAU_CONTINUER;
}
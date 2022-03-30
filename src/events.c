/**
 * \file events.c
 * \author Guillaume
 * \brief Module de gestion des evenements (souris/clavier/fenetre)
 * Detecte les evenements liés au clics de la souris, aux touches appuyées ou relachées et a la croix de la fenetre pour quitter
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
 * \param joueur le joueur
 * \param parametres parametres du jeu (touches et volume)
 * \return code de succès et d'erreur personnalisé
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

/*------------------------------------------------- Déplacements du joueur  -------------------------------------------------------------------*/

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

/*------------------------------------------------- Attaques du joueurs et autre compétence(s)  -------------------------------------------------------------------*/
 
                 //Attaque vers le haut
                else if  (parametres->attack_up == event.key.keysym.scancode)
                    joueur->flags->attack_up = joueur->flags->attack_down + 1;
                //Attaque vers le bas
                else if  (parametres->attack_down == event.key.keysym.scancode)
                    joueur->flags->attack_down = joueur->flags->attack_up + 1;
                //Attaque vers la droite
                else if  (parametres->attack_right == event.key.keysym.scancode)
                    joueur->flags->attack_right = joueur->flags->attack_left + 1;
                //Attaque vers la gauche
                else if  (parametres->attack_left == event.key.keysym.scancode)
                    joueur->flags->attack_left = joueur->flags->attack_right + 1;
                //Dash
                else if  (parametres->dash == event.key.keysym.scancode){
                    if(joueur->flags->dash == 0)
                            joueur->flags->dash = 1;
                }

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
                    default:
                        break;
                }
                break;

            //Relachement
            case SDL_KEYUP:
/*------------------------------------------------- Déplacements du joueur  -------------------------------------------------------------------*/
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
                
/*------------------------------------------------- Attaques du joueurs et autre compétence(s)  -------------------------------------------------------------------*/
                 //Attaque vers le haut
                else if  (parametres->attack_up == event.key.keysym.scancode)
                    joueur->flags->attack_up = 0;
                //Attaque vers le bas
                else if  (parametres->attack_down == event.key.keysym.scancode)
                    joueur->flags->attack_down = 0;
                //Attaque vers la droite
                else if  (parametres->attack_right == event.key.keysym.scancode)
                    joueur->flags->attack_right = 0;
                //Attaque vers la gauche
                else if  (parametres->attack_left == event.key.keysym.scancode)
                    joueur->flags->attack_left = 0;
                //Dash
                else if  (parametres->dash == event.key.keysym.scancode){
                    if(joueur->flags->dash == 0)
                            joueur->flags->dash = 1;
                }
                
                else switch (event.key.keysym.scancode)
                {
                    case SDL_SCANCODE_TAB: //TAB
                        joueur->flags->map_shown = 0;
                        break;
                    default:
                        break;
                }
                break;
        }
    }
    return NIVEAU_CONTINUER;
}
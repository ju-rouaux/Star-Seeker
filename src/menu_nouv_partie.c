#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <window.h>
#include <moteur.h>
#include <menu.h>
#include <menu_nouv_partie.h>



static int handleEvents_options(t_moteur * moteur, t_bouton * nouvelle_galaxie, t_bouton * retour){

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
                        if(((mouse_x >= nouvelle_galaxie->rect.x) && (mouse_x <= (nouvelle_galaxie->rect.x + moteur->echelle * (strlen(B_NOUVELLE_GALAXIE)/2.5))))&&((mouse_y >= nouvelle_galaxie->rect.y) && mouse_y <= (nouvelle_galaxie->rect.y + moteur->echelle * 2))){
                            printf("Nouvelle Partie");
                        }
                        // if(((mouse_x >= texte->rect.x) && (mouse_x <= (texte->rect.x + moteur->echelle * 4.5)))&&((mouse_y >= texte->rect.y) && (mouse_y <= (texte->rect.y + moteur->echelle * 2)))){
                        //     SDL_StartTextInput();
                        //     if(e.type == SDL_KEYDOWN)
                        //         printf("Test");
                        // }
                        // if(((mouse_x >= options->rect.x )&& (mouse_x <= (options->rect.x + moteur->echelle * 4.5)))&&((mouse_y >= options->rect.y) && (mouse_y <= (options->rect.y + moteur->echelle * 2)))){
                        //     printf("Options");
                        // }
                         if(((mouse_x >= retour->rect.x) && (mouse_x <= (retour->rect.x + moteur->echelle * (strlen(B_RETOUR)/2.5))))&&((mouse_y >= retour->rect.y) && mouse_y <= (retour->rect.y + moteur->echelle * 2))){
                            chargerMenu(moteur);
                        return 1;
                        }
                        break;
                    default:break;
                };
                break;
        case SDL_MOUSEMOTION :

            if(((mouse_x >= nouvelle_galaxie->rect.x) && (mouse_x <= (nouvelle_galaxie->rect.x + moteur->echelle * 4.5)))&&((mouse_y >= nouvelle_galaxie->rect.y) && (mouse_y <= (nouvelle_galaxie->rect.y + moteur->echelle * 2))))
                SDL_SetTextureColorMod(nouvelle_galaxie->texture,255,0,0);
            else SDL_SetTextureColorMod(nouvelle_galaxie->texture,0,0,255);

            // if(((mouse_x >= texte->rect.x) && (mouse_x <= (texte->rect.x + moteur->echelle * 4.5)))&&((mouse_y >= texte->rect.y) && (mouse_y <= (texte->rect.y + moteur->echelle * 2))))
            //     SDL_SetTextureColorMod(texte->texture,255,0,0);
            // else SDL_SetTextureColorMod(texte->texture,0,0,255);

            // if(((mouse_x >= options->rect.x )&& (mouse_x <= (options->rect.x + moteur->echelle * 4.5)))&&((mouse_y >= options->rect.y) && (mouse_y <= (options->rect.y + moteur->echelle * 2))))
            //     SDL_SetTextureColorMod(options->texture,255,0,0);
            // else SDL_SetTextureColorMod(options->texture,0,0,255);

            if(((mouse_x >= retour->rect.x) && (mouse_x <= (retour->rect.x + moteur->echelle * 4.5)))&&((mouse_y >= retour->rect.y) && mouse_y <= (retour->rect.y + moteur->echelle * 2)))
                SDL_SetTextureColorMod(retour->texture,255,0,0);
            else SDL_SetTextureColorMod(retour->texture,0,0,255);

        break;
        }
    }
    return 0;
}



int charger_menuNouvellePartie(t_moteur * moteur){

    t_bouton * nouvelle_galaxie = NULL;
    t_bouton * retour = NULL;

    nouvelle_galaxie = initialiserBouton(moteur,B_NOUVELLE_GALAXIE);
    retour = initialiserBouton(moteur,B_RETOUR);


    while(handleEvents_options(moteur,nouvelle_galaxie,retour)==0){
        if(SDL_SetRenderDrawColor(moteur->renderer,0,0,0,255) !=0){
            printf("Erreur lors du SDL_SetRenderDrawColor dans le menu");
            return -1;
        }
        if(SDL_RenderClear(moteur->renderer)!=0){
            printf("Erreur lors du SDL_RenderClear dans le menu");
            return -1;
        }
        if(update_texture(moteur,nouvelle_galaxie,moteur->window_width /4 ,moteur->window_height *0.18,B_NOUVELLE_PARTIE ) != 0){
            printf("Erreur lors de la mise a jour des textures pour le bouton \"Nouvelle Partie\" dans le menu\n");
            return -1;
        }
        // if(update_texture(moteur,texte,moteur->window_width /4 ,moteur->window_height *0.30,B_CHARGER_PARTIE) != 0){
        //     printf("Erreur lors de la mise a jour des textures pour le bouton \"Charger Partie\" dans le menu\n");
        //     return -1;
        // }
        if(update_texture(moteur,retour,moteur->window_width /4 ,moteur->window_height *0.58,B_OPTIONS) != 0){
            printf("Erreur lors de la mise a jour des textures pour le bouton \"Options\" dans le menu\n");
            return -1;
        }
        // if(update_texture(moteur,quitter,moteur->window_width /4 ,moteur->window_height *0.75,B_QUITTER) != 0){
        //     printf("Erreur lors de la mise a jour des textures pour le bouton \"Quitter\" dans le menu\n");
        //     return -1;
        // }
        updateEchelle(moteur);
        SDL_RenderPresent(moteur->renderer);

    }
    detruireBouton(&nouvelle_galaxie);
    detruireBouton(&retour);

    return 0;
}

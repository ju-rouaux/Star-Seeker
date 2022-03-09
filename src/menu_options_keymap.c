#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <window.h>
#include <moteur.h>
#include <menu.h>
#include <menu_options.h>
#include <menu_options_keymap.h>


/**
 * \brief Gere tout les evenements liées au boutons danns le sous menu keymap
 * 
 * \param moteur strcture moteur
 * \param haut structure pour le bouton "haut"
 * \param bas structure pour le bouton "bas"
 * \param droite structure pour le bouton "droite"
 * \param gauche structure pour le bouton "gauche"
 * \param projectile structure pour le bouton "projectile"
 * \param retour structure pour le bouton "retour"
 * \return int 0 si succes, 1 si l'utilisateur ferme la fenetre, autre chiffre positif selon le bouton appuyé
 */
static int handleEvents_options_keymap(t_moteur * moteur, t_bouton * haut, t_bouton * bas,t_bouton * droite,t_bouton * gauche,t_bouton * projectile, t_bouton * retour){

    int mouse_x, mouse_y;
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
                        if(((mouse_x >= haut->rect.x) && (mouse_x <= (haut->rect.x + moteur->echelle * (strlen(B_UP)/2.5))))&&((mouse_y >= haut->rect.y) && mouse_y <= (haut->rect.y + moteur->echelle * 2)))
                            return 2;
                        if(((mouse_x >= bas->rect.x) && (mouse_x <= (bas->rect.x + moteur->echelle * (strlen(B_DOWN)/2.5))))&&((mouse_y >= bas->rect.y) && (mouse_y <= (bas->rect.y + moteur->echelle * 2))))
                            return 3;
                        if(((mouse_x >= droite->rect.x )&& (mouse_x <= (droite->rect.x + moteur->echelle * (strlen(B_RIGHT)/2.5))))&&((mouse_y >= droite->rect.y) && (mouse_y <= (droite->rect.y + moteur->echelle * 2))))
                            return 4;
                        if(((mouse_x >= gauche->rect.x) && (mouse_x <= (gauche->rect.x + moteur->echelle * (strlen(B_LEFT)/2.5))))&&((mouse_y >= gauche->rect.y) && (mouse_y <= (gauche->rect.y + moteur->echelle * 2))))
                                return 5;
                        if(((mouse_x >= projectile->rect.x )&& (mouse_x <= (projectile->rect.x + moteur->echelle * (strlen(B_PROJECTILE)/2.5))))&&((mouse_y >= projectile->rect.y) && (mouse_y <= (projectile->rect.y + moteur->echelle * 2))))
                            return 6;
                         if(((mouse_x >= retour->rect.x) && (mouse_x <= (retour->rect.x + moteur->echelle * (strlen(B_RETOUR)/2.5))))&&((mouse_y >= retour->rect.y) && mouse_y <= (retour->rect.y + moteur->echelle * 2)))
                        return 7;
                        break;
                    default:return -1;break;
                };
                break;
        case SDL_MOUSEMOTION :

            if(((mouse_x >= haut->rect.x) && (mouse_x <= (haut->rect.x + moteur->echelle * (strlen(B_UP)/2.5))))&&((mouse_y >= haut->rect.y) && (mouse_y <= (haut->rect.y + moteur->echelle * 2))))
                SDL_SetTextureColorMod(haut->texture,255,0,0);
            else SDL_SetTextureColorMod(haut->texture,0,0,255);

            if(((mouse_x >= bas->rect.x) && (mouse_x <= (bas->rect.x + moteur->echelle * (strlen(B_DOWN)/2.5))))&&((mouse_y >= bas->rect.y) && (mouse_y <= (bas->rect.y + moteur->echelle * 2))))
                SDL_SetTextureColorMod(bas->texture,255,0,0);
            else SDL_SetTextureColorMod(bas->texture,0,0,255);

            if(((mouse_x >= droite->rect.x) && (mouse_x <= (droite->rect.x + moteur->echelle * (strlen(B_RIGHT)/2.5))))&&((mouse_y >= droite->rect.y) && (mouse_y <= (droite->rect.y + moteur->echelle * 2))))
                SDL_SetTextureColorMod(droite->texture,255,0,0);
            else SDL_SetTextureColorMod(droite->texture,0,0,255);

            if(((mouse_x >= gauche->rect.x) && (mouse_x <= (gauche->rect.x + moteur->echelle * (strlen(B_LEFT)/2.5))))&&((mouse_y >= gauche->rect.y) && (mouse_y <= (gauche->rect.y + moteur->echelle * 2))))
                SDL_SetTextureColorMod(gauche->texture,255,0,0);
            else SDL_SetTextureColorMod(gauche->texture,0,0,255);

            if(((mouse_x >= projectile->rect.x) && (mouse_x <= (projectile->rect.x + moteur->echelle * (strlen(B_PROJECTILE)/2.5))))&&((mouse_y >= projectile->rect.y) && (mouse_y <= (projectile->rect.y + moteur->echelle * 2))))
                SDL_SetTextureColorMod(projectile->texture,255,0,0);
            else SDL_SetTextureColorMod(projectile->texture,0,0,255);

            if(((mouse_x >= retour->rect.x) && (mouse_x <= (retour->rect.x + moteur->echelle * (strlen(B_RETOUR)/2.5))))&&((mouse_y >= retour->rect.y) && (mouse_y <= (retour->rect.y + moteur->echelle * 2))))
                SDL_SetTextureColorMod(retour->texture,255,0,0);
            else SDL_SetTextureColorMod(retour->texture,0,0,255);

        break;
        }
    }
    return 0;
}


/**
 * \brief Charge tout les boutons / fonctionnalités du sous menu pour les keymap
 * 
 * \param moteur structure moteur
 * \return int 0 si succes, negatif si echec
 */
int charger_menuOptions_keymap(t_moteur * moteur){

    int temp = 0;

    t_bouton * haut = NULL;
    t_bouton * bas = NULL;
    t_bouton * droite = NULL;
    t_bouton * gauche = NULL;
    t_bouton * projectile = NULL;
    t_bouton * retour = NULL;

    haut = initialiserBouton(moteur,B_UP);
    bas = initialiserBouton(moteur,B_DOWN);
    droite = initialiserBouton(moteur,B_RIGHT);
    gauche = initialiserBouton(moteur,B_LEFT);
    projectile = initialiserBouton(moteur,B_PROJECTILE);
    retour = initialiserBouton(moteur,B_RETOUR);


    while(temp==0){
        if(SDL_SetRenderDrawColor(moteur->renderer,0,0,0,255) !=0){
            printf("Erreur lors du SDL_SetRenderDrawColor dans le menu_options_keymap");
            return -1;
        }
        if(SDL_RenderClear(moteur->renderer)!=0){
            printf("Erreur lors du SDL_RenderClear dans le menu_options_keymap");
            return -1;
        }

        if(update_texture(moteur,haut,moteur->window_width /5 ,moteur->window_height *0.1, B_DOWN ) != 0){
            printf("Erreur lors de la mise a jour des textures pour le bouton \"haut\" dans le menu_options_keymap\n");
            return -1;
        }

        if(update_texture(moteur,bas,moteur->window_width /5 ,moteur->window_height *0.4, B_UP) != 0){
            printf("Erreur lors de la mise a jour des textures pour le bouton \"bas\" dans le menu_options_keymap\n");
            return -1;
        }

        if(update_texture(moteur,droite,moteur->window_width /5 ,moteur->window_height *0.7, B_RIGHT ) != 0){
            printf("Erreur lors de la mise a jour des textures pour le bouton \"droite\" dans le menu_options_keymap\n");
            return -1;
        }

        if(update_texture(moteur,gauche,moteur->window_width /2 ,moteur->window_height *0.1, B_LEFT) != 0){
            printf("Erreur lors de la mise a jour des textures pour le bouton \"gauche\" dans le menu_options_keymap\n");
            return -1;
        }

        if(update_texture(moteur,projectile,moteur->window_width /2 ,moteur->window_height *0.4, B_PROJECTILE) != 0){
            printf("Erreur lors de la mise a jour des textures pour le bouton \"projectile\" dans le menu_options_keymap\n");
            return -1;
        }

        if(update_texture(moteur,retour,moteur->window_width /2 ,moteur->window_height *0.7,B_RETOUR) != 0){
            printf("Erreur lors de la mise a jour des textures pour le bouton \"Retour\" dans le menu_options_keymap\n");
            return -1;
        }
        updateEchelle(moteur);
        SDL_RenderPresent(moteur->renderer);

        temp = handleEvents_options_keymap(moteur,haut,bas,droite,gauche,projectile,retour);

        switch(temp){
            case 0 : break;
            case 1 : 
            case -1 : {
                printf("Erreur (default)\n");
                detruireBouton(&haut);
                detruireBouton(&bas);
                detruireBouton(&droite);
                detruireBouton(&gauche);
                detruireBouton(&projectile);
                detruireBouton(&retour);
                return -1;
            }
            case 7 : {
                printf("Retour\n");
                detruireBouton(&haut);
                detruireBouton(&bas);
                detruireBouton(&droite);
                detruireBouton(&gauche);
                detruireBouton(&projectile);
                detruireBouton(&retour);
                charger_menuOptions(moteur);
                break;
            }
            case 2 : printf("Map up\n");temp = 0;break;
            case 3 : printf("Map down\n");temp = 0;break;
            case 4 : printf("Map right\n");temp = 0;break;
            case 5 : printf("Map left\n");temp = 0;break;
            case 6 : printf("Map projectile\n");temp = 0;break;
            default :{
                printf("Erreur, menu inconnu\n");
                detruireBouton(&haut);
                detruireBouton(&bas);
                detruireBouton(&droite);
                detruireBouton(&gauche);
                detruireBouton(&projectile);
                detruireBouton(&retour);
                return -1;
            }
        }

    }

    return 0;


}

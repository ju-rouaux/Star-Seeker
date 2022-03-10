/**
 * \file menu.c
 * \author Guillaume
 * \brief Sous menu, volume et acces au menu pour le mapping des touches
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <window.h>
#include <moteur.h>
#include <menu.h>


/**
 * \brief Fonction d'appel pour la mise a jour des differentes textures
 * 
 * \param moteur moteur du jeu
 * \param boutons tableau de bouton
 * \return 0 si succès; negatif si echec
 */
static int update_MenuOptions(t_moteur * moteur, t_bouton ** boutons){
        if(SDL_SetRenderDrawColor(moteur->renderer,0,0,0,255) !=0){
            printf("Erreur lors du SDL_SetRenderDrawColor dans le menu options\n");
            return -1;
        }
        if(SDL_RenderClear(moteur->renderer)!=0){
            printf("Erreur lors du SDL_RenderClear dans le menu options\n");
            return -1;
        }
        if(update_texture(moteur,boutons[0],moteur->window_width /4 ,moteur->window_height *0.15) != 0){
            printf("Erreur lors de la mise a jour des textures pour le bouton \"Volume\" dans le menu options\n");
            return -1;
        }
        if(update_texture(moteur,boutons[1],moteur->window_width /4 ,moteur->window_height *0.42) != 0){
            printf("Erreur lors de la mise a jour des textures pour le bouton \"Keymap\" dans le menu options\n");
            return -1;
        }
        if(update_texture(moteur,boutons[2],moteur->window_width /4 ,moteur->window_height *0.7) != 0){
            printf("Erreur lors de la mise a jour des textures pour le bouton \"Retour\" dans le menu options\n");
            return -1;
        }
        updateEchelle(moteur);
        SDL_RenderPresent(moteur->renderer);

    return 0;
}

/**
 * \brief Gere les evenements dans le sous menu options
 *
 * \param moteur structure du moteur
 * \param boutons tableau de boutons
 * \return int 0 si succes, 1 si l'utilisateur ferme la fenetre, autre chiffre positif selon le bouton appuyé 
 */
static int handleEvents_options(t_moteur * moteur, t_bouton ** boutons){

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
                        for(int i = 0; i < NB_B_MENU_OPTIONS ; i++){
                            if(((mouse_x >= boutons[i]->rect.x) && (mouse_x <= (boutons[i]->rect.x  + moteur->echelle * (boutons[i]->longueur/2.5))))&&((mouse_y >= boutons[i]->rect.y) && (mouse_y <= (boutons[i]->rect.y + moteur->echelle * 2))))
                                return i + 2;
                        }
                        break;
                    default:return -1;break;
                };
                break;
        case SDL_MOUSEMOTION :

            for(int  i = 0; i < NB_B_MENU_OPTIONS ; i++){
                if(((mouse_x >= boutons[i]->rect.x) && (mouse_x <= (boutons[i]->rect.x  + moteur->echelle * (boutons[i]->longueur/2.5))))&&((mouse_y >= boutons[i]->rect.y) && (mouse_y <= (boutons[i]->rect.y + moteur->echelle * 2))))
                    SDL_SetTextureColorMod(boutons[i]->texture,255,0,0);
                else SDL_SetTextureColorMod(boutons[i]->texture,0,0,255);
            }

        break;
        }
    }
    return 0;
}


/**
 * \brief Charge le sous menu des options
 *
 * \param moteur moteur
 * \return int 0 si succès, 1 si echec
 */
int chargerMenu_Options(t_moteur * moteur){

    t_bouton ** boutons = NULL;
    char noms_boutons[NB_B_MENU_OPTIONS][TAILLE_MAX] = NOMS_B_MENU_OPTIONS;

    boutons = initialiserBoutons(moteur,NB_B_MENU_OPTIONS,noms_boutons);

    if(boutons == NULL){
        printf("Erreur allocation memoire boutons options\n");
        return -1;
    }

    int temp = 0;

    while(temp==0){

        if(update_MenuOptions(moteur,boutons)!=0){
            printf("Erreur lors de l'update dans le menu options");
            return -1;
        }

        temp = handleEvents_options(moteur,boutons);


        switch(temp){
            case 0 : break;
            case 1 :
            case -1 : {
                printf("Erreur (default)");
                detruireBoutons(&boutons,NB_B_MENU_OPTIONS);
                return -1;
            }
            case 2 : {
                printf("Muet (on/off)\n");
                temp = 0;
                break;
            }
            case 3 : {
                printf("Keymap\n");
                detruireBoutons(&boutons,NB_B_MENU_OPTIONS);
                chargerMenu_Options_keymap(moteur);
                break;
            }
            case 4 :{
                printf("Retour\n");
                detruireBoutons(&boutons,NB_B_MENU_OPTIONS);
                chargerMenu(moteur);
                break;
            }
            default :{
                printf("Erreur, menu inconnu");
                detruireBoutons(&boutons,NB_B_MENU_OPTIONS);
                return -1;
            }
        }
    }
    detruireBoutons(&boutons,NB_B_MENU_OPTIONS);
    return 0;
}

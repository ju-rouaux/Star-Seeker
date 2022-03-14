/**
 * \file menu_options_keymap.c
 * \author Guillaume
 * \brief Sous menu pour le mapping des touches
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
 * \brief Gere tout les evenements liées au boutons danns le sous menu keymap
 * 
 * \param moteur structure moteur
 * \param boutons tableau de boutons des options
 * \return 0 si succes, 1 si l'utilisateur ferme la fenetre, autre chiffre positif selon le bouton appuyé
 */
static int handleEvents_options_keymap(t_moteur * moteur, t_bouton ** boutons,SDL_Scancode * key) {

    int mouse_x, mouse_y;
    SDL_Event e;

    while (SDL_PollEvent( & e)) {
        mouse_x = e.button.x, mouse_y = e.button.y;
        switch (e.type) {

        case SDL_QUIT:
            return 1;

        case SDL_MOUSEBUTTONDOWN:
            /**Si un des boutons de la souris est relaché*/
            switch (e.button.button) {
            case SDL_BUTTON_LEFT:
                /**Bouton gauche*/

                for (int i = 0; i < NB_B_MENU_OPTIONS_KEYMAP; i++) {
                    if (i != NB_B_MENU_OPTIONS_KEYMAP - 1) { // Cas particulier pour le bouton retour
                        if (((mouse_x >= boutons[i] -> rect.x) && (mouse_x <= (boutons[i] -> rect.x + moteur -> echelle * (boutons[i] -> longueur / B_LARGEUR)))) && ((mouse_y >= boutons[i] -> rect.y) && (mouse_y <= (boutons[i] -> rect.y + moteur -> echelle * B_LONGUEUR)))) {
                            while (SDL_WaitEvent( & e) && e.type != SDL_KEYDOWN) {
                                *key = e.key.keysym.scancode;
                                maj_TextureMenu(moteur, boutons, NB_B_MENU_OPTIONS_KEYMAP);//mise a jour des textures 
                            }
                            SDL_SetTextureColorMod(boutons[i] -> texture, 8, 125, 0);
                            return (i + 2);
                        }
                    } else return i + 2;
                }
                break;
            default:
                return -1;
                break;
            };
            break;

        case SDL_MOUSEMOTION:
            for (int i = 0; i < NB_B_MENU_OPTIONS_KEYMAP; i++) {
                if (((mouse_x >= boutons[i] -> rect.x) && (mouse_x <= (boutons[i] -> rect.x + moteur -> echelle * (boutons[i] -> longueur / B_LARGEUR)))) && ((mouse_y >= boutons[i] -> rect.y) && (mouse_y <= (boutons[i] -> rect.y + moteur -> echelle * B_LONGUEUR))))
                    SDL_SetTextureColorMod(boutons[i] -> texture, 255, 0, 0);
                else SDL_SetTextureColorMod(boutons[i] -> texture, 0, 0, 255);
            }
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
int chargerMenu_Options_keymap(t_moteur * moteur) {
    
    SDL_Scancode key;

    t_bouton ** boutons = NULL;

    char nom_boutons[NB_B_MENU_OPTIONS_KEYMAP][TAILLE_MAX] = NOMS_B_MENU_OPTIONS_KEYMAP;

    boutons = initialiserBoutons(moteur, NB_B_MENU_OPTIONS_KEYMAP, nom_boutons);

    if (boutons == NULL) {
        printf("Erreur allocation memoire boutons\n");
        return -1;
    }

    SDL_Texture * texture_titre = NULL;
    SDL_Rect * rect_titre = NULL;
    rect_titre = initialiserTexte(moteur,&texture_titre,"Star Seeker");

    if(rect_titre == NULL){
        printf("Erreur allocation Texte titre\n");
        return -1;
    }

    int temp = 0;

    while (temp == 0) {
        if (SDL_RenderClear(moteur -> renderer) != 0) {
            printf("Erreur lors du SDL_RenderClear dans le menu");
            return -1;//Retourne cas d'erreur
        }
        if (maj_TextureMenu(moteur, boutons, NB_B_MENU_OPTIONS_KEYMAP) != 0 ) {
            printf("Erreur lors de l'update dans le menu principal");
            return -1;
        }
        if (maj_TextureTexte(moteur, rect_titre,&texture_titre,180,30,"Star Seeker") != 0) {
            printf("Erreur lors de l'update dans le menu principal");
            return -1;
        }

        temp = handleEvents_options_keymap(moteur, boutons, &key);

        switch (temp) {
            case 0:
                break;
            case 1:
            case -1: {
                printf("Erreur (default)\n");
                detruireBoutons( & boutons, NB_B_MENU_OPTIONS_KEYMAP);
                detruireTexte(&rect_titre,texture_titre);
                return -1;
            }
            case 2:
                printf("Map up\n");
                printf("Key mapped for up : %d\n",key);
                temp = 0;//pour rester sur le menu actuel
                break;
            case 3:
                printf("Map down\n");
                printf("Key mapped for down : %d\n",key);
                temp = 0;//pour rester sur le menu actuel
                break;
            case 4:
                printf("Map right\n");
                printf("Key mapped for right : %d\n",key);
                temp = 0;//pour rester sur le menu actuel
                break;
            case 5:
                printf("Map left\n");
                printf("Key mapped for left : %d\n",key);
                temp = 0;//pour rester sur le menu actuel
                break;
            case 6:
                printf("Map projectile\n");
                printf("Key mapped for projectile : %d\n",key);
                temp = 0;//pour rester sur le menu actuel
                break;
            case 7: {
                printf("Retour\n");
                detruireBoutons( & boutons, NB_B_MENU_OPTIONS_KEYMAP);
                detruireTexte(&rect_titre,texture_titre);
                chargerMenu_Options(moteur);
                break;
            }
            default: {
                printf("Erreur, menu inconnu\n");
                detruireBoutons( & boutons, NB_B_MENU_OPTIONS_KEYMAP);
                detruireTexte(&rect_titre,texture_titre);
                return -1;
            }
        }
    updateEchelle(moteur);//on met a jour l'echelle
    SDL_RenderPresent(moteur -> renderer);
    }
    return 0;
}
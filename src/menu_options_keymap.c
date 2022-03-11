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
static int handleEvents_options_keymap(t_moteur * moteur, t_bouton ** boutons) {

    int mouse_x, mouse_y;
    SDL_Event e;
    SDL_Scancode key;

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
                        if (((mouse_x >= boutons[i] -> rect.x) && (mouse_x <= (boutons[i] -> rect.x + moteur -> echelle * (boutons[i] -> longueur / 2.5)))) && ((mouse_y >= boutons[i] -> rect.y) && (mouse_y <= (boutons[i] -> rect.y + moteur -> echelle * 2)))) {
                            while (SDL_WaitEvent( & e) && e.type != SDL_KEYDOWN) {
                                key = e.key.keysym.scancode;
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
                if (((mouse_x >= boutons[i] -> rect.x) && (mouse_x <= (boutons[i] -> rect.x + moteur -> echelle * (boutons[i] -> longueur / 2.5)))) && ((mouse_y >= boutons[i] -> rect.y) && (mouse_y <= (boutons[i] -> rect.y + moteur -> echelle * 2))))
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

    t_bouton ** boutons = NULL;//tableau de bouton
    char nom_boutons[NB_B_MENU_OPTIONS_KEYMAP][TAILLE_MAX] = NOMS_B_MENU_OPTIONS_KEYMAP;

    boutons = initialiserBoutons(moteur, NB_B_MENU_OPTIONS_KEYMAP, nom_boutons);//initialisation du tableau de boutons et allocation de la memoire necessaire

    if (boutons == NULL) {
        printf("Erreur allocation memoire boutons menu keymap\n");
        return -1;
    }

    int temp = 0;

    while (temp == 0) {

        if (maj_TextureMenu(moteur, boutons, NB_B_MENU_OPTIONS_KEYMAP) != 0) {//mise a jour des textures 
            printf("Erreur lors de l'update dans le menu options keymap");
            return -1;
        }

        temp = handleEvents_options_keymap(moteur, boutons);

        switch (temp) {
        case 0:
            break;
        case 1:
        case -1: {
            printf("Erreur (default)\n");
            detruireBoutons( & boutons, NB_B_MENU_OPTIONS_KEYMAP);
            return -1;
        }
        case 2:
            printf("Map up\n");
            temp = 0;//pour rester sur le menu actuel
            break;
        case 3:
            printf("Map down\n");
            temp = 0;//pour rester sur le menu actuel
            break;
        case 4:
            printf("Map right\n");
            temp = 0;//pour rester sur le menu actuel
            break;
        case 5:
            printf("Map left\n");
            temp = 0;//pour rester sur le menu actuel
            break;
        case 6:
            printf("Map projectile\n");
            temp = 0;//pour rester sur le menu actuel
            break;
        case 7: {
            printf("Retour\n");
            detruireBoutons( & boutons, NB_B_MENU_OPTIONS_KEYMAP);
            chargerMenu_Options(moteur);
            break;
        }
        default: {
            printf("Erreur, menu inconnu\n");
            detruireBoutons( & boutons, NB_B_MENU_OPTIONS_KEYMAP);
            return -1;
        }
        }
    }
    return 0;
}
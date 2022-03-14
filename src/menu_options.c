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
 * \brief Gere les evenements dans le sous menu options
 *
 * \param moteur structure du moteur
 * \param boutons tableau de boutons
 * \return int 0 si succes, 1 si l'utilisateur ferme la fenetre, autre chiffre positif selon le bouton appuyé 
 */
static int handleEvents_options(t_moteur * moteur, t_bouton ** boutons) {

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
                for (int i = 0; i < NB_B_MENU_OPTIONS; i++) {
                    if (((mouse_x >= boutons[i] -> rect.x) && (mouse_x <= (boutons[i] -> rect.x + moteur -> echelle * (boutons[i] -> longueur / B_LARGEUR)))) && ((mouse_y >= boutons[i] -> rect.y) && (mouse_y <= (boutons[i] -> rect.y + moteur -> echelle * B_LONGUEUR))))
                        return i + 2;
                }
                break;
            default:
                return -1;
                break;
            };
            break;
        case SDL_MOUSEMOTION:

            for (int i = 0; i < NB_B_MENU_OPTIONS; i++) {
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
 * \brief Charge le sous menu des options
 *
 * \param moteur moteur
 * \return int 0 si succès, 1 si echec
 */
int chargerMenu_Options(t_moteur * moteur) {

    t_bouton ** boutons = NULL; //tableau de bouton
    char noms_boutons[NB_B_MENU_OPTIONS][TAILLE_MAX] = NOMS_B_MENU_OPTIONS;

    boutons = initialiserBoutons(moteur, NB_B_MENU_OPTIONS, noms_boutons); //initialisation du tableau de boutons et allocation de la memoire necessaire

    if (boutons == NULL) {
        printf("Erreur allocation memoire boutons options\n");
        return -1;
    }

    int temp = 0;

    while (temp == 0) {

        if (maj_TextureMenu(moteur, boutons, NB_B_MENU_OPTIONS) != 0) {//mise a jour des textures 
            printf("Erreur lors de l'update dans le menu options");
            return -1;
        }

        temp = handleEvents_options(moteur, boutons);

        switch (temp) {//Selon le resultat de l'event
        case 0: //pour rester sur le menu actuel (on ne fait rien)
            break;
        case 1:
        case -1: {
            printf("Erreur (default)");
            detruireBoutons( & boutons, NB_B_MENU_OPTIONS);
            return -1;
        }
        case 2: {
            printf("Muet (on/off)\n");
            temp = 0;//pour rester sur le menu actuel
            break;
        }
        case 3: {
            printf("Keymap\n");
            detruireBoutons( & boutons, NB_B_MENU_OPTIONS);
            chargerMenu_Options_keymap(moteur);
            break;
        }
        case 4: {
            printf("Retour\n");
            detruireBoutons( & boutons, NB_B_MENU_OPTIONS);
            chargerMenu(moteur);
            break;
        }
        default: {
            printf("Erreur, menu inconnu");
            detruireBoutons( & boutons, NB_B_MENU_OPTIONS);
            return -1;
        }
        }
    }
    detruireBoutons( & boutons, NB_B_MENU_OPTIONS);
    return 0;
}
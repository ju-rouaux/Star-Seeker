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

    t_bouton ** boutons = NULL;

    char nom_boutons[NB_B_MENU_OPTIONS][TAILLE_MAX] = NOMS_B_MENU_OPTIONS;

    boutons = initialiserBoutons(moteur, NB_B_MENU_OPTIONS, nom_boutons);

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
        if (maj_TextureMenu(moteur, boutons, NB_B_MENU_OPTIONS) != 0 ) {
            printf("Erreur lors de l'update dans le menu principal");
            return -1;
        }
        if (maj_TextureTexte(moteur, rect_titre,&texture_titre,180,30,"Star Seeker") != 0) {
            printf("Erreur lors de l'update dans le menu principal");
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
            detruireTexte(&rect_titre,texture_titre);
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
            detruireTexte(&rect_titre,texture_titre);
            chargerMenu_Options_keymap(moteur);
            break;
        }
        case 4: {
            printf("Retour\n");
            detruireBoutons( & boutons, NB_B_MENU_OPTIONS);
            detruireTexte(&rect_titre,texture_titre);
            chargerMenu(moteur);
            break;
        }
        default: {
            printf("Erreur, menu inconnu");
            detruireBoutons( & boutons, NB_B_MENU_OPTIONS);
            detruireTexte(&rect_titre,texture_titre);
            return -1;
        }
        }
         updateEchelle(moteur);//on met a jour l'echelle
        SDL_RenderPresent(moteur -> renderer);
    }
    return 0;
}
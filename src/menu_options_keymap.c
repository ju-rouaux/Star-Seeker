/**
 * \file menu_options_keymap.c
 * \author Guillaume
 * \brief Sous menu pour le mapping des touches
 * 
 */

#include <menu_options_keymap.h>


/**
 * \brief Gere tout les evenements liées au boutons danns le sous menu keymap
 * 
 * \param moteur structure moteur
 * \param boutons tableau de boutons des options
 * \return 0 si succes, 1 si l'utilisateur ferme la fenetre, autre chiffre positif selon le bouton appuyé
 */
static int handleEvents_options_keymap(t_moteur * moteur, t_bouton ** boutons,SDL_Scancode * key_code) {

    SDL_Point mouse;
    SDL_Event e;

    while (SDL_PollEvent( & e)) {
        mouse.x = e.button.x;
        mouse.y = e.button.y;
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
                        if (SDL_PointInRect(&mouse,&boutons[i]->rect)) {
                            while (SDL_WaitEvent( &e) && e.type != SDL_KEYUP ) {
                                if(e.type == SDL_KEYDOWN)
                                    *key_code = e.key.keysym.scancode; //on recupere la valeur de la touche appuyée
                                maj_TextureMenu(moteur, boutons, NB_B_MENU_OPTIONS_KEYMAP);//mise a jour des textures 
                            }
                            SDL_SetTextureColorMod(boutons[i] -> texture, 8, 125, 0);//On definit le bouton en vert
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
                if (SDL_PointInRect(&mouse,&boutons[i]->rect))
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
 * \return code de sortie personnalisé selon l'evenement
 */
e_menu chargerMenu_Options_keymap(t_moteur * moteur) {
    
    SDL_Scancode key_temp = -1;

    t_bouton ** boutons = NULL;

    char nom_boutons[NB_B_MENU_OPTIONS_KEYMAP][TAILLE_MAX] = NOMS_B_MENU_OPTIONS_KEYMAP;

    boutons = initialiserBoutons(moteur, NB_B_MENU_OPTIONS_KEYMAP, nom_boutons);

    if (boutons == NULL) {
        printf("Erreur allocation memoire boutons\n");
        return ERROR_MENU;
    }

    SDL_Texture * texture_titre = NULL;
    SDL_Rect * rect_titre = NULL;
    rect_titre = initialiserTexte(moteur,&texture_titre,"Star Seeker");

    if(rect_titre == NULL){
        printf("Erreur allocation Texte titre\n");
        return ERROR_MENU;
    }

    int temp = 0;

    while (temp == 0) {
        if (SDL_RenderClear(moteur -> renderer) != 0) {
            printf("Erreur lors du SDL_RenderClear dans le menu");
            return ERROR_MENU_TEXTURE;//Retourne cas d'erreur
        }
        if (maj_TextureMenu(moteur, boutons, NB_B_MENU_OPTIONS_KEYMAP) != 0 ) {
            // printf("Erreur lors de l'update dans le menu principal");
            return ERROR_MENU_TEXTURE;
        }
        if (maj_TextureTexte(moteur, rect_titre,&texture_titre,180,30,"Star Seeker") != 0) {
            // printf("Erreur lors de l'update dans le menu principal");
            return ERROR_MENU_TEXTURE;
        }

        temp = handleEvents_options_keymap(moteur, boutons, &key_temp);

        switch (temp) {
            case 0:
                break;
            case 1:
            case -1: {
                printf("Erreur (default)\n");
                detruireBoutons( & boutons, NB_B_MENU_OPTIONS_KEYMAP);
                detruireTexte(&rect_titre,texture_titre);
                return ERROR_MENU;
            }
            case 2:
                printf("Key mapped for up : %d\n",key_temp);
                moteur->parametres.key_up = key_temp;
                temp = 0;//pour rester sur le menu actuel
                break;
            case 3:
                printf("Key mapped down : %d\n",moteur->parametres.key_down);
                moteur->parametres.key_down = key_temp;
                temp = 0;//pour rester sur le menu actuel
                break;
            case 4:
                printf("Key mapped for right : %d\n",key_temp);
                moteur->parametres.key_right = key_temp;
                temp = 0;//pour rester sur le menu actuel
                break;
            case 5:
                printf("Key mapped for left : %d\n",key_temp);
                moteur->parametres.key_left = key_temp;
                temp = 0;//pour rester sur le menu actuel
                break;
            case 6:
                printf("Key mapped for projectile : %d\n",key_temp);
                moteur->parametres.key_projectile = key_temp;
                temp = 0;//pour rester sur le menu actuel
                break;
            case 7: {
                printf("Retour\n");
                detruireBoutons( & boutons, NB_B_MENU_OPTIONS_KEYMAP);
                detruireTexte(&rect_titre,texture_titre);
                return M_OPTIONS;
                break;
            }
            default: {
                printf("Erreur, menu inconnu\n");
                detruireBoutons( & boutons, NB_B_MENU_OPTIONS_KEYMAP);
                detruireTexte(&rect_titre,texture_titre);
                return ERROR_MENU;
            }
        }
    updateEchelle(moteur);//on met a jour l'echelle
    SDL_RenderPresent(moteur -> renderer);
    }
    return M_OPTIONS;
}
/**
 * \file menu_options_keymap.c
 * \author Guillaume Richard
 * \brief Sous menu pour le mapping des touches
 * Permet au joueur de redéfinir ses touches
 * 
 */

#include <menu_options_keymap.h>


/**
 * \brief Gere tout les evenements liées au boutons danns le sous menu keymap
 * 
 * \param moteur le moteur
 * \param boutons le tableau de boutons
 * \return 0 si succes, 1 si l'utilisateur ferme la fenetre, autre chiffre positif selon le bouton appuyé
 */
static int handleEvents_options_keymap(t_moteur * moteur, t_bouton ** boutons,SDL_Scancode * key_code) {

    SDL_Point mouse;
    SDL_Event e;

    while (SDL_PollEvent( & e)) {
        //Position du curseur de la souris
        mouse.x = e.button.x;
        mouse.y = e.button.y;
        switch (e.type) {
            case SDL_QUIT: //si le joueur ferme la fenetre avec la croix
                return 1;
            case SDL_MOUSEBUTTONDOWN:
                /**Si un des boutons de la souris est relaché*/
                switch (e.button.button) {
                case SDL_BUTTON_LEFT:
                    /**Bouton gauche*/
                    for (int i = 0; i < NB_B_MENU_OPTIONS_KEYMAP; i++) { // parcours du tableau de boutons
                        if (i != NB_B_MENU_OPTIONS_KEYMAP - 1) { // Cas particulier pour le bouton retour
                            if (SDL_PointInRect(&mouse,&boutons[i]->rect)) {
                                while (SDL_WaitEvent(&e) && e.type != SDL_KEYUP ) {//On attend une interaction avec le clavier
                                    if(e.type == SDL_KEYDOWN)
                                        *key_code = e.key.keysym.scancode; //on recupere la valeur de la touche appuyée
                                    maj_TextureMenu(moteur, boutons, NB_B_MENU_OPTIONS_KEYMAP);//mise a jour des textures
                                }
                                if(e.type == SDL_KEYUP)
                                    SDL_SetTextureColorMod(boutons[i] -> texture, 0, 0, 255);// On remet la couleur d'origine
                                return (i + 2);
                            }
                        } else return i + 2;
                    }
                    break;
                default:
                    break;
                };
                break;

            case SDL_MOUSEMOTION:
                for (int i = 0; i < NB_B_MENU_OPTIONS_KEYMAP - 1; i++) {
                    //Changement de la couleur du bouton quand la souris passe dessus
                    if (SDL_PointInRect(&mouse,&boutons[i]->rect))
                        SDL_SetTextureColorMod(boutons[i] -> texture, 125, 255, 0);//vert
                    else SDL_SetTextureColorMod(boutons[i] -> texture, 0, 0, 255);//Bleu
                }
                if (SDL_PointInRect(&mouse,&boutons[NB_B_MENU_OPTIONS_KEYMAP - 1]->rect))//couleur pour le bouton retour
                        SDL_SetTextureColorMod(boutons[NB_B_MENU_OPTIONS_KEYMAP -1] -> texture, 255, 0, 0);
                    else SDL_SetTextureColorMod(boutons[NB_B_MENU_OPTIONS_KEYMAP - 1] -> texture, 0, 0, 255);
                break;
        }
    }
    return 0;
}

/**
 * \brief Charge tous les boutons / fonctionnalités du sous menu pour les keymap
 * 
 * \param moteur le moteur
 * \return code de sortie personnalisé selon l'évenement
 */
e_code_main chargerMenu_Options_keymap(t_moteur * moteur) {

    SDL_Scancode key_temp = -1;
    t_bouton ** boutons = NULL;
    char nom_boutons[NB_B_MENU_OPTIONS_KEYMAP][TAILLE_MAX] = NOMS_B_MENU_OPTIONS_KEYMAP;
    boutons = initialiserBoutons(moteur, NB_B_MENU_OPTIONS_KEYMAP, nom_boutons);

    if (boutons == NULL) {
        printf("Erreur allocation memoire boutons\n");
        return ERROR_MENU;
    }

    SDL_Rect * rect_titre = NULL;
    SDL_Texture * texture_titre = NULL;
    rect_titre = initialiserTexte(moteur,&texture_titre,"Star Seeker");

    if(rect_titre == NULL){
        printf("Erreur allocation Texte titre\n");
        return ERROR_MENU;
    }

    int temp = 0;

    while (temp == 0) {
        regulerFPS(moteur);//On limite les fps
        if (SDL_RenderClear(moteur -> renderer) != 0) {
            printf("Erreur lors du SDL_RenderClear dans le menu Keymap\n");
            return ERROR_MENU_TEXTURE;//Retourne cas d'erreur
        }

        if (maj_TextureMenu(moteur, boutons, NB_B_MENU_OPTIONS_KEYMAP) != 0 ) {
            printf("Erreur lors de l'update dans le menu Keymap\n");
            return ERROR_MENU_TEXTURE;
        }

        if (maj_TextureTexte(moteur, rect_titre,&texture_titre,180,30,"Star Seeker") != 0) {
            printf("Erreur lors de l'update dans le menu Keymap\n");
            return ERROR_MENU_TEXTURE;
        }

        temp = handleEvents_options_keymap(moteur, boutons, &key_temp);

        switch (temp) { //Selon l'évenement
            case 0:
                break;
            case 1:
            case -1:
                printf("Erreur (default)\n");
                detruireBoutons( & boutons, NB_B_MENU_OPTIONS_KEYMAP);
                detruireTexte(&rect_titre,texture_titre);
                return ERROR_MENU;
            case 2:
                printf("Touche du haut reparamétrée : %d\n",key_temp);
                moteur->parametres.key_up = key_temp;
                temp = 0;//pour rester sur le menu actuel
                break;
            case 3:
                printf("Touche du bas reparamétrée : %d\n",moteur->parametres.key_down);
                moteur->parametres.key_down = key_temp;
                temp = 0;//pour rester sur le menu actuel
                break;
            case 4:
                printf("Touche de droite reparamétrée : %d\n",key_temp);
                moteur->parametres.key_right = key_temp;
                temp = 0;//pour rester sur le menu actuel
                break;
            case 5:
                printf("Touche de gauche reparamétrée : %d\n",key_temp);
                moteur->parametres.key_left = key_temp;
                temp = 0;//pour rester sur le menu actuel
                break;
            case 6:
                printf("Touche de l'interaction reparamétrée : %d\n",key_temp);
                moteur->parametres.key_interaction = key_temp;
                temp = 0;//pour rester sur le menu actuel
                break;
            case 7:
                printf("Touche de l'attaque du haut reparamétrée : %d\n",key_temp);
                moteur->parametres.attack_up = key_temp;
                temp = 0;//pour rester sur le menu actuel
                break;
            case 8:
                printf("Touche de l'attaque du bas reparamétrée : %d\n",key_temp);
                moteur->parametres.attack_down = key_temp;
                temp = 0;//pour rester sur le menu actuel
                break;
            case 9 :
                printf("Touche de l'attaque de droite reparamétrée : %d\n",key_temp);
                moteur->parametres.attack_right = key_temp;
                temp = 0;//pour rester sur le menu actuel
                break;
            case 10 :
                printf("Touche de l'attaque de gauche reparamétrée : %d\n",key_temp);
                moteur->parametres.attack_left = key_temp;
                temp = 0;//pour rester sur le menu actuel
                break;
            case 11:
                printf("Touche du dash reparamétrée : %d\n",key_temp);
                moteur->parametres.dash = key_temp;
                temp = 0;//pour rester sur le menu actuel
                break;
            case 12: //Pour retourner au menu des options
                printf("Retour\n");
                detruireBoutons( & boutons, NB_B_MENU_OPTIONS_KEYMAP);
                detruireTexte(&rect_titre,texture_titre);
                return M_OPTIONS;
                break;
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
/**
 * \file menu.c
 * \author Guillaume
 * \brief Sous menu, volume et acces au menu pour le mapping des touches
 * Permet au joueur de choisir s'il veut du son et d'acceder au menu pour reparamétrer ses touches
 * 
 */

#include <menu_options.h>


/**
 * \brief Gere les evenements dans le sous menu options
 *
 * \param moteur le du moteur
 * \param boutons le tableau de boutons
 * \return int 0 si succes, 1 si l'utilisateur ferme la fenetre, autre chiffre positif selon le bouton appuyé 
 */
static int handleEvents_options(t_moteur * moteur, t_bouton ** boutons) {

    SDL_Point mouse;
    SDL_Event e;

    while (SDL_PollEvent( & e)) {
        //position du curseur de la souris
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
                    for (int i = 0; i < NB_B_MENU_OPTIONS; i++) {
                        if (SDL_PointInRect(&mouse,&boutons[i]->rect))
                            return i + 2;
                    }
                    break;
                default:
                    break;
                };
                break;
            case SDL_MOUSEMOTION:
            //Changement de la couleur du bouton quand la souris passe dessus
                for (int i = 0; i < NB_B_MENU_OPTIONS; i++) {
                    if (SDL_PointInRect(&mouse,&boutons[i]->rect))
                        SDL_SetTextureColorMod(boutons[i] -> texture, 255, 0, 0);//Rouge
                    else SDL_SetTextureColorMod(boutons[i] -> texture, 0, 0, 255);//bleu
                }
                break;
        }

        //Pour le bouton du volume
        if(moteur->parametres.volume_audio == SDL_MIX_MAXVOLUME)
            SDL_SetTextureColorMod(boutons[0] -> texture, 125, 255, 0); //Si actif, vert
        else SDL_SetTextureColorMod(boutons[0] -> texture, 255 , 125, 0);//sinon orange
    }
    return 0;
}

/**
 * \brief Charge le sous menu des options
 *
 * \param moteur le moteur
 * \return code de sortie personnalisé selon l'evenement
 */
e_code_main chargerMenu_Options(t_moteur * moteur) {

    t_bouton ** boutons = NULL;
    char nom_boutons[NB_B_MENU_OPTIONS][TAILLE_MAX] = NOMS_B_MENU_OPTIONS;
    boutons = initialiserBoutons(moteur, NB_B_MENU_OPTIONS, nom_boutons);

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
        regulerFPS(moteur);//limitation des images par seconde
        if (SDL_RenderClear(moteur -> renderer) != 0) {
            printf("Erreur lors du SDL_RenderClear dans le menu Options");
            return ERROR_MENU_TEXTURE;//Retourne cas d'erreur
        }

        if (maj_TextureMenu(moteur, boutons, NB_B_MENU_OPTIONS) != 0 ) {
            printf("Erreur lors de l'update dans le menu Options");
            return ERROR_MENU_TEXTURE;
        }

        if (maj_TextureTexte(moteur, rect_titre,&texture_titre,180,30,"Star Seeker") != 0) {
            printf("Erreur lors de l'update dans le menu Options");
            return ERROR_MENU_TEXTURE;
        }

        temp = handleEvents_options(moteur, boutons);

        switch (temp) {//Selon le resultat de l'event
            case 0: //pour rester sur le menu actuel (on ne fait rien)
                break;
            case 2:
                printf("Muet (on/off)\n");
                // Si le volume est activé alors on le desactive, sinon on l'active
                if(moteur->parametres.volume_audio == SDL_MIX_MAXVOLUME){
                    changerVolume(0);
                    moteur->parametres.volume_audio = 0;
                }else{
                    changerVolume(MIX_MAX_VOLUME);
                    moteur->parametres.volume_audio = MIX_MAX_VOLUME;
                }
                temp = 0;//pour rester sur le menu actuel
                break;
            case 3: //Menu pour le keymapping
                printf("Keymap\n");
                detruireBoutons( & boutons, NB_B_MENU_OPTIONS);
                detruireTexte(&rect_titre,texture_titre);
                return M_KEYMAP;
                break;
            case 4: //Menu pour le keymapping
                printf("Crédits\n");
                detruireBoutons( & boutons, NB_B_MENU_OPTIONS);
                detruireTexte(&rect_titre,texture_titre);
                return M_CREDITS;
            case 5: //pour retourner au menu principal
                printf("Retour\n");
                detruireBoutons( & boutons, NB_B_MENU_OPTIONS);
                detruireTexte(&rect_titre,texture_titre);
                return M_PRINCIPAL;
                break;
            default:
                printf("Erreur, menu inconnu");
                detruireBoutons( & boutons, NB_B_MENU_OPTIONS);
                detruireTexte(&rect_titre,texture_titre);
                return ERROR_MENU;
        }
        updateEchelle(moteur);//on met a jour l'echelle
        SDL_RenderPresent(moteur -> renderer);
    }
    return M_PRINCIPAL;
}
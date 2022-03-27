/**
 * \file menu.c
 * \author Guillaume
 * \brief Sous menu, volume et acces au menu pour le mapping des touches
 * 
 */

#include <menu_options.h>


/**
 * \brief Gere les evenements dans le sous menu options
 *
 * \param moteur structure du moteur
 * \param boutons tableau de boutons
 * \return int 0 si succes, 1 si l'utilisateur ferme la fenetre, autre chiffre positif selon le bouton appuyé 
 */
static int handleEvents_options(t_moteur * moteur, t_bouton ** boutons) {

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
                for (int i = 0; i < NB_B_MENU_OPTIONS; i++) {
                    if (SDL_PointInRect(&mouse,&boutons[i]->rect))
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
                if (SDL_PointInRect(&mouse,&boutons[i]->rect))
                    SDL_SetTextureColorMod(boutons[i] -> texture, 255, 0, 0);
                else SDL_SetTextureColorMod(boutons[i] -> texture, 0, 0, 255);
            }

            break;
        }

        //Pour le bouton reset sauvegarde
        if(moteur->parametres.volume_audio == SDL_MIX_MAXVOLUME)
            SDL_SetTextureColorMod(boutons[0] -> texture, 125, 255, 0); //Si actif : rouge
        else SDL_SetTextureColorMod(boutons[0] -> texture, 255 , 125, 0);//sinon reste en bleu
    }
    return 0;
}

/**
 * \brief Charge le sous menu des options
 *
 * \param moteur moteur
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
        regulerFPS(moteur);
        if (SDL_RenderClear(moteur -> renderer) != 0) {
            printf("Erreur lors du SDL_RenderClear dans le menu");
            return ERROR_MENU_TEXTURE;//Retourne cas d'erreur
        }
        if (maj_TextureMenu(moteur, boutons, NB_B_MENU_OPTIONS) != 0 ) {
            printf("Erreur lors de l'update dans le menu principal");
            return ERROR_MENU_TEXTURE;
        }
        if (maj_TextureTexte(moteur, rect_titre,&texture_titre,180,30,"Star Seeker") != 0) {
            printf("Erreur lors de l'update dans le menu principal");
            return ERROR_MENU_TEXTURE;
        }

        temp = handleEvents_options(moteur, boutons);

        switch (temp) {//Selon le resultat de l'event
            case 0: //pour rester sur le menu actuel (on ne fait rien)
                break;
            case 2: {
                printf("Muet (on/off)\n");
                if(moteur->parametres.volume_audio == SDL_MIX_MAXVOLUME){
                    Mix_VolumeMusic(0);
                    moteur->parametres.volume_audio = 0;
                }
                else{
                    Mix_VolumeMusic(MIX_MAX_VOLUME);
                    moteur->parametres.volume_audio = MIX_MAX_VOLUME;
                }
                temp = 0;//pour rester sur le menu actuel
                break;
            }
            case 3: 
                printf("Keymap\n");
                detruireBoutons( & boutons, NB_B_MENU_OPTIONS);
                detruireTexte(&rect_titre,texture_titre);
                return M_KEYMAP;
                break;
            case 4: {
                printf("Retour\n");
                detruireBoutons( & boutons, NB_B_MENU_OPTIONS);
                detruireTexte(&rect_titre,texture_titre);
                return M_PRINCIPAL;
                break;
            }
            default: {
                printf("Erreur, menu inconnu");
                detruireBoutons( & boutons, NB_B_MENU_OPTIONS);
                detruireTexte(&rect_titre,texture_titre);
                return ERROR_MENU;
            }
        }
        updateEchelle(moteur);//on met a jour l'echelle
        SDL_RenderPresent(moteur -> renderer);
    }
    return M_PRINCIPAL;
}
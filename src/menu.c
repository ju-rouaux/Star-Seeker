/**
 * \file menu.c
 * \author Guillaume Richard
 * \brief Menu principal du jeu
 * 
 */

#include <partie.h>
#include <menu.h>


/**
 * \brief Met a jour la texture de chacun des boutons passé en paramètre
 * 
 * \param moteur moteur du jeu
 * \param boutons tableau de boutons
 * \param nb_boutons nombre de boutons
 * \return 0 si succès, negatif si echec 
 */
int maj_TextureMenu(t_moteur * moteur, t_bouton ** boutons, int nb_boutons) {

    if (SDL_SetRenderDrawColor(moteur -> renderer, 0, 0, 0, 255) != 0) {
        printf("Erreur lors du SDL_SetRenderDrawColor dans le menu");
        return -1;//Retourne cas d'erreur
    }

    for (int i = 0; i < nb_boutons; i++) {
        if (nb_boutons > 5 && nb_boutons <= 8) {
            if (i < (nb_boutons / 2)) //On divise par 2 le nombre de boutons pour les mettres sur 2 colonnes et on met la premiere moité sur une premiere colonne
            {                                                                                                      //utiliser pour definir l'espacement entre les boutons
                if (update_textureBouton(moteur, boutons[i], moteur -> window_width / 5, moteur -> window_height * (float)(i + 1.2) / ((nb_boutons + 2.2) / 2)) != 0) {
                    printf("Erreur update texture bouton\n");                                                       //i + cste pour commencer a i !=0 et 
                    return -1;//Retourne cas d'erreur
                }
            } else if (i >= (nb_boutons / 2)){ //on repartie la deuxieme moitié des boutons sur la 2eme colonne
                                                                                                                        //utiliser pour definir l'espacement entre les boutons
                if (update_textureBouton(moteur, boutons[i], moteur -> window_width / 2, moteur -> window_height * (float)(i + 1.2 - (nb_boutons / 2)) / ((nb_boutons + 2.2) / 2)) != 0) {
                    printf("Erreur update texture bouton\n");
                    return -1;//Retourne cas d'erreur
                }
            }
        }else if(nb_boutons > 8){
            if (i < (nb_boutons * 0.33)){ //On divise par 3 le nombre de boutons pour les mettres sur 3 colonnes et on met la premiere moité sur une premiere colonne
                                                                                                                  //utiliser pour definir l'espacement entre les boutons
                if (update_textureBouton(moteur, boutons[i], moteur -> window_width / 8, moteur -> window_height * (float)(i + 1.2) / ((nb_boutons + (nb_boutons /3) + 3) / 3)) != 0) {
                    printf("Erreur update texture bouton\n");                                                       //i + cste pour commencer a i !=0 et 
                    return -1;//Retourne cas d'erreur
                }
            }else if (i >= (nb_boutons * 0.33) && i < (nb_boutons * 0.66)){ //on repartie le deuxieme tiers des boutons sur la 2eme colonne
                                                                                                                        //utiliser pour definir l'espacement entre les boutons
                if (update_textureBouton(moteur, boutons[i], moteur -> window_width / 2.4, moteur -> window_height * (float)(i + 0.8 - (nb_boutons * 0.33)) / ((nb_boutons + 6) / 3)) != 0) {
                    printf("Erreur update texture bouton\n");
                    return -1;//Retourne cas d'erreur
                }
            }else if (i >= (nb_boutons * 0.66)){ //on repartie les derniers boutons sur la 3eme colonne
                                                                                                                        //utiliser pour definir l'espacement entre les boutons
                if (update_textureBouton(moteur, boutons[i], moteur -> window_width / 1.3 , moteur -> window_height * (float)(i + 0.31 - (nb_boutons * (0.66))) / ((nb_boutons + 3) / 3)) != 0) {
                    printf("Erreur update texture bouton\n");
                    return -1;//Retourne cas d'erreur
                }
            }
        }else if (nb_boutons <= 5) //Si il y a peu de bouton, on les mets tous sur une meme colonne
        {                                                                                                       //utiliser pour definir l'espacement entre les boutons
            if (update_textureBouton(moteur, boutons[i], moteur -> window_width / 4, moteur -> window_height * (float)(i + 1.7) / (nb_boutons + 2.2 )) != 0) {
                printf("Erreur update texture bouton\n");
                return -1;//Retourne cas d'erreur
            }
        }
    }
    return 0;//Retourne cas de succès
}

/**
 * \brief Met a jour la texture d'un bouton
 * 
 * \param moteur le moteur
 * \param bouton un bouton
 * \param rect_x coordonées x en haut a gauche du bouton (origine du rectangle en x)
 * \param rect_y coordonées y en haut a gauche du bouton (origine du rectangle en y)
 * \return int 0 si succès, negatif si echec
 */
int update_textureBouton(t_moteur * moteur, t_bouton * bouton, int rect_x, int rect_y) {

    bouton -> rect.x = rect_x - (bouton -> longueur * 10); //Maj des coordonnées x du bouton
    bouton -> rect.y = rect_y;//Maj des coordonnées x du bouton
    bouton -> rect.w = moteur -> echelle * (bouton -> longueur / B_LARGEUR); //Maj de la longeur du bouton selon l'echelle
    bouton -> rect.h = moteur -> echelle * B_LONGUEUR;//Maj de la largeur du bouton selon l'echelle

    if (SDL_RenderCopy(moteur -> renderer, bouton -> texture, NULL, & bouton -> rect) != 0) {
        printf("Erreur du SDL_RenderCopy dans le menu\n");
        return -1;//Retourne cas d'erreur'
    }
    return 0;//Retourne cas de succès
}

/**
 * \brief Initalise un bouton en allouant la memoire et en initialisant ses données
 * 
 * \param moteur le moteur
 * \param nb_boutons nombre de boutons
 * \param nom_boutons tableau de nom des différents boutons
 * \return tableau de boutons alloués et initialisés
 */
t_bouton ** initialiserBoutons(t_moteur * moteur, int nb_boutons, char nom_boutons[][TAILLE_MAX]) {

    t_bouton ** boutons = malloc(sizeof(t_bouton*) * nb_boutons); //Allocation dynamique selon le nombre de boutons

    if (boutons == NULL) {
        printf("Impossible d'allouer la mémoire pour le tableau de bouton\n");
        return NULL;//Retourne cas d'erreur
    }

    for (int i = 0; i < nb_boutons; i++) {//Parcours de tout les boutons
        boutons[i] = malloc(sizeof(t_bouton));

        if (boutons[i] == NULL) {
            printf("Impossible d'allouer la mémoire pour le bouton[%d] dans le menu\n", i);
            return NULL;
        }

        SDL_Surface * surface;
        SDL_Color textColor = { //definition de la couleur d'origine du texte
            255,
            255,
            255,
            0
        };

        TTF_Font * font = TTF_OpenFont("./assets/font/KidpixiesRegular-p0Z1.ttf", 1000);//Definition de la police d'ecriture

        if (font == NULL) {
            fprintf(stderr, "error: font not found\n");
            return NULL;
        }

        boutons[i] -> rect.x = 0; //Initialisation des valeurs a 0
        boutons[i] -> rect.y = 0;
        boutons[i] -> rect.h = 0;
        boutons[i] -> rect.w = 0;
        boutons[i] -> longueur = strlen(nom_boutons[i]);//Initialisation de la longeur selon le nombre de lettres

        surface = TTF_RenderText_Solid(font, nom_boutons[i], textColor);
        boutons[i] -> texture = SDL_CreateTextureFromSurface(moteur -> renderer, surface);
        SDL_FreeSurface(surface);//Destruction de la surface
        SDL_SetTextureColorMod(boutons[i] -> texture, 0, 0, 255);//bleu

        TTF_CloseFont(font);
    }

    return boutons;//retourne le tableau de boutons
}

/**
 * \brief Libère la memoire allouée par la structure d'un boutons, met son pointeur a NULL et libere la texture du bouton
 * 
 * \param boutons adresse du tableau de boutons
 * \param nb_boutons nombre de boutons
 */
void detruireBoutons(t_bouton *** boutons, int nb_boutons) {

    if (*boutons != NULL) {
        for (int i = 0; i < nb_boutons; i++) {//parcours du tableau de boutons
            if ((*boutons)[i] != NULL) {
                SDL_DestroyTexture((*boutons)[i] -> texture);//Desctruction de la texture
                free((*boutons)[i]);//libération de la memoire
            }
        }
        free(*boutons);
    }
    * boutons = NULL;//Mise a NULL 
}

/**
 * \brief Gere les evenements pour le menu
 * Gestion de la position de la souris et des clics
 * 
 * \param moteur le moteur
 * \param boutons le tableau de boutons
 * \return 0 si succes, 1 si l'utilisateur ferme la fenetre, autre chiffre positif selon le bouton appuyé
 */
static int handleEvents_menu(t_moteur * moteur, t_bouton ** boutons) {

    SDL_Point mouse;
    SDL_Event e;

    while (SDL_PollEvent( & e)) {
        //position du curseur de la souris
        mouse.x = e.button.x;
        mouse.y = e.button.y;
        switch (e.type) {
        case SDL_QUIT: //Si le joueur ferme la fenetre a l'aide de la croix
            return 1;
        case SDL_MOUSEBUTTONDOWN: //Si clic
            switch (e.button.button) {
            case SDL_BUTTON_LEFT: // Si clic gauche
                for (int i = 0; i < NB_B_MENU; i++) { //Parcours du tableau de boutons
                    if (SDL_PointInRect(&mouse,&boutons[i]->rect))
                        return i + 2;
                }
                break;
            default:
                break;
            }
            break;
        case SDL_MOUSEMOTION: //Si la souris bouge
        {
            for (int i = 0; i < NB_B_MENU; i++) {
                if (SDL_PointInRect(&mouse,&boutons[i]->rect)){
                    if(i == 2 && moteur->parametres.reset_sauvegarde_joueur == FAUX)
                    SDL_SetTextureColorMod(boutons[i] -> texture, 255, 0, 0);//Rouge
                    else SDL_SetTextureColorMod(boutons[i] -> texture, 255, 0, 0);//rouge
                }
                else{
                    if(i == 2 && moteur->parametres.reset_sauvegarde_joueur == VRAI)
                        SDL_SetTextureColorMod(boutons[i] -> texture, 255, 125, 0);//Orange
                    else  SDL_SetTextureColorMod(boutons[i] -> texture, 0, 0, 255);//Bleu
                }
            }
        }
        break;
        }
    }
    return 0;
}

/**
 * \brief Initalise un rectangle pour du texte en allouant la memoire et en l'initialise
 * 
 * \param moteur moteur du jeu
 * \param texture texture 
 * \param texte texte a afficher
 * \return SDL_Rect* 
 */
SDL_Rect * initialiserTexte(t_moteur * moteur, SDL_Texture ** texture, char * texte){

    SDL_Surface * surface;
    SDL_Rect * rect = malloc(sizeof(SDL_Rect));//Allocation de la mémoire
    if ( rect == NULL) {
        printf("Impossible d'allouer la mémoire pour le texte : %s\n",texte);
        return NULL;//Retourne cas d'erreur
    }
    SDL_Color textColor = { //defenition de la couleur d'origine du texte
        255,
        255,
        255,
        0
    };
    //Premiere police d'ecriture utilisée
    TTF_Font * font = TTF_OpenFont("./assets/font/KidpixiesRegular-p0Z1.ttf", 1000);
    if (font == NULL) {
        fprintf(stderr, "error: font not found\n");
        return NULL;
    }

    rect->x = 0;//initialisation à 0
    rect->y = 0;
    rect->h = 0;
    rect->w = 0;

    surface = TTF_RenderText_Solid(font, texte, textColor);
    *texture = SDL_CreateTextureFromSurface(moteur -> renderer, surface);
    SDL_FreeSurface(surface);
    TTF_CloseFont(font);

    return rect;
}

/**
 * \brief Met a jour la texture du texte
 *
 * \param moteur moteur du jeu
 * \param rect rectangle du texte
 * \param texture texture du texte
 * \param rect_x coordonnées x du rect
 * \param rect_y coordonnées y du rect
 * \param texte texte a afficher
 * \return 0 si succès, negatif si echec
 */
int maj_TextureTexte(t_moteur * moteur,SDL_Rect * rect, SDL_Texture ** texture,int rect_x, int rect_y, char * texte){

    if (SDL_SetRenderDrawColor(moteur -> renderer, 0, 0, 0, 255) != 0) {
        printf("Erreur lors du SDL_SetRenderDrawColor dans le menu");
        return -1;//Retourne cas d'erreur
    }

    rect->x = rect_x - (strlen(texte) * 10); //Maj des coordonnées x du bouton
    rect->y = rect_y;//Maj des coordonnées x du bouton
    rect->w = moteur -> echelle * (strlen(texte)/ T_LARGEUR); //Maj de la longeur du bouton selon l'echelle
    rect->h = moteur -> echelle * T_LONGUEUR;//Maj de la largeur du bouton selon l'echelle

    if (SDL_RenderCopy(moteur -> renderer,*texture, NULL, rect) != 0) {
        printf("Erreur du SDL_RenderCopy pour la texture texte : %s\n",texte);
        return -1;//Retourne cas d'erreur'
    }
    return 0;//Retourne cas de succès
}

/**
 * \brief Libère la memoire allouée pour (le rectangle du) texte, met son pointeur a NULL et libere la texture de ce dernier
 * 
 * \param rect Adresse du rectangle
 * \param texture texture utilisée
 */
void detruireTexte(SDL_Rect ** rect, SDL_Texture * texture){
    SDL_DestroyTexture(texture);//Desctruction de la texture
    if(*rect != NULL){
    free(*rect);
    }
    *rect = NULL;//Mise a NULL 
}



/**
 * \brief Charge le menu (Rectangles, police)
 * 
 * \param moteur Structure du moteur
 * \return code de sortie personnalisé selon l'evenement
 */
e_code_main chargerMenu(t_moteur * moteur) {

    t_bouton ** boutons = NULL;
    char nom_boutons[NB_B_MENU][TAILLE_MAX] = NOMS_B_MENU;
    boutons = initialiserBoutons(moteur, NB_B_MENU, nom_boutons);

    if (boutons == NULL) {
        printf("Erreur allocation memoire boutons\n");
        return ERROR_MENU; //retourne cas d'erreur
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
            printf("Erreur lors du SDL_RenderClear dans le menu principal\n");
            return ERROR_MENU_TEXTURE;//Retourne cas d'erreur
        }
        if (maj_TextureMenu(moteur, boutons, NB_B_MENU) != 0 ) {
            printf("Erreur lors de l'update dans le menu principal\n");
            return ERROR_MENU_TEXTURE;
        }
        if (maj_TextureTexte(moteur, rect_titre,&texture_titre,180,30,"Star Seeker") != 0) {
            printf("Erreur lors de l'update dans le menu principal\n");
            return ERROR_MENU_TEXTURE;
        }

        temp = handleEvents_menu(moteur, boutons);

        switch (temp) {//Selon l'evenement
            case 0:
                break; // on ne fait rien
            case 1: return JEU_QUITTER;
            case 2:
                printf("Nouvelle Partie\n");
                detruireBoutons( & boutons, NB_B_MENU);
                detruireTexte(&rect_titre,texture_titre);
                return M_JEU;
                break;
            case 3:
                printf("Charger Partie\n");
                detruireBoutons( & boutons, NB_B_MENU);
                detruireTexte(&rect_titre,texture_titre);
                return M_CHARGER;
                break;
            case 4:
                printf("Toggle save\n");
                //Si le reset est desactive, on l'active
                if(moteur->parametres.reset_sauvegarde_joueur == FAUX)
                    moteur->parametres.reset_sauvegarde_joueur = VRAI;
                else moteur->parametres.reset_sauvegarde_joueur = FAUX;
                temp = 0;
                break;
            case 5: {
                printf("Options\n");
                detruireBoutons( & boutons, NB_B_MENU);
                detruireTexte(&rect_titre,texture_titre);
                return M_OPTIONS;
            }
            case 6 :{
                printf("Quitter\n");
                detruireBoutons( & boutons, NB_B_MENU);
                detruireTexte(&rect_titre,texture_titre);
                return JEU_QUITTER;
            }
            default: {
                printf("Erreur, menu inconnu");
                detruireBoutons( & boutons, NB_B_MENU);
                detruireTexte(&rect_titre,texture_titre);
                return ERROR_MENU;
            }
        }

    updateEchelle(moteur);//on met a jour l'echelle
    SDL_RenderPresent(moteur -> renderer);
    }
    return ERROR_MENU;
}


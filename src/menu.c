/**
 * \file menu.c
 * \author Guillaume
 * \brief Menu principal
 * 
 */

#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <SDL2/SDL.h>

#include <SDL2/SDL_image.h>

#include <SDL2/SDL_ttf.h>

#include <window.h>

#include <moteur.h>

#include <menu.h>

#include <menu_options.h>

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
    if (SDL_RenderClear(moteur -> renderer) != 0) {
        printf("Erreur lors du SDL_RenderClear dans le menu");
        return -1;//Retourne cas d'erreur
    }

    for (int i = 0; i < nb_boutons; i++) {
        if (nb_boutons > 4) {
            if (i < (nb_boutons / 2)) //On divise par 2 le nombre de boutons pour les mettres sur 2 colonnes et on met la premiere moité sur une premiere colonne
            {                                                                                                      //utiliser pour definir l'espacement entre les boutons
                if (update_textureBouton(moteur, boutons[i], moteur -> window_width / 5, moteur -> window_height * (float)(i + 1.2) / ((nb_boutons + 2.2) / 2)) != 0) {
                    printf("Erreur update texture bouton\n");                                                       //i + cste pour commencer a i !=0 et 
                    return -1;//Retourne cas d'erreur
                }
            } else if (i >= (nb_boutons / 2)) //on repartie la deuxieme moitié des boutons sur la 2eme colonne
    {                                                                                                               //utiliser pour definir l'espacement entre les boutons
                if (update_textureBouton(moteur, boutons[i], moteur -> window_width / 2, moteur -> window_height * (float)(i + 1.2 - (nb_boutons / 2)) / ((nb_boutons + 2.2) / 2)) != 0) {
                    printf("Erreur update texture bouton\n");
                    return -1;//Retourne cas d'erreur
                }
            }
        } else if (nb_boutons <= 4) //Si il y a peu de bouton, on les mets tous sur une meme colonne
        {                                                                                                       //utiliser pour definir l'espacement entre les boutons
            if (update_textureBouton(moteur, boutons[i], moteur -> window_width / 4, moteur -> window_height * (float)(i + 1.7) / (nb_boutons + 2.2 )) != 0) {
                printf("Erreur update texture bouton\n");
                return -1;//Retourne cas d'erreur
            }
        }
    }
    updateEchelle(moteur);//on met a jour l'echelle
    SDL_RenderPresent(moteur -> renderer);
    return 0;//Retourne cas de succès
}

/**
 * \brief Met a jour la texture d'un bouton
 * 
 * \param moteur structure du moteur
 * \param bouton structure d'un bouton
 * \param rect_x coordonées x en haut a gauche du bouton (origine du rectangle en x)
 * \param rect_y coordonées y en haut a gauche du bouton (origine du rectangle en y)
 * \return int 0 si succès, negatif si echec
 */
int update_textureBouton(t_moteur * moteur, t_bouton * bouton, int rect_x, int rect_y) {

    bouton -> rect.x = rect_x - (bouton -> longueur * 10); //Maj des coordonnées x du bouton
    bouton -> rect.y = rect_y;//Maj des coordonnées x du bouton
    bouton -> rect.w = moteur -> echelle * (bouton -> longueur / B_LARGEUR); //Maj de la longeur du bouton selon l'echelle
    bouton -> rect.h = moteur -> echelle * B_LONGUEUR;//Maj de la largeur du bouton selon l'echelle

    if (SDL_RenderDrawRect(moteur -> renderer, & bouton -> rect) != 0) {
        printf("Erreur lors de l'affichage d'un bouton\n");
        return -1;//Retourne cas d'erreur'
    }

    if (SDL_RenderCopy(moteur -> renderer, bouton -> texture, NULL, & bouton -> rect) != 0) {
        printf("Erreur du SDL_RenderCopy dans le menu\n");
        return -1;//Retourne cas d'erreur'
    }
    return 0;//Retourne cas de succès
}

/**
 * \brief Initalise un bouton en allouant la memoire et en initialisant ses données
 * 
 * \param moteur structure du moteur
 * \param nb_boutons nombre de boutons
 * \param nom_boutons tableau de nom des différents boutons
 * \return tableau de boutons initialisés
 */
t_bouton ** initialiserBoutons(t_moteur * moteur, int nb_boutons, char nom_boutons[][TAILLE_MAX]) {

    t_bouton ** boutons = malloc(sizeof(t_bouton * ) * nb_boutons); //Allocation dynamique selon le nombre de boutons

    if ( * boutons == NULL) {
        printf("Impossible d'allouer la mémoire pour le tableau de boutonl\n");
        return NULL;//Retourne cas d'erreur
    }

    for (int i = 0; i < nb_boutons; i++) {//Parcours de tout les boutons
        boutons[i] = malloc(sizeof(t_bouton));

        if (boutons[i] == NULL) {
            printf("Impossible d'allouer la mémoire pour le bouton[%d] dans le menu principal\n", i);
            return NULL;
        }

        SDL_Surface * surface;
        SDL_Color textColor = { //defenition de la couleur d'origine du texte
            255,
            255,
            255,
            0
        };

        TTF_Font * font = TTF_OpenFont("./PressStart2P-Regular.ttf", 1000);//Definition de la police d'ecriture

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
        SDL_SetTextureColorMod(boutons[i] -> texture, 0, 0, 255);

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

    if ( * boutons != NULL) {
        for (int i = 0; i < nb_boutons; i++) {//parcours des boutons
            if (( * boutons)[i] != NULL) {
                SDL_DestroyTexture(( * boutons)[i] -> texture);//Desctruction de la texture
                free(( * boutons)[i]);//liberation de la memoire
            }
        }
        free( * boutons);
    }
    * boutons = NULL;//Mise a NULL 
}

/**
 * \brief Gere les evenements pour le menu
 * Gestion de la position de la souris et des clics
 * 
 * \param moteur strcture moteur
 * \param boutons tableau de boutons
 * \return int 0 si succes, 1 si l'utilisateur ferme la fenetre, autre chiffre positif selon le bouton appuyé
 */
static int handleEvents_menu(t_moteur * moteur, t_bouton ** boutons) {

    int mouse_x, mouse_y; /**Coordonnées du curseur*/
    SDL_Event e;

    while (SDL_PollEvent( & e)) {
        mouse_x = e.button.x, mouse_y = e.button.y; /*Mise a jour de la position du curseur*/
        switch (e.type) {
        case SDL_QUIT:
            return 1;
        case SDL_MOUSEBUTTONDOWN:
            switch (e.button.button) {
            case SDL_BUTTON_LEFT:
                for (int i = 0; i < NB_B_MENU; i++) {
                    if (((mouse_x >= boutons[i] -> rect.x) && (mouse_x <= (boutons[i] -> rect.x + moteur -> echelle * (boutons[i] -> longueur / B_LARGEUR)))) && ((mouse_y >= boutons[i] -> rect.y) && (mouse_y <= (boutons[i] -> rect.y + moteur -> echelle * B_LONGUEUR))))
                        return i + 2;
                }
                break;
            default:
                return -1;
            }
            break;
        case SDL_MOUSEMOTION: {

            for (int i = 0; i < NB_B_MENU; i++) {
                if (((mouse_x >= boutons[i] -> rect.x) && (mouse_x <= (boutons[i] -> rect.x + moteur -> echelle * (boutons[i] -> longueur / B_LARGEUR)))) && ((mouse_y >= boutons[i] -> rect.y) && (mouse_y <= (boutons[i] -> rect.y + moteur -> echelle * B_LONGUEUR))))
                    SDL_SetTextureColorMod(boutons[i] -> texture, 255, 0, 0);
                else SDL_SetTextureColorMod(boutons[i] -> texture, 0, 0, 255);
            }
        }
        break;

        }
    }
    return 0;
}


SDL_Rect * initialiserTexte(t_moteur * moteur, int rect_y, char * texte){

    SDL_Surface * surface;
    SDL_Texture * texture;
    SDL_Rect *rect = malloc(sizeof(SDL_Rect));

    SDL_Color textColor = { //defenition de la couleur d'origine du texte
        255,
        255,
        255,
        0
    };

    TTF_Font * font = TTF_OpenFont("./PressStart2P-Regular.ttf", 1000);//Definition de la police d'ecriture

    if (font == NULL) {
        fprintf(stderr, "error: font not found\n");
        return NULL;
    }


    rect->x = (strlen(texte)* 10);
    rect->y = rect_y;
    rect->h = moteur -> echelle * B_LONGUEUR;
    rect->w = moteur -> echelle * ((strlen(texte)* 10) / B_LARGEUR);


    surface = TTF_RenderText_Solid(font, texte, textColor);
    texture = SDL_CreateTextureFromSurface(moteur -> renderer, surface);
    SDL_FreeSurface(surface);
    SDL_SetTextureColorMod(texture, 0, 0, 255);

    TTF_CloseFont(font);

    if (SDL_RenderDrawRect(moteur -> renderer, rect) != 0) {
        printf("Erreur lors de l'affichage d'un bouton\n");
        return NULL;//Retourne cas d'erreur'
    }

    if (SDL_RenderCopy(moteur -> renderer,texture, NULL, rect) != 0) {
        printf("Erreur du SDL_RenderCopy dans le menu\n");
        return NULL;//Retourne cas d'erreur'
    }
    return rect;
}




/**
 * \brief Charge le menu (Rectangles, police)
 * 
 * \param moteur Structure du moteur
 * \return int 0 si succès, negatif si echec
 */
int chargerMenu(t_moteur * moteur) {

    t_bouton ** boutons = NULL;
    SDL_Rect * titre = initialiserTexte(moteur,100,"Star Seeker");


    char nom_boutons[NB_B_MENU][TAILLE_MAX] = NOMS_B_MENU;

    boutons = initialiserBoutons(moteur, NB_B_MENU, nom_boutons);

    if (boutons == NULL) {
        printf("Erreur allocation memoire boutons\n");
        return -1;
    }

    int temp = 0;

    while (temp == 0) {

        if (maj_TextureMenu(moteur, boutons, NB_B_MENU) != 0) {
            printf("Erreur lors de l'update dans le menu principal");
            return -1;
        }
        temp = handleEvents_menu(moteur, boutons); 

        switch (temp) {
        case 0:
            break;
        case 1:
        case 5:
        case -1: {
            detruireBoutons( & boutons, NB_B_MENU);
            return -1;
        }
        case 2:
            printf("Nouvelle Partie\n");
            break;
        case 3:
            printf("Charger Partie\n");
            break;
        case 4: {
            printf("Options\n");
            detruireBoutons( & boutons, NB_B_MENU);
            chargerMenu_Options(moteur);
            break;
        }

        default: {
            printf("Erreur, menu inconnu");
            detruireBoutons( & boutons, NB_B_MENU);
            return -1;
        }
        }
    }
    return 0;
}
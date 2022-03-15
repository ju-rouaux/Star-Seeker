#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <window.h>
#include <moteur.h>
#include <menu_planetes.h>


int update_texturePlanetes(t_moteur * moteur, t_planetes * planetes, int num,int nb_planetes){

    planetes->rect.x = (num / (nb_planetes + 2));
    planetes->rect.y = moteur -> echelle * cos((num + nb_planetes)/(nb_planetes +1));
    planetes->rect.w = moteur -> echelle * 2;
    planetes->rect.h = moteur -> echelle * 2;


    if (SDL_RenderDrawRect(moteur -> renderer, & planetes -> rect) != 0) {
        printf("Erreur lors de l'affichage d'un bouton\n");
        return -1;//Retourne cas d'erreur'
    }

    if (SDL_RenderCopy(moteur -> renderer, planetes -> texture, NULL, & planetes -> rect) != 0) {
        printf("Erreur du SDL_RenderCopy dans le menu\n");
        return -1;//Retourne cas d'erreur'
    }

    return 0;//Retourne cas de succès
}



int maj_TextureMenuPlanetes(t_moteur * moteur, t_planetes ** planetes, int nb_planetes) {

    if (SDL_SetRenderDrawColor(moteur -> renderer, 0, 0, 0, 255) != 0) {
        printf("Erreur lors du SDL_SetRenderDrawColor dans le menu");
        return -1;//Retourne cas d'erreur
    }

    for (int i = 0; i < nb_planetes; i++) {
            if (update_texturePlanetes(moteur, planetes[i],i + 1, nb_planetes) != 0) {
                printf("Erreur update texture bouton\n");
                return -1;//Retourne cas d'erreur
            }
    }
    return 0;//Retourne cas de succès
}


t_planetes ** initialiserPlanetes(t_moteur * moteur, int nb_planetes){
    t_planetes ** planetes = malloc(sizeof(t_planetes*) * nb_planetes); //Allocation dynamique selon le nombre de boutons

    if (planetes == NULL) {
        printf("Impossible d'allouer la mémoire pour le tableau de bouton\n");
        return NULL;//Retourne cas d'erreur
    }

    for (int i = 0; i < nb_planetes; i++) {//Parcours de tout les boutons
        planetes[i] = malloc(sizeof(t_planetes));

        if (planetes[i] == NULL) {
            printf("Impossible d'allouer la mémoire pour le bouton[%d] dans le menu principal\n", i);
            return NULL;
        }

        SDL_Surface * surface;

        surface = SDL_LoadBMP("./img/planete.bmp");
        if(surface == NULL)
        {
            printf("Impossible de charger la surface tileset_map.bmp : %s\n", SDL_GetError());
            free(planetes[i]->texture);
            return NULL;
        }
        planetes[i]->texture = SDL_CreateTextureFromSurface(moteur->renderer, surface);
        SDL_FreeSurface(surface);

        if(planetes[i]->texture == NULL)
        {
            printf("Impossible de charger la texture de tileset_map.bmp : %s\n", SDL_GetError());
            free(planetes[i]->texture);
            return NULL;
        }
    }

    return planetes;//retourne le tableau de boutons
}

/**
 * \brief Libère la memoire allouée par la structure d'un boutons, met son pointeur a NULL et libere la texture du bouton
 * 
 * \param boutons adresse du tableau de boutons
 * \param nb_boutons nombre de boutons
 */
void detruirePlanetes(t_planetes *** planetes, int nb_planetes) {

    if (*planetes != NULL) {
        for (int i = 0; i < nb_planetes; i++) {//parcours des boutons
            if ((*planetes)[i] != NULL) {
                SDL_DestroyTexture((*planetes)[i] -> texture);//Desctruction de la texture
                free((*planetes)[i]);//liberation de la memoire
            }
        }
        free(*planetes);
    }
    * planetes = NULL;//Mise a NULL 
}


static int handleEvents_menu(t_moteur * moteur, t_planetes ** planetes, int nb_planetes) {

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
                for (int i = 0; i < nb_planetes; i++) {
                    if (((mouse_x >= planetes[i] -> rect.x) && (mouse_x <= (planetes[i] -> rect.x + moteur -> echelle * 5))) && ((mouse_y >= planetes[i] -> rect.y) && (mouse_y <= (planetes[i] -> rect.y + moteur -> echelle * 2))))
                        return i + 2;
                }
                break;
            default:
                return -1;
            }
            break;
        case SDL_MOUSEMOTION: {

            for (int i = 0; i < nb_planetes; i++) {
                if (((mouse_x >= planetes[i] -> rect.x) && (mouse_x <= (planetes[i] -> rect.x + moteur -> echelle * 5))) && ((mouse_y >= planetes[i] -> rect.y) && (mouse_y <= (planetes[i] -> rect.y + moteur -> echelle * 2))))
                    SDL_SetTextureColorMod(planetes[i] -> texture, 255, 0, 0);
                else SDL_SetTextureColorMod(planetes[i] -> texture, 0, 0, 255);
            }
        }
        break;

        }
    }
    return 0;
}


int chargerMenu_planetes(t_moteur * moteur, int nb_planetes, int r, int g, int b){

    t_planetes ** planetes = initialiserPlanetes(moteur,nb_planetes);

    if (planetes == NULL) {
        printf("Erreur allocation memoire boutons\n");
        return -1;
    }


    int temp = 0;

    while (temp == 0) {
        if (SDL_RenderClear(moteur -> renderer) != 0) {
            printf("Erreur lors du SDL_RenderClear dans le menu");
            return -1;//Retourne cas d'erreur
        }
        if (maj_TextureMenuPlanetes(moteur, planetes, nb_planetes) != 0 ) {
            printf("Erreur lors de l'update dans le menu principal");
            return -1;
        }

        temp = handleEvents_menu(moteur, planetes, nb_planetes);

        switch (temp) {
            case 0:
                break;
            case 1:
            case 5:
            case -1: {
                detruirePlanetes( & planetes, nb_planetes);
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
            }
            default: {
                printf("Erreur, menu inconnu");
                detruirePlanetes( & planetes, nb_planetes);
                return -1;
            }
        }
    
    updateEchelle(moteur);//on met a jour l'echelle
    SDL_RenderPresent(moteur -> renderer);
    }
    return 0;



}
/**
 * \file menu_credits.h
 * 
 * \brief Menu d'affichage des crédits du jeu
 * 
 * \author Julien Rouaux
 */

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <moteur.h>
#include <main.h>

#define PRECISION_RENDU_TEXTE 1000


/**
 * \struct t_texte
 * \brief Structure facilitant la manipulation des textes affichés
 */
typedef struct
{
    SDL_Texture * rendu_texte;
    int largeur;
    int hauteur;
    int indice;
} t_texte;


/**
 * \brief Affiche a l'écran du texte.
 * 
 * \param moteur Le moteur
 * \param texte Le texte à afficher
 * \param souris L'emplacement de la souris (ou NULL) si une variation de couleur est souhaitée lorsque la souris survole le texte
 * \param rect_retour Le rectangle où retourner l'emplacement du rendu du texte (ou NULL si pas nécéssaire)

 */
static void renduTexte(t_moteur * moteur, t_texte * texte, SDL_Point * souris, SDL_Rect * rect_retour)
{
    SDL_Rect dest;
    dest.w = (float)texte->largeur/PRECISION_RENDU_TEXTE * moteur->echelle;
    dest.h = (float)texte->hauteur/PRECISION_RENDU_TEXTE * moteur->echelle;
    dest.x = moteur->window_width / 2 - dest.w / 2 - 25;
    dest.y = texte->indice * moteur->window_height / 6 - 50;

    SDL_SetTextureColorMod(texte->rendu_texte, 224, 130, 16);

    if(texte->indice == 1 || texte->indice == 5) //Titre ou retour
        SDL_SetTextureColorMod(texte->rendu_texte, 0, 0, 255);

    if(souris != NULL)
        if(SDL_PointInRect(souris, &dest))
            SDL_SetTextureColorMod(texte->rendu_texte, 255,0,0);

    if(rect_retour != NULL)
    {
        rect_retour->h = dest.h;
        rect_retour->w = dest.w;
        rect_retour->x = dest.x;
        rect_retour->y = dest.y;
    }

    SDL_RenderCopy(moteur->renderer, texte->rendu_texte, NULL, &dest);
}


/**
 * \brief Génère le texte à afficher sur le menu.
 * 
 * \param moteur Le moteur
 * \param police La police d'affichage
 * \param contenu Le texte à afficher
 * \param indice L'ordre d'affichagede haut en bas
 * 
 * \return La structure pour afficher le texte.
 */
static t_texte * creerRenduTexte(t_moteur * moteur, TTF_Font * police, char * contenu, int indice)
{
    SDL_Surface * surface = NULL;
    SDL_Color couleur = {255,255,255,255};
    t_texte * texte = malloc(sizeof(t_texte));
    if(texte == NULL)
        return NULL;

    if(TTF_SizeText(police, contenu, &texte->largeur, &texte->hauteur) != 0)
    {
        texte->largeur = 4;
        texte->hauteur = 1; 
    }
    surface = TTF_RenderText_Solid(police, contenu, couleur);
    if(surface == NULL)
    {
        free(texte);
        return NULL;
    }
    texte->rendu_texte = SDL_CreateTextureFromSurface(moteur->renderer, surface);
    SDL_FreeSurface(surface);

    texte->indice = indice;

    return texte;
}


/**
 * \brief Libère la mémoire allouée aux textes du menu.
 */
static void freeMenu(t_texte ** titre, t_texte ** julien, t_texte ** guillaume, t_texte ** camille, t_texte ** retour)
{
    if(*titre != NULL)
        free(*titre);
    *titre = NULL;

    if(*julien != NULL)
        free(*julien);
    *julien = NULL;

    if(*guillaume != NULL)
        free(*guillaume);
    *guillaume = NULL;

    if(*camille != NULL)
        free(*camille);
    *camille = NULL;

    if(*retour != NULL)
        free(*retour);
    *retour = NULL;
}


/**
 * \brief Affiche le menu des crédits.
 * 
 * \param moteur Le moteur
 * 
 * \return L'action à réaliser après la fermeture du menu.
 */
e_code_main afficherMenuCredits(t_moteur * moteur)
{
    int sortie = 0;
    SDL_Event event;
    SDL_Point souris;
    SDL_Rect rect_retour;

    t_texte *titre, *julien, *guillaume, *camille, *retour;
    TTF_Font * police = TTF_OpenFont("./assets/font/KidpixiesRegular-p0Z1.ttf", PRECISION_RENDU_TEXTE);
    if(police == NULL)
        return M_PRINCIPAL;

    titre = creerRenduTexte(moteur, police, "Credits - Star Seeker", 1);
    julien = creerRenduTexte(moteur, police, "Julien Rouaux", 2);
    guillaume = creerRenduTexte(moteur, police, "Guillaume Richard", 3);
    camille = creerRenduTexte(moteur, police, "Camille Remoue", 4);
    retour = creerRenduTexte(moteur, police, "Retour", 5);

    TTF_CloseFont(police);

    while(sortie == 0)
    {
        regulerFPS(moteur);
        updateEchelle(moteur);
        SDL_GetMouseState(&souris.x, &souris.y);

        //Events
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT:
                    freeMenu(&titre, &julien, &guillaume, &camille, &retour);
                    return JEU_QUITTER;

                case SDL_MOUSEBUTTONDOWN:
                    if(SDL_PointInRect(&souris, &rect_retour))
                    {
                        freeMenu(&titre, &julien, &guillaume, &camille, &retour);
                        return M_OPTIONS;
                    }
                    break;

                default:
                    break;
            }
        }

        renduTexte(moteur, titre, NULL, NULL);
        renduTexte(moteur, julien, NULL, NULL);
        renduTexte(moteur, guillaume, NULL, NULL);
        renduTexte(moteur, camille, NULL, NULL);
        renduTexte(moteur, retour, &souris, &rect_retour);

        //Rendu
        SDL_RenderPresent(moteur->renderer);
        SDL_RenderClear(moteur->renderer);
    }

    freeMenu(&titre, &julien, &guillaume, &camille, &retour);
    return M_OPTIONS;
}
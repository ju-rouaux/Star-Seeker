/**
 * \file menu_niveau.c
 * 
 * \brief Menu de sélection d'un niveau d'une partie.
 * 
 * \author Julien Rouaux
 */


#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <main.h>
#include <moteur.h>
#include <audio.h>
#include <generation_niveau.h>

#define PRECISION_RENDU_TEXTE 1000

/**
 * \struct t_selection
 * \brief Représente un choix sur le menu de sélection de niveau.
 * 
 * La sélection se compose d'un texte : le nom de la planète,
 * et de l'image d'une planète à l'échelle du niveau.
 */
typedef struct
{
    int indice;

    SDL_Texture * rendu_texte;
    int largeur_texte;
    int hauteur_texte;

    float taille_planete;

    SDL_Rect position_planete;
    SDL_Rect position_texte;
} t_selection;


/**
 * \struct t_texte
 * \brief Modélise un simple élément textuel du menu.
 */
typedef struct
{
    SDL_Texture * rendu_texte;
    int largeur;
    int hauteur;
} t_texte;




/**
 * \brief Retourne l'indice du niveau étant survolé par la souris.
 * 
 * \param selections La liste différentes options du menu
 * \param nb_selects Le nombre de sélections différentes
 * \param souris La position du curseur de la souris
 * 
 * \return L'indice du niveau survolé par la souris, ou -1 si aucun.
 */
static int indiceSelection(t_selection ** selections, int nb_selects, SDL_Point * souris)
{
    for(int i = 0; i < nb_selects; i++)
        if(SDL_PointInRect(souris, &selections[i]->position_planete) || SDL_PointInRect(souris, &selections[i]->position_texte))
            return i;
    
    return -1;
}


/**
 * \brief Affiche une sélection du menu en fonction de son indice.
 * 
 * \param moteur Le moteur
 * \param select La sélection à afficher
 * \param apparence L'apparence de la planète affichée sur la sélection
 * \param quantite Le nombre de sélections total qui sera affiché sur l'écran
 */
static void renduSelection(t_moteur * moteur, t_selection * select, SDL_Texture * apparence, int quantite)
{
    //Calcul de la position de la sélection
    int x = moteur->window_width / 5 + (select->indice * (moteur->window_width - moteur->window_width / 5) / quantite);
    int y = moteur->window_height / 2;

    //Rendu planète
    select->position_planete.h = moteur->echelle * select->taille_planete;
    select->position_planete.w = moteur->echelle * select->taille_planete;
    select->position_planete.x = x - select->position_planete.w / 2;
    select->position_planete.y = y + (select->indice % 2 ? y/3 : -y/3) - select->position_planete.h / 2;
    SDL_RenderCopy(moteur->renderer, apparence, NULL, &select->position_planete);
    
    //Rendu texte
    select->position_texte.w = (float)select->largeur_texte/PRECISION_RENDU_TEXTE * moteur->echelle/2;
    select->position_texte.h = (float)select->hauteur_texte/PRECISION_RENDU_TEXTE * moteur->echelle/2;
    select->position_texte.x = x - select->position_texte.w / 2;
    select->position_texte.y = select->position_planete.y + select->position_planete.h;
    SDL_RenderCopy(moteur->renderer, select->rendu_texte, NULL, &select->position_texte);
}


/**
 * \brief Créer un bouton pour sélectionner un niveau.
 * 
 * \param renderer Le renderer du jeu
 * \param police La police d'affichage du nom de la planète
 * \param texte Le nom de la planète
 * \param indice L'indice du niveau
 * \param taille_planete La taille d'affichage de la planète
 * 
 * \return Le bouton, NULl si echec.
 */
static t_selection * creerSelection(SDL_Renderer * renderer, TTF_Font * police, char * texte, int indice, float taille_planete)
{
    t_selection * select = malloc(sizeof(t_selection));
    if(select == NULL)
        return NULL;

    //Calculer taille texte
    if(TTF_SizeText(police, texte, &select->largeur_texte, &select->hauteur_texte) != 0)
    {
        select->largeur_texte = 4;
        select->hauteur_texte = 1;
    }
    
    //Générer texte
    SDL_Color couleur = {255,255,255,255};
    SDL_Surface * surface = TTF_RenderText_Solid(police, texte, couleur);
    if(surface == NULL)
    {
        free(select);
        return NULL;
    }
    select->rendu_texte = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    if(select->rendu_texte == NULL)
    {
        free(select);
        return NULL;
    }
    surface = NULL;

    //Autres données
    select->taille_planete = taille_planete;
    select->indice = indice;

    return select;
}


/**
 * \brief Libère la mémoire allouée à la liste de sélections du menu.
 * 
 * \param selections Adresse de la liste des sélections à libérer
 * \param nb_selections Nombre d'éléments dans la liste
 */
static void detruireSelections(t_selection *** selections, int nb_selections)
{
    if(*selections != NULL)
    {
        for(int i = 0; i < nb_selections; i++)
        {
            if((*selections)[i] != NULL)
            {
                SDL_DestroyTexture((*selections)[i]->rendu_texte);
                free((*selections)[i]);
            }
            (*selections)[i] = NULL;
        }
        free(*selections);
    }
    *selections = NULL;
}


/**
 * \brief Alloue la liste infos_niveau les différents choix du menu.
 * 
 * \param moteur Le moteur
 * \param police La police du texte à afficher
 * \param infos_niveaux La liste des informations sur la structure des niveaux de la partie
 * \param nb_infos Le nombre d'éléments de la liste
 * \param ancien_niveau_charge Indice du niveau précédemment chargé
 * 
 * \return La liste des différents choix contextuels du menu.
 */
static t_selection ** initSelections(t_moteur * moteur, TTF_Font * police, niveau_informations_t ** infos_niveaux, int nb_infos, int ancien_niveau_charge)
{
    float taille_planete;

    //Matrice des sélections possibles du menu
    t_selection ** selections = malloc(sizeof(t_selection*) * nb_infos);
    if(selections == NULL)
        return NULL;

    for(int i = 0; i < nb_infos; i++)
    {
        //Taille proportionelle à la surface de la planète
        taille_planete = (infos_niveaux[i]->hauteur * infos_niveaux[i]->longueur)*3.0/900;
        
        if(i == ancien_niveau_charge) //Indiquer au joueur le niveau où il est situé mettent le nom de la planète en italique
            TTF_SetFontStyle(police, TTF_STYLE_ITALIC);

        selections[i] = creerSelection(moteur->renderer, police, infos_niveaux[i]->nom_planete, i, taille_planete);
        if(selections[i] == NULL)
        {
            detruireSelections(&selections, i-1);
            return NULL;
        }

        if(i == ancien_niveau_charge)
            TTF_SetFontStyle(police, TTF_STYLE_NORMAL);
    }

    return selections;
}


/**
 * \brief Affiche le nom de la galaxie en guise de titre du menu
 * 
 * \param moteur Le moteur
 * \param titre Le titre à afficher
 */
static void renduTitre(t_moteur * moteur, t_texte * titre)
{
    SDL_Rect dest;
    dest.w = (float)titre->largeur/PRECISION_RENDU_TEXTE * moteur->echelle*1.5;
    dest.h = (float)titre->hauteur/PRECISION_RENDU_TEXTE * moteur->echelle*1.5;
    dest.x = 20; //offset de 20 px
    dest.y = 20; //offset de 20 px
    SDL_RenderCopy(moteur->renderer, titre->rendu_texte, NULL, &dest);
}


/**
 * \brief 
 * 
 * \param moteur le moteur
 * \param bouton le bouton
 * \param souris Coordonnées de la souris
 * \return Vrai si la souris survole le bouton, faux sinon.
 */
static int renduBoutonMenuPrincipal(t_moteur * moteur, t_texte * bouton, SDL_Point * souris)
{
    int survole = 0;

    SDL_Rect dest;
    dest.w = (float)bouton->largeur/PRECISION_RENDU_TEXTE * moteur->echelle;
    dest.h = (float)bouton->hauteur/PRECISION_RENDU_TEXTE * moteur->echelle;
    dest.x = 20; //offset de 20 px
    dest.y = moteur->window_height - dest.h - 20; //offset de 20 px

    if( (survole = SDL_PointInRect(souris, &dest)) )
        SDL_SetTextureColorMod(bouton->rendu_texte, 255,0,0);
    else
        SDL_SetTextureColorMod(bouton->rendu_texte, 255,255,255);

    SDL_RenderCopy(moteur->renderer, bouton->rendu_texte, NULL, &dest);

    return survole;
}



/**
 * \brief Initialise le menu
 * 
 * \param moteur le moteur
 * \param infos_niveaux La liste des informations sur la structure des niveaux de la partie
 * \param nb_infos Le nombre d'éléments de la liste
 * \param titre L'adresse du titre a initialiser
 * \param menu L'adresse du menu a initialiser
 * \param ancien_niveau_charge Indice du niveau précédemment chargé
 * \return la structure du menu allouée
 */
static t_selection ** initMenu(t_moteur * moteur, niveau_informations_t ** infos_niveaux, int nb_infos, t_texte ** titre, t_texte ** menu, int ancien_niveau_charge)
{
    //Police d'affichage
    TTF_Font * police = TTF_OpenFont("./assets/font/KidpixiesRegular-p0Z1.ttf", PRECISION_RENDU_TEXTE);
    if(police == NULL)
    {
        printf("Impossible d'ouvrir la police\n");
        return NULL;
    }


    //Générer les sélections
    t_selection ** selections = initSelections(moteur, police, infos_niveaux, nb_infos, ancien_niveau_charge);
    if(selections == NULL)
    {
        TTF_CloseFont(police);
        return NULL;
    }


    SDL_Color couleur = {255,255,255,255};
    SDL_Surface * surface = NULL;


    //Générer le titre
    *titre = malloc(sizeof(t_texte));
    if(*titre == NULL)
    {
        detruireSelections(&selections, nb_infos);
        TTF_CloseFont(police);
        return NULL;
    }
    if(TTF_SizeText(police, moteur->galaxie, &(*titre)->largeur, &(*titre)->hauteur) != 0)
    {
        (*titre)->largeur = 4;
        (*titre)->hauteur = 1;
    }
    surface = TTF_RenderText_Solid(police, moteur->galaxie, couleur);
    if(surface == NULL)
    {
        detruireSelections(&selections, nb_infos);
        TTF_CloseFont(police);
        return NULL;
    }
    (*titre)->rendu_texte = SDL_CreateTextureFromSurface(moteur->renderer, surface);
    SDL_FreeSurface(surface);
    if((*titre)->rendu_texte == NULL)
    {
        detruireSelections(&selections, nb_infos);
        TTF_CloseFont(police);
        return NULL;
    }
    surface = NULL;


    //Générer bouton menu principal
    *menu = malloc(sizeof(t_texte));
    if(*menu == NULL)
    {
        SDL_DestroyTexture((*titre)->rendu_texte);
        free(*titre);
        detruireSelections(&selections, nb_infos);
        TTF_CloseFont(police);
        return NULL;
    }
    if(TTF_SizeText(police, "Partir", &(*menu)->largeur, &(*menu)->hauteur) != 0)
    {
        (*menu)->largeur = 4;
        (*menu)->hauteur = 1;
    }
    surface = TTF_RenderText_Solid(police, "Partir", couleur);
    if(surface == NULL)
    {
        free(*menu);
        SDL_DestroyTexture((*titre)->rendu_texte);
        free(*titre);
        detruireSelections(&selections, nb_infos);
        TTF_CloseFont(police);
        return NULL;
    }
    (*menu)->rendu_texte = SDL_CreateTextureFromSurface(moteur->renderer, surface);
    SDL_FreeSurface(surface);
    if((*menu)->rendu_texte == NULL)
    {
        free(*menu);
        SDL_DestroyTexture((*titre)->rendu_texte);
        free(*titre);
        detruireSelections(&selections, nb_infos);
        TTF_CloseFont(police);
        return NULL;
    }
    surface = NULL;

    TTF_CloseFont(police);

    return selections;
}

/**
 * \brief Detruit et libère la mémoire allouée
 * 
 * \param selections Adresse de la liste des sélections à libérer
 * \param nb_selections Nombre d'éléments dans la liste
 * \param titre adresse du titre a detruire
 * \param menu adresse du menu a detruire
 */
static void freeMenu(t_selection *** selections, int nb_selections, t_texte ** titre, t_texte ** menu)
{
    detruireSelections(selections, nb_selections);
    if(*menu != NULL)
    {
        SDL_DestroyTexture((*menu)->rendu_texte);
        free(*menu);
    }
    if(*titre != NULL)
    {
        SDL_DestroyTexture((*titre)->rendu_texte);
        free(*titre);
    }
    *titre = NULL;
    *menu = NULL;
}

/**
 * \brief Affiche le menu de sélection d'une planète.
 * 
 * \param retour_niveau Valeur de sortie, retourne l'indice du niveau à charger si un choix est fait
 * \param moteur Le moteur
 * \param infos_niveaux La liste des informations sur la structure des niveaux de la partie
 * \param nb_infos Le nombre d'éléments de la liste
 * \param ancien_niveau_charge Indice du niveau précédemment chargé
 * 
 * \return L'action réalisée, l'indice du niveau choisi est retourné dans retour_niveau si NIVEAU_CHANGER est retourné.
 */
e_code_main afficherMenuNiveau(int * retour_niveau, t_moteur * moteur, niveau_informations_t ** infos_niveaux, int nb_infos, int ancien_niveau_charge)
{
    SDL_Event event;
    SDL_Point souris;

    int sortie = 0; //Code de sortie du menu
    int indice_selection = -1; //Niveau selectionné (-1 si aucun)

    t_texte * titre, *menu;

    //Initialisation
    t_selection ** selections = initMenu(moteur, infos_niveaux, nb_infos, &titre, &menu, ancien_niveau_charge);
    if(selections == NULL)
        return M_PRINCIPAL;

    //Boucle principale
    while(sortie == 0)
    {
        regulerFPS(moteur);
        updateEchelle(moteur);

        //Events
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT:
                    freeMenu(&selections, nb_infos, &titre, &menu);
                    return JEU_QUITTER;
                
                case SDL_KEYDOWN:
                    switch (event.key.keysym.scancode)
                    {
                    case SDL_SCANCODE_ESCAPE :
                        *retour_niveau = ancien_niveau_charge;
                        freeMenu(&selections, nb_infos, &titre, &menu);
                        return NIVEAU_CHANGER;
                        
                    default:
                        break;
                    }break;

                case SDL_MOUSEBUTTONDOWN:
                    if(indice_selection == -2)
                    {
                        freeMenu(&selections, nb_infos, &titre, &menu);
                        Mix_PlayChannel(4, moteur->bruitages->menu_selection, 0);
                        return M_PRINCIPAL;
                    }
                    else if(indice_selection != -1)
                    {
                        *retour_niveau = indice_selection;
                        freeMenu(&selections, nb_infos, &titre, &menu);
                        return NIVEAU_CHANGER;
                    }
                    break;

                default:
                    break;
            }
        }

        //Rendu des selections puis obtenir la selection
        SDL_GetMouseState(&souris.x, &souris.y);
        for(int i = 0; i < nb_infos; i++)
        {
            if(indice_selection == i)
            {
                SDL_SetTextureColorMod(selections[i]->rendu_texte, 255,0,0);
                SDL_SetTextureColorMod(moteur->textures->planete, 255,0,0);
            }
            else
            {
                SDL_SetTextureColorMod(selections[i]->rendu_texte, infos_niveaux[i]->rouge, infos_niveaux[i]->vert, infos_niveaux[i]->bleu);
                SDL_SetTextureColorMod(moteur->textures->planete, infos_niveaux[i]->rouge, infos_niveaux[i]->vert, infos_niveaux[i]->bleu);
            }
            renduSelection(moteur, selections[i], moteur->textures->planete, nb_infos);
        }
        indice_selection = indiceSelection(selections, nb_infos, &souris);

        renduTitre(moteur, titre);
        if(renduBoutonMenuPrincipal(moteur, menu, &souris))
            indice_selection = -2;
        
        //Rendu
        SDL_RenderPresent(moteur->renderer);
        SDL_RenderClear(moteur->renderer);
    }
    

    detruireSelections(&selections, nb_infos);
    return M_PRINCIPAL;
}
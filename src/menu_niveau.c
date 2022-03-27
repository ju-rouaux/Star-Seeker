#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <generation_niveau.h>
#include <main.h>


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


//Retourne -1 si rien survolé, sinon indice sélection
static int indiceSelection(t_selection ** selections, int nb_selects, SDL_Point * souris)
{
    for(int i = 0; i < nb_selects; i++)
        if(SDL_PointInRect(souris, &selections[i]->position_planete) || SDL_PointInRect(souris, &selections[i]->position_texte))
            return i;
    
    return -1;
}


static void renduSelection(t_moteur * moteur, t_selection * select, SDL_Texture * apparence, int quantite)
{
    SDL_SetTextureColorMod(select->rendu_texte, 255,255,255);
    int x = moteur->window_width / 4 + (select->indice * (moteur->window_width - moteur->window_width / 4) / quantite);
    int y = moteur->window_height / 2;
    //Rendu planète
    select->position_planete.h = moteur->echelle * select->taille_planete;
    select->position_planete.w = moteur->echelle * select->taille_planete;
    select->position_planete.x = x - select->position_planete.w / 2;
    select->position_planete.y = y + (select->indice % 2 ? y/3 : -y/3) - select->position_planete.h / 2;
    SDL_RenderCopy(moteur->renderer, apparence, NULL, &select->position_planete);
    
    //Rendu texte
    select->position_texte.w = (float)select->largeur_texte/1000 * moteur->echelle/2;
    select->position_texte.h = (float)select->hauteur_texte/1000 * moteur->echelle/2;
    select->position_texte.x = x - select->position_texte.w / 2;
    select->position_texte.y = select->position_planete.y + select->position_planete.h;
    SDL_RenderCopy(moteur->renderer, select->rendu_texte, NULL, &select->position_texte);
}



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
        printf("erreur surface\n");
        free(select);
        return NULL;
    }
    select->rendu_texte = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    if(select->rendu_texte == NULL)
    {
        printf("erreur texture\n");
        free(select);
        return NULL;
    }
    surface = NULL;

    //Autres données
    select->taille_planete = de(3);
    select->indice = indice;

    return select;
}


void detruireSelections(t_selection *** selections, int nb_selections)
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

t_selection ** initSelections(t_moteur * moteur, niveau_informations_t ** infos_niveaux, int nb_infos)
{
    //Matrice des sélections possibles du menu
    t_selection ** selections = malloc(sizeof(t_selection*) * nb_infos);
    if(selections == NULL)
        return NULL;

    //Police d'affichage
    TTF_Font * police = TTF_OpenFont("./assets/font/KidpixiesRegular-p0Z1.ttf", 1000);
    if(police == NULL)
    {
        printf("Impossible d'ouvrir la police\n");
        free(selections);
        return NULL;
    }
    
    for(int i = 0; i < nb_infos; i++)
    {
        selections[i] = creerSelection(moteur->renderer, police, infos_niveaux[i]->nom_planete, i, infos_niveaux[i]->longueur/10);
        if(selections[i] == NULL)
        {
            TTF_CloseFont(police);
            detruireSelections(&selections, i-1);
            return NULL;
        }
    }

    TTF_CloseFont(police);
    return selections;
}



e_code_main afficherMenuNiveau(int * retour_niveau, t_moteur * moteur, niveau_informations_t ** infos_niveaux, int nb_infos)
{
    SDL_Event event;
    SDL_Point souris;

    int sortie = 0; //Code de sortie du menu
    int indice_selection = -1; //Niveau selectionné (-1 si aucun)

    //Initialisation
    t_selection ** selections = initSelections(moteur, infos_niveaux, nb_infos);
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
                    return JEU_QUITTER;
                
                case SDL_KEYDOWN:
                    switch (event.key.keysym.scancode)
                    {
                    case SDL_SCANCODE_ESCAPE :
                        detruireSelections(&selections, nb_infos);
                        return M_PRINCIPAL;
                    default:
                        break;
                    }

                case SDL_MOUSEBUTTONDOWN:
                    if(indice_selection != -1)
                    {
                        *retour_niveau = indice_selection;
                        detruireSelections(&selections, nb_infos);
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
                SDL_SetTextureColorMod(moteur->textures->planete, 255,0,0);
            else
                SDL_SetTextureColorMod(moteur->textures->planete, infos_niveaux[i]->rouge, infos_niveaux[i]->vert, infos_niveaux[i]->bleu);
            renduSelection(moteur, selections[i], moteur->textures->planete, nb_infos);
        }
        indice_selection = indiceSelection(selections, nb_infos, &souris);

        //Rendu
        SDL_RenderPresent(moteur->renderer);
        SDL_RenderClear(moteur->renderer);
    }
    

    detruireSelections(&selections, nb_infos);
    return M_PRINCIPAL;
}
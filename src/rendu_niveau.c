/**
 * \file
 * \brief Module d'affichage d'un niveau
 * 
 * \author Julien Rouaux
 */


#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <moteur.h>
#include <niveau.h>
#include <rendu_niveau.h>


/**
 * \brief Dessine un carré aux coordonnées données.
 * 
 * \param moteur Structure moteur du jeu
 * \param type Apparence du carré
 * \param x Position en largeur de la fenêtre de l'origine de la tile
 * \param y Position en hauteur de la fenêtre de l'origine de la tile
 * 
 * \return 0 si succès, sinon faire un SDL_GetError() pour connaitre l'erreur.
 */
static int dessinerTile(t_moteur * moteur, t_tile_type type, float x, float y)
{
    if(type == AUCUN)
        return 0;
        
    SDL_Rect source; //Partie de du tileset à afficher
    SDL_Rect destination; //Position dans la fenetre où afficher
    
    destination.h = moteur->camera->echelle;
    destination.w = moteur->camera->echelle;
    destination.x = x * moteur->camera->echelle;
    destination.y = y * moteur->camera->echelle;
    
    tileNiveau(&source, type);

    return SDL_RenderCopy(moteur->renderer, moteur->textures->map, &source, &destination);
}

/**
 * \brief Affiche une salle dont l'origine se situe aux coordonnées données.
 * 
 * \param moteur Structure moteur du jeu
 * \param salle Salle à afficher
 * \param x Position en largeur de la fenêtre de l'origine de la salle
 * \param y Position en hauteur de la fenêtre de l'origine de la salle
 * 
 * \return 0 si tout va bien, sinon une valeur négative
 */
static int afficherSalle(t_moteur * moteur, const t_salle * salle, float x, float y)
{
    t_tile_type type = AUCUN;
    int i, j;
    int id_courant = salle->id_salle;

    //Passage des coordonnées à l'échelle du rendu

    //Dessiner sol
    for(i = 0; i < NB_TILE_HAUTEUR; i++)
    {
        for(j = 0; j < NB_TILE_LARGEUR; j++)
        {
            if(dessinerTile(moteur, SOL, x + j, y + i) != 0)
            {
                printf("Erreur lors de l'affichage d'une tile du sol : %s\n", SDL_GetError());
                return -1;
            }
        }
    }
    
    //Dessiner mur haut
    i = -1;
    for(j = -1; j < NB_TILE_LARGEUR+1; j++)
    {
        if(salle->portes[UP] != NULL &&
        id_courant == salle->portes[UP]->id_salle) //Si reliée en haut
            type = AUCUN;
        else
        {
            //Porte haut
            if(j == (NB_TILE_LARGEUR / 2) && salle->portes[UP] != NULL)
                type = PORTE_HAUT;
            //Coins
            else if(j == -1 && salle->portes[LEFT] != NULL && id_courant == salle->portes[LEFT]->id_salle)
                type = AUCUN;
            else if(j == NB_TILE_LARGEUR && salle->portes[RIGHT] != NULL && id_courant == salle->portes[RIGHT]->id_salle)
                type = AUCUN;
            //Mur
            else 
                type = MUR;
                
        }
        if(dessinerTile(moteur, type, x + j, y + i) != 0)
        {
            printf("Erreur lors de l'affichage d'une tile du mur du haut : %s\n", SDL_GetError());
            return -1;
        }
    }
    
    //Dessiner mur bas
    i = NB_TILE_HAUTEUR;
    for(j = -1; j < NB_TILE_LARGEUR+1; j++)
    {
        if(salle->portes[DOWN] != NULL &&
        id_courant == salle->portes[DOWN]->id_salle) //Si reliée en bas
            type = AUCUN;
        else
        {
            //Porte bas
            if(j == (NB_TILE_LARGEUR / 2) && salle->portes[DOWN] != NULL)
                type = PORTE_BAS;
            //Coins
            else if(j == -1 && salle->portes[LEFT] != NULL && id_courant == salle->portes[LEFT]->id_salle)
                type = AUCUN;
            else if(j == NB_TILE_LARGEUR && salle->portes[RIGHT] != NULL && id_courant == salle->portes[RIGHT]->id_salle)
                type = AUCUN;
            //Mur
            else
                type = MUR;
                
        }
        if(dessinerTile(moteur, type, x + j, y + i) != 0)
        {
            printf("Erreur lors de l'affichage d'une tile du mur du bas : %s\n", SDL_GetError());
            return -1;
        }
    }

    //Dessiner mur gauche
    j = -1;
    for(i = -1; i < NB_TILE_HAUTEUR+1; i++)
    {
        if(salle->portes[LEFT] != NULL &&
        id_courant == salle->portes[LEFT]->id_salle) //Si pas reliée à gauche
            type = AUCUN;
        else
        {
            //Porte gauche
            if(i == (NB_TILE_HAUTEUR / 2) && salle->portes[LEFT] != NULL)
                type = PORTE_GAUCHE;
            //Coins
            else if(i == -1 && salle->portes[UP] != NULL && id_courant == salle->portes[UP]->id_salle)
                type = AUCUN;
            else if(i == NB_TILE_HAUTEUR && salle->portes[DOWN] != NULL && id_courant == salle->portes[DOWN]->id_salle)
                type = AUCUN;
            //Mur
            else 
                type = MUR;
                
            if(dessinerTile(moteur, type, x + j, y + i) != 0)
            {
                printf("Erreur lors de l'affichage d'une tile du mur de gauche : %s\n", SDL_GetError());
                return -1;
            }
        }
    }

    //Dessiner mur droite
    j = NB_TILE_LARGEUR;
    for(i = -1; i < NB_TILE_HAUTEUR+1; i++)
    {
        if(salle->portes[RIGHT] != NULL &&
        id_courant == salle->portes[RIGHT]->id_salle) //Si pas reliée à droite
            type = AUCUN;
        else
        {
            //Porte droite
            if(i == (NB_TILE_HAUTEUR / 2) && salle->portes[RIGHT] != NULL)
                type = PORTE_DROITE;
            //Coins
            else if(i == -1 && salle->portes[UP] != NULL && id_courant == salle->portes[UP]->id_salle)
                type = AUCUN;
            else if(i == NB_TILE_HAUTEUR && salle->portes[DOWN] != NULL && id_courant == salle->portes[DOWN]->id_salle)
                type = AUCUN;
            //Mur
            else
                type = MUR;
                
            if(dessinerTile(moteur, type, x + j, y + i) != 0)
            {
                printf("Erreur lors de l'affichage d'une tile du mur de droite : %s\n", SDL_GetError());
                return -1;
            }
        }
    }

    return 0;
}


//Fonction temporaire affichant le niveau
//Elle devra appeler les salles chargées pour les afficher.
//
int afficherNiveau(t_moteur * moteur, t_niveau * niveau, float j_x, float j_y)
{
    int resultat = 0;
    t_camera * camera = moteur->camera;

    for(int i = 0; i < niveau->h; i++)
    {
        for(int j = 0; j < niveau->l; j++)
        {
            if(niveau->salles[i*niveau->l + j] != NULL)
                if(niveau->salles[i*niveau->l +j]->id_salle == niveau->salle_chargee->id_salle)
                {
                    resultat = afficherSalle(moteur, niveau->salles[i*niveau->l + j], j*NB_TILE_LARGEUR - camera->x, i*NB_TILE_HAUTEUR - camera->y);
                    if(resultat != 0)
                        return resultat;
                }
        }
    }
    
    return 0;
}

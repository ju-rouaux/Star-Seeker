/**
 * \file rendu_niveau.c
 * 
 * \brief Module d'affichage d'un niveau
 * 
 * \author Julien Rouaux
 */


#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <moteur.h>
#include <textures.h> //t_tile_type
#include <niveau.h>
#include <rendu_niveau.h>


/**
 * \brief Dessine un carré aux coordonnées données.
 * 
 * \param moteur Structure moteur du jeu
 * \param type Apparence du carré
 * \param x Position en largeur de la fenêtre de l'origine de la tile
 * \param y Position en hauteur de la fenêtre de l'origine de la tile
 * \param collisions Tableau des collisions du niveau
 * \param indice_collision Indice de la prochaine place libre au tableau des collisions
 * 
 * \return 0 si succès, sinon faire un SDL_GetError() pour connaitre l'erreur.
 */
static int dessinerTile(t_moteur * moteur, t_tile_type type, float x, float y, SDL_Rect collisions[], int * indice_collision)
{
    if(type == AUCUN)
        return 0;
        
    SDL_Rect source; //Partie de du tileset à afficher
    SDL_Rect destination; //Position dans la fenetre où afficher
    
    destination.h = moteur->echelle;
    destination.w = moteur->echelle;
    destination.x = x * moteur->echelle;
    destination.y = y * moteur->echelle;
    
    if(type == MUR && collisions != NULL && indice_collision != NULL)
        collisions[(*indice_collision)++] = destination;

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
 * \param collisions Tableau des collisions du niveau
 * \param indice_collision Indice de la prochaine place libre au tableau des collisions
 * 
 * \return 0 si tout va bien, sinon une valeur négative
 */
static int afficherSalle(t_moteur * moteur, const t_salle * salle, float x, float y, SDL_Rect collisions[], int * indice_collision)
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
            if(dessinerTile(moteur, SOL, x + j, y + i, collisions, indice_collision) != 0)
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
        if(dessinerTile(moteur, type, x + j, y + i, collisions, indice_collision) != 0)
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
        if(dessinerTile(moteur, type, x + j, y + i, collisions, indice_collision) != 0)
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
                
            if(dessinerTile(moteur, type, x + j, y + i, collisions, indice_collision) != 0)
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
                
            if(dessinerTile(moteur, type, x + j, y + i, collisions, indice_collision) != 0)
            {
                printf("Erreur lors de l'affichage d'une tile du mur de droite : %s\n", SDL_GetError());
                return -1;
            }
        }
    }

    return 0;
}


//Fonction temporaire affichant le niveau
int afficherNiveau(t_moteur * moteur, float j_x, float j_y)
{
    int resultat = 0;
    t_camera * camera = moteur->camera;
    t_niveau * niveau = moteur->niveau_charge;

    if(niveau->collisions == NULL && niveau->salle_chargee && niveau->salle_chargee->dimensions) //Si les collisions ne sont pas chargées, c'est qu'on a changé de salle
            //Fourchette large = nombre de sous salles * mur gauche et droit + mur haut et bas + coins * 2 car ils peuvent être déssinés 2 fois
            niveau->collisions = malloc(sizeof(SDL_Rect) * niveau->salle_chargee->dimensions->nombre * (NB_TILE_LARGEUR*2 + NB_TILE_HAUTEUR*2 + 4*2) );

    niveau->taille_collisions = 0;

    for(int i = 0; i < niveau->h; i++)
    {
        for(int j = 0; j < niveau->l; j++)
        {
            if(niveau->salles[i*niveau->l + j] != NULL)
                if(niveau->salles[i*niveau->l +j]->id_salle == niveau->salle_chargee->id_salle)
                {
                    resultat = afficherSalle(moteur, niveau->salles[i*niveau->l + j], j*NB_TILE_LARGEUR - camera->x, i*NB_TILE_HAUTEUR - camera->y, niveau->collisions, &(niveau->taille_collisions));
                    if(resultat != 0)
                        return resultat;
                }
        }
    }

    
    return 0;
}

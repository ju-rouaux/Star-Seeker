#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <moteur.h>
#include <niveau.h>
#include <rendu_niveau.h>
#include <textures.h>
#include <camera.h>


/**
 * \brief Dessine un carré aux coordonnées données
 * 
 * \param moteur Structure moteur du jeu
 * \param type Apparence du carré
 * \param x Position en largeur de la fenêtre
 * \param y Position en hauteur de la fenêtre
 * \param taille Taille des cotés des carrés
 * 
 * \return 0 si succès, sinon faire un SDL_GetError() pour connaitre l'erreur.
 */
int dessinerTile(t_moteur * moteur, t_tile_type type, int x, int y, int taille)
{
    if(type == AUCUN)
        return 0;

    SDL_Rect source; //Partie de du tileset à afficher
    SDL_Rect destination; //Position dans la fenetre où afficher
    
    destination.h = taille;
    destination.w = taille;
    destination.x = x;
    destination.y = y;
    
    tileNiveau(&source, type);

    return SDL_RenderCopy(moteur->renderer, moteur->textures->map, &source, &destination);
}

/**
 * \brief Affiche une salle dont l'origine se situe aux coordonnées données
 * 
 * \param moteur Structure moteur du jeu
 * \param salle Salle à afficher
 * \param x Position en largeur de la fenêtre
 * \param y Position en hauteur de la fenêtre
 * \param scale Echelle de rendu du niveau
 */
static int afficherSalle(t_moteur * moteur, t_salle * salle, int x, int y, int scale)
{
    t_tile_type type;
    int id_courant = salle->id_salle;
    int i, j;
    
    //Dessiner sol
    for(i = 0; i < NB_TILE_HAUTEUR; i++)
    {
        for(j = 0; j < NB_TILE_LARGEUR; j++)
        {
            if(dessinerTile(moteur, SOL, (j+x)*scale, (i+y)*scale, scale) != 0)
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
            if(j == (NB_TILE_LARGEUR / 2) && salle->portes[UP] != NULL) //Porte haut
                type = PORTE_HAUT;
            else //Mur
                type = MUR;
                
        }
        if(dessinerTile(moteur, type, (j+x)*scale, (i+y)*scale, scale) != 0)
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
            if(j == (NB_TILE_LARGEUR / 2) && salle->portes[DOWN] != NULL) //Porte bas
                type = PORTE_BAS;
            else //Mur
                type = MUR;
                
        }
        if(dessinerTile(moteur, type, (j+x)*scale, (i+y)*scale, scale) != 0)
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
            if(i == (NB_TILE_HAUTEUR / 2) && salle->portes[LEFT] != NULL) //Porte gauche
                type = PORTE_GAUCHE;
            else //Mur
                type = MUR;
                
            if(dessinerTile(moteur, type, (j+x)*scale, (i+y)*scale, scale) != 0)
            {
                printf("Erreur lors de l'affichage d'une tile du mur du bas : %s\n", SDL_GetError());
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
            if(i == (NB_TILE_HAUTEUR / 2) && salle->portes[RIGHT] != NULL) //Porte droite
                type = PORTE_DROITE;
            else //Mur
                type = MUR;
                
            if(dessinerTile(moteur, type, (j+x)*scale, (i+y)*scale, scale) != 0)
            {
                printf("Erreur lors de l'affichage d'une tile du mur du bas : %s\n", SDL_GetError());
                return -1;
            }
        }
    }

    return 0;

    //ANCIEN RENDU
    /*
    //Afficher sol
    for(int i = -1; i < NB_TILE_HAUTEUR+1; i++)
    {
        for(int j = -1; j < NB_TILE_LARGEUR+1; j++)
        {
            if(i == -1) //Mur du haut
            {
                if(salle->portes[UP] != NULL &&
                id_courant == salle->portes[UP]->id_salle &&
                j != -1 && j != NB_TILE_LARGEUR+1) //Reliée en haut
                    type = AUCUN;
                else
                {
                    if(j == (NB_TILE_LARGEUR+2) / 2 && salle->portes[UP] != NULL) //Porte haut
                        type = PORTE_HAUT;
                    else //Mur
                        type = MUR;
                }
            }
            else if(i == NB_TILE_HAUTEUR+1) //Mur du bas
            {
                if(salle->portes[DOWN] != NULL &&
                id_courant == salle->portes[DOWN]->id_salle &&
                j != -1 && j != NB_TILE_LARGEUR+1) //Reliée en haut
                    type = AUCUN;
                else
                {
                    if(j == (NB_TILE_LARGEUR+2) / 2 && salle->portes[DOWN] != NULL) //Porte bas
                        type = PORTE_BAS;
                    else //Mur
                        type = MUR;
                }
            }
            else if(j == -1) //Mur de gauche
            {
                if(salle->portes[LEFT] != NULL &&
                id_courant == salle->portes[LEFT]->id_salle) //Reliée à gauche
                    type = AUCUN;
                else
                {
                    if(i == (NB_TILE_HAUTEUR+2) / 2 && salle->portes[LEFT] != NULL) //Porte gauche
                        type = PORTE_GAUCHE;
                    else //Mur
                        type = MUR;
                }
            }
            else if(j == NB_TILE_LARGEUR+1) //Mur de droite
            {
                if(salle->portes[RIGHT] != NULL &&
                id_courant == salle->portes[RIGHT]->id_salle) //Reliée à gauche
                    type = AUCUN;
                else
                {
                    if(i == (NB_TILE_HAUTEUR+2) / 2 && salle->portes[RIGHT] != NULL) //Porte gauche
                        type = PORTE_DROITE;
                    else //Mur
                        type = MUR;
                }
            }
            else
                type = SOL;
            if(type != AUCUN)
                if(dessinerTile(moteur, type, (j+x)*scale, (i+y)*scale, scale) != 0)
                {
                    printf("Erreur lors de l'affichage d'une tile : %s\n", SDL_GetError());
                    return -1;
                } 
        }
    }
    */
}

//Fonction temporaire affichant l'entièreté du niveau.
//Elle devra appeler les salles chargées pour les afficher.
int afficherNiveau(t_moteur * moteur, t_niveau * niveau, t_camera * camera)
{
    int resultat = 0;
    int id_desire1 = 24;
    int id_desire2 = 25;

    updateScale(moteur->window, camera);
    



    //Calculer camera et ainsi calculer coordonnées origine du niveau relatives caméra
    /*for(int i = 0; i < niveau->h; i++)
    {
        for(int j = 0; j < niveau->l; j++)
        {
            if(niveau->salles[i*niveau->l + j] != NULL)
                if(niveau->salles[i*niveau->l +j]->id_salle == id_desire)
                    resultat = afficherSalle(moteur, niveau->salles[i*niveau->l + j], j*NB_TILE_LARGEUR, i*NB_TILE_HAUTEUR, 6);
        }
    }
    */
    return 0;
}

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

    //Afficher sol
    for(int i = 0; i < NB_TILE_HAUTEUR; i++)
    {
        for(int j = 0; j < NB_TILE_LARGEUR; j++)
        {
            if(i == 0) //Mur du haut
            {
                if(salle->portes[UP] != NULL &&
                id_courant == salle->portes[UP]->id_salle &&
                j != 0 && j != NB_TILE_LARGEUR-1) //Reliée en haut
                    type = SOL;
                else
                {
                    if(j == (NB_TILE_LARGEUR / 2) && salle->portes[UP] != NULL) //Porte haut
                        type = PORTE_HAUT;
                    else //Mur
                        type = MUR;
                }
            }
            else if(i == NB_TILE_HAUTEUR-1) //Mur du bas
            {
                if(salle->portes[DOWN] != NULL &&
                id_courant == salle->portes[DOWN]->id_salle &&
                j != 0 && j != NB_TILE_LARGEUR-1) //Reliée en haut
                    type = SOL;
                else
                {
                    if(j == (NB_TILE_LARGEUR / 2) && salle->portes[DOWN] != NULL) //Porte bas
                        type = PORTE_BAS;
                    else //Mur
                        type = MUR;
                }
            }
            else if(j == 0) //Mur de gauche
            {
                if(salle->portes[LEFT] != NULL &&
                id_courant == salle->portes[LEFT]->id_salle) //Reliée à gauche
                    type = SOL;
                else
                {
                    if(i == (NB_TILE_HAUTEUR / 2) && salle->portes[LEFT] != NULL) //Porte gauche
                        type = PORTE_GAUCHE;
                    else //Mur
                        type = MUR;
                }
            }
            else if(j == NB_TILE_LARGEUR-1) //Mur de droite
            {
                if(salle->portes[RIGHT] != NULL &&
                id_courant == salle->portes[RIGHT]->id_salle) //Reliée à gauche
                    type = SOL;
                else
                {
                    if(i == (NB_TILE_HAUTEUR / 2) && salle->portes[RIGHT] != NULL) //Porte gauche
                        type = PORTE_DROITE;
                    else //Mur
                        type = MUR;
                }
            }
            else
                type = SOL;

            if(dessinerTile(moteur, type, (j+x)*scale, (i+y)*scale, scale) != 0)
            {
                printf("Erreur lors de l'affichage d'une tile : %s\n", SDL_GetError());
                return -1;
            } 
        }
    }

    return 0;
}

//Fonction temporaire affichant l'entièreté du niveau.
//Elle devra appeler les salles chargées pour les afficher.
int afficherNiveau(t_moteur * moteur, t_niveau * niveau)
{
    int resultat = 0;
    //Calculer camera et ainsi calculer coordonnées origine du niveau relatives caméra
    for(int i = 0; i < niveau->h; i++)
    {
        for(int j = 0; j < niveau->l; j++)
        {
            if(niveau->salles[i*niveau->l + j] != NULL)
                resultat = afficherSalle(moteur, niveau->salles[i*niveau->l + j], j*NB_TILE_LARGEUR, i*NB_TILE_HAUTEUR, 4);
            
            
        }
    }
    return 0;
}

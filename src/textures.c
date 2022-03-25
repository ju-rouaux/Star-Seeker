/**
 * \file textures.c
 * 
 * \brief Module de chargement de textures. Propose aussi quelques outils relatifs aux
 * terxtures.
 * 
 * \author Julien Rouaux
 */


#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <textures.h>


/**
 * \brief Charge les textures du jeu
 * 
 * \param renderer Pointeur du renderer de la fenêtre.
 * 
 * \return Le pointeur de la structure contenant les références à toutes 
 * les textures, NULL si echec.
 */
t_textures * chargerTextures(SDL_Renderer * renderer)
{
    SDL_Surface * surface = NULL;

    t_textures * textures = malloc(sizeof(t_textures));
    if(textures == NULL)
    {
        printf("Impossible d'allouer la mémoire pour t_textures\n");
        return NULL;
    }
    textures->map = NULL;
    textures->player = NULL;

    //Map
    surface = SDL_LoadBMP("./assets/img/tileset_map.bmp");
    if(surface == NULL)
    {
        printf("Impossible de charger la surface tileset_map.bmp : %s\n", SDL_GetError());
        free(textures);
        return NULL;
    }
    textures->map = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    if(textures->map == NULL)
    {
        printf("Impossible de charger la texture de tileset_map.bmp : %s\n", SDL_GetError());
        free(textures);
        return NULL;
    }
    surface = NULL;



    //Player
    surface = SDL_LoadBMP("./assets/img/personnage.bmp");
    if(surface == NULL)
    {
        printf("Impossible de charger la surface personnage.bmp : %s\n", SDL_GetError());
        return NULL;
    }
    textures->player = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    if(textures->player == NULL)
    {
        printf("Impossible de charger la texture de personnage.bmp : %s\n", SDL_GetError());
        return NULL;
    }
    surface = NULL;

    //Projectiles
    surface = SDL_LoadBMP("./assets/img/projectiles.bmp");
    if(surface == NULL)
    {
        printf("Impossible de charger la surface projectiles.bmp : %s\n", SDL_GetError());
        return NULL;
    }
    textures->projectiles = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    if(textures->projectiles == NULL)
    {
        printf("Impossible de charger la texture de projectiles.bmp : %s\n", SDL_GetError());
        return NULL;
    }
    surface = NULL;

    //Corps monstres
    surface = SDL_LoadBMP("./assets/img/monstres_haut.bmp");
    if(surface == NULL)
    {
        printf("Impossible de charger la surface monstres_haut.bmp : %s\n", SDL_GetError());
        return NULL;
    }
    textures->monstres_haut = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    if(textures->monstres_haut == NULL)
    {
        printf("Impossible de charger la texture de monstres_haut.bmp : %s\n", SDL_GetError());
        return NULL;
    }
    surface = NULL;

    //Pattes monstres
    surface = SDL_LoadBMP("./assets/img/monstres_bas.bmp");
    if(surface == NULL)
    {
        printf("Impossible de charger la surface monstres_bas.bmp : %s\n", SDL_GetError());
        return NULL;
    }
    textures->monstres_bas = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    if(textures->monstres_bas == NULL)
    {
        printf("Impossible de charger la texture de monstres_bas.bmp : %s\n", SDL_GetError());
        return NULL;
    }
    surface = NULL;

    //Overlay
    surface = SDL_LoadBMP("./assets/img/overlay.bmp");
    if(surface == NULL)
    {
        printf("Impossible de charger la surface overlay.bmp : %s\n", SDL_GetError());
        return NULL;
    }
    textures->overlay = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    if(textures->overlay == NULL)
    {
        printf("Impossible de charger la texture de overlay.bmp : %s\n", SDL_GetError());
        return NULL;
    }
    surface = NULL;

    //Particules
    surface = SDL_LoadBMP("./assets/img/particules.bmp");
    if(surface == NULL)
    {
        printf("Impossible de charger la surface particules.bmp : %s\n", SDL_GetError());
        return NULL;
    }
    textures->particules = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    if(textures->particules == NULL)
    {
        printf("Impossible de charger la texture de particules.bmp : %s\n", SDL_GetError());
        return NULL;
    }
    surface = NULL;

    return textures;
}


/**
 * \brief Libère la mémoire allouée pour les textures et mets son 
 * pointeur à NULL.
 * 
 * \param textures La structure des textures du jeu.
 */
void detruireTextures(t_textures ** textures)
{
    if(*textures != NULL)
    {
        if((*textures)->map != NULL)
            SDL_DestroyTexture((*textures)->map);
        if((*textures)->player != NULL)
            SDL_DestroyTexture((*textures)->player);
        if((*textures)->projectiles != NULL)
            SDL_DestroyTexture((*textures)->projectiles);
        if((*textures)->monstres_bas != NULL)
            SDL_DestroyTexture((*textures)->monstres_bas);
        if((*textures)->monstres_haut != NULL)
            SDL_DestroyTexture((*textures)->monstres_haut);
        free(*textures);
    }
    *textures = NULL;
}

/**
 * \brief Outil permettant de découper une tileset et récupérer une partie de la texture.
 * 
 * \param rectangle Rectangle où stocker le résultat de calcul
 * \param x Position en x de la tile désirée
 * \param y Position en y de la tile désirée
 */
void splitTexture(SDL_Rect * rectangle, int x, int y, int tailleX, int tailleY, int decalageX, int decalageY)
{
    rectangle->x = x * decalageX;
    rectangle->y = y * decalageY;
    rectangle->h = tailleX;
    rectangle->w = tailleY;
}


/**
 * \brief Permet de récupérer la bonne partie du tileset de niveau en fonction
 * du type de tile désiré.
 * 
 * \param rectangle Rectangle où stocker le résultat de calcul
 * \param type Type de tile désiré
 */
void tileNiveau(SDL_Rect * rectangle, t_tile_type type)
{
    switch (type)
    {
    case SOL:
        splitTexture(rectangle, 0,0, 16,16, 16,16);
        break;
    case MUR:
        splitTexture(rectangle, 1,0, 16,16, 16,16);
        break;
    case PORTE_HAUT:
        splitTexture(rectangle, 2,0, 16,16, 16,16);
        break;
    case PORTE_GAUCHE:
        splitTexture(rectangle, 3,0, 16,16, 16,16);
        break;
    case PORTE_BAS:
        splitTexture(rectangle, 4,0, 16,16, 16,16);
        break;
    case PORTE_DROITE:
        splitTexture(rectangle, 5,0, 16,16, 16,16);
        break;
    default: //texture par défaut
        splitTexture(rectangle, 0,0, 16,16, 16,16);
        break;
    }
}
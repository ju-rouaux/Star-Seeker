/**
 * \file textures.h
 * 
 * \brief Module de chargement de textures. Propose aussi quelques outils relatifs aux
 * terxtures.
 * 
 * \author Julien Rouaux
 */

#ifndef _JEU_TEXTURES_
#define _JEU_TEXTURES_

#include <SDL2/SDL.h>

#define TAILLE_TILE 16


/**
 * \enum t_tile_type
 * \brief Identifiants des tiles d'un niveau
 */
typedef enum
{
    AUCUN, SOL, MUR, PORTE_BAS, PORTE_DROITE, PORTE_HAUT, PORTE_GAUCHE
} t_tile_type;



/**
 * \struct t_textures
 * \brief Contient toutes les textures du jeu
 */
typedef struct
{
    SDL_Texture * map;
    SDL_Texture * player;
    SDL_Texture * projectiles;
    SDL_Texture * monstres_haut;
    SDL_Texture * monstres_bas;
    SDL_Texture * overlay;
    SDL_Texture * particules;
    SDL_Texture * planete;
    SDL_Texture * collectibles;

} t_textures;


t_textures * chargerTextures(SDL_Renderer * renderer);
void detruireTextures(t_textures ** textures);
void splitTexture(SDL_Rect * rectangle, int x, int y, int tailleX, int tailleY, int decalageX, int decalageY);
void tileNiveau(SDL_Rect * rectangle, t_tile_type type);


#endif //_JEU_TEXTURES_
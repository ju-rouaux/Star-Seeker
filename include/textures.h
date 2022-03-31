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
    SDL_Texture * map;/**<Le tileset pour la map*/
    SDL_Texture * player;/**<Le tileset pour le joueur*/
    SDL_Texture * projectiles;/**<Le tileset pour un projectile*/
    SDL_Texture * monstres_haut;/**<Le tileset pour la partie haute du monstre*/
    SDL_Texture * monstres_bas;/**<Le tileset pour la partie basse du monstre*/
    SDL_Texture * overlay;/**<Le tileset pour l'overlay*/
    SDL_Texture * particules;/**<Le tileset pour les particules*/
    SDL_Texture * planete;/**<Le tileset pour les planetes*/
    SDL_Texture * collectibles;/**<Le tileset pour les collectibles*/

} t_textures;


t_textures * chargerTextures(SDL_Renderer * renderer);
void detruireTextures(t_textures ** textures);
void splitTexture(SDL_Rect * rectangle, int x, int y, int tailleX, int tailleY, int decalageX, int decalageY);
void tileNiveau(SDL_Rect * rectangle, t_tile_type type);


#endif //_JEU_TEXTURES_
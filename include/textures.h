#ifndef _JEU_TEXTURES_
#define _JEU_TEXTURES_

#include <SDL2/SDL.h>

#define TAILLE_TILE 16

/*
    CE FICHIER CONTIENT AUSSI LES ENUMERATIONS NECESSAIRES
    A L'IDENTIFICATION D'UNE TILE DANS UN TILESET
*/
typedef enum
{
    SOL, MUR, PORTE_BAS, PORTE_DROITE, PORTE_HAUT, PORTE_GAUCHE
} t_tile_type;

/**
 * \struct t_textures
 * \brief Contient toutes les textures du jeu
 */
typedef struct
{
    SDL_Texture * map;
    SDL_Texture * player;
} t_textures;

t_textures * chargerTextures(SDL_Renderer * renderer);
void detruireTextures(t_textures ** textures);
void splitTexture(SDL_Rect * rectangle, int x, int y);
void tileNiveau(SDL_Rect * rectangle, t_tile_type type);

#endif //_JEU_TEXTURES_
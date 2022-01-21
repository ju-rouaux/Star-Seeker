#ifndef _JEU_TEXTURES_
#define _JEU_TEXTURES_

#include <SDL2/SDL.h>

/*
    CE FICHIER CONTIENDRA AUSSI LES ENUMERATIONS NECESSAIRES
    A L'IDENTIFICATION D'UNE TILE DANS UN TILESET
*/


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

#endif //_JEU_TEXTURES_
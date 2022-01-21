#ifndef _JEU_TEXTURES_
#define _JEU_TEXTURES_

#include <SDL2/SDL.h>

typedef struct
{
    SDL_Texture * map;
    SDL_Texture * player;
} t_textures;

t_textures * chargerTextures(SDL_Renderer * renderer);
void detruireTextures(t_textures ** textures);

#endif //_JEU_TEXTURES_
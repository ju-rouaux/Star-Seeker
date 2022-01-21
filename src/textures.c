#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <textures.h>

//REtourne NULL si echec
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
    surface = SDL_LoadBMP("./img/tileset_map.bmp");
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


/*
    //Player
    surface = SDL_LoadBMP("./img/player.bmp");
    if(surface == NULL)
    {
        printf("Impossible de charger la surface player.bmp : %s\n", SDL_GetError());
        return NULL;
    }
    textures->map = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    if(textures->map == NULL)
    {
        printf("Impossible de charger la texture de player.bmp : %s\n", SDL_GetError());
        return NULL;
    }
    surface = NULL;

*/

    return textures;
}

void detruireTextures(t_textures ** textures)
{
    if(*textures != NULL)
    {
        if((*textures)->map != NULL)
            SDL_DestroyTexture((*textures)->map);
        if((*textures)->player != NULL)
            SDL_DestroyTexture((*textures)->player);
        free(*textures);
    }
    *textures = NULL;
}
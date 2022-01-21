#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <window.h>
#include <event.h>
#include <player.h>
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              
int main(int argc, char * argv[])
{
    SDL_Window * window = NULL;
    SDL_Renderer * renderer = NULL;
    SDL_Surface * image = NULL;
    
    if(SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        printf("Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    creerFenetreEtRendu(&window, &renderer);

    SDL_RWops *rwop;
    rwop=SDL_RWFromFile("./img/personnage.png", "rb");
    image=IMG_LoadPNG_RW(rwop);

    SDL_Texture *image_tex = SDL_CreateTextureFromSurface(renderer, image);
    if(!image_tex){
        fprintf(stderr, "Erreur a la creation du rendu de l'image : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    SDL_FreeSurface(image); /* on a la texture, plus besoin de l'image */

    move * player = malloc(sizeof(move));

    while(handleEvents() != 1){
        move_player(player);
         
    }
    free(player);
    detruireFenetreEtRendu(&window, &renderer);

    SDL_Quit();
    return 0;
 }

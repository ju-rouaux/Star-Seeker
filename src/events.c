#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

/*



*/

void handleEvents(){
    const char  * key_code = malloc(sizeof(char));
    const char * key_name= malloc(sizeof(char));

    
    SDL_Event event;

    while (SDL_PollEvent(&event)) {

    switch (event.type) {
        case SDL_MOUSEBUTTONDOWN : printf("SDL_MOUSEBUTTONDOWN");;
        case SDL_MOUSEBUTTONUP : printf("SDL_MOUSEBUTTONUP");;
        case SDL_KEYDOWN : printf("SDL_KEYDOWN");
                key_code = SDL_GetScancodeName(event.key.keysym.scancode),
                key_name = SDL_GetKeyName(event.key.keysym.sym),
                printf("La cle %s : %s a été appuyée", key_name,key_code);
        case SDL_KEYUP : printf("SDL_KEYDOWN");
                key_code = SDL_GetScancodeName(event.key.keysym.scancode),
                key_name = SDL_GetKeyName(event.key.keysym.sym),
                printf("La cle %s : %s a été relachée", key_name,key_code);

        case SDL_MOUSEMOTION : printf("Mouse has moved");;
            
        

    }

    }
    key_code = NULL;
    key_name = NULL;
}
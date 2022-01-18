#include <stdio.h>
#include <SDL2/SDL.h>

/*



*/

void handleEvents(){
    
    SDL_Event event;
    while (SDL_PollEvent(&event)) {

    switch (event.type) {
        case SDL_MOUSEBUTTONDOWN : printf("SDL_MOUSEBUTTONDOWN");;
        case SDL_MOUSEBUTTONUP : printf("SDL_MOUSEBUTTONUP");;
        case SDL_KEYDOWN : printf("SDL_SDL_KEYDOWN");switch(event->key.keysym.scancode)
                SDL_GetScancodeName(event->key.keysym.scancode),
                SDL_GetKeyName(event->key.keysym.sym));
            switch(event->key.keysym.scancode)
                SDL_GetScancodeName(event->key.keysym.scancode),
                SDL_GetKeyName(event->key.keysym.sym));
        case SDL_KEYUP : printf("SDL_SDL_KEYDOWN");switch(event->key.keysym.scancode)
                SDL_GetScancodeName(event->key.keysym.scancode),
                SDL_GetKeyName(event->key.keysym.sym));
            switch(event->key.keysym.scancode)
                SDL_GetScancodeName(event->key.keysym.scancode),
                SDL_GetKeyName(event->key.keysym.sym));
        

    }

    }
}
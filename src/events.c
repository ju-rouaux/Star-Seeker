#include <stdio.h>

#include <stdlib.h>

#include <SDL2/SDL.h>

/*



*/

int handleEvents() {
  const char * key_code;
  const char * key_name;

  SDL_Event event;

  while (SDL_PollEvent( & event)) {


    switch (event.type) {

        //gestion de la souris
    case SDL_MOUSEBUTTONDOWN:
      printf("SDL_MOUSEBUTTONDOWN");
      break;
    case SDL_MOUSEBUTTONUP:
      printf("SDL_MOUSEBUTTONUP");
      break;
    case SDL_MOUSEMOTION:
      printf("Mouse has moved");
      break;

    //gestion du clavier
    case SDL_KEYDOWN:
      printf("SDL_KEYDOWN"),
      key_code = SDL_GetScancodeName(event.key.keysym.scancode),
        key_name = SDL_GetKeyName(event.key.keysym.sym),
        printf("La cle %s : %s a été appuyée", key_name, key_code);break; 
    case SDL_KEYUP:
      printf("SDL_KEYDOWN"),
      key_code = SDL_GetScancodeName(event.key.keysym.scancode),
        key_name = SDL_GetKeyName(event.key.keysym.sym),
        printf("La cle %s : %s a été relachée", key_name, key_code);break;
        
    
    
    //gestion de la fenetre

    case SDL_WINDOWEVENT:
        switch(event.window.event){
            case SDL_WINDOWEVENT_CLOSE : return 1; break;
            case SDL_WINDOWEVENT_HIDDEN : printf("fenetre cachée");break;
            case SDL_WINDOWEVENT_MAXIMIZED :printf("fenetre agrandie");break;
            case SDL_WINDOWEVENT_MINIMIZED :printf("fenetre diminuée");break;
            case SDL_WINDOWEVENT_MOVED : printf("Fenetre deplacée");break;
            case SDL_WINDOWEVENT_SHOWN : printf("Fenetre montrée");break;
            case SDL_WINDOWEVENT_LEAVE : printf("La souris a quitté la fenetre");break;

        }
    }
  }
}

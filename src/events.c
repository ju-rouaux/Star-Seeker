#include <stdio.h>

#include <stdlib.h>

#include <SDL2/SDL.h>

/*



*/

int handleEvents() {
  const char * key_code;
  const char * key_name;

  int q_down = 0;
  int ctrl_down = 0;

  SDL_Event event;

  while (SDL_PollEvent( & event)) {

    switch (event.type) {
    case SDL_MOUSEBUTTONDOWN:
      printf("SDL_MOUSEBUTTONDOWN");
      break;
    case SDL_MOUSEBUTTONUP:
      printf("SDL_MOUSEBUTTONUP");
      break;
    case SDL_KEYDOWN:
      printf("SDL_KEYDOWN"),
      key_code = SDL_GetScancodeName(event.key.keysym.scancode),
        key_name = SDL_GetKeyName(event.key.keysym.sym),
        printf("La cle %s : %s a été appuyée", key_name, key_code);
        switch (event.key.keysym.sym) {
        case SDLK_q:
          q_down = 1;
          break;
        case SDLK_LCTRL:
          ctrl_down = 1;
          break;;
        };
      break;
        
    case SDL_KEYUP:
      printf("SDL_KEYDOWN"),
      key_code = SDL_GetScancodeName(event.key.keysym.scancode),
        key_name = SDL_GetKeyName(event.key.keysym.sym),
        printf("La cle %s : %s a été relachée", key_name, key_code);
        switch (event.key.keysym.sym) {
      case SDLK_q:
        q_down = 0;
        break;
      case SDLK_LCTRL:
        ctrl_down = 0;
        break;
      };break;
        
    case SDL_MOUSEMOTION:
      printf("Mouse has moved");
      break;
    }

  if (q_down && ctrl_down)
    return 1;
  }
}

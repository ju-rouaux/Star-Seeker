#include <stdio.h>

#include <stdlib.h>

#include "../include/SDL2/SDL.h"


int handleEvents() {

  const char * key_code, * key_name;
  int mouse_x, mouse_y;
  int scrolling;

  SDL_Event event;

  while (SDL_PollEvent( & event)) {

    switch (event.type) {

      //gestion de la souris
    case SDL_MOUSEBUTTONDOWN:
      switch (event.button.button) {
      case SDL_BUTTON_LEFT:
        printf("\nMouse left button pressed");
        break;
      case SDL_BUTTON_MIDDLE:
        printf("\nMouse scroll button pressed");
        break;
      case SDL_BUTTON_RIGHT:
        printf("\nMouse right button pressed");
        break;
      default:
        printf("\nMouse got unknown event");
        break;
      };
      switch (event.button.clicks) {
      case 1:
        printf("\nSimple click");
        break;
      case 2:
        printf("\nDouble click");
        break;
      default:
        printf("\nClicked too many times hahaha");
        break;
      };
      break;
      printf("\nSDL_MOUSEBUTTONDOWN");
      break;
    case SDL_MOUSEBUTTONUP:
      switch (event.button.button) {
      case SDL_BUTTON_LEFT:
        printf("\nMouse left button released");
        break;
      case SDL_BUTTON_MIDDLE:
        printf("\nMouse scroll button released");
        break;
      case SDL_BUTTON_RIGHT:
        printf("\nMouse right button released");
        break;
      default:
        printf("\nMouse got unknown event");
        break;
      };
      printf("\nSDL_MOUSEBUTTONUP");
      break;
    case SDL_MOUSEMOTION:
      mouse_x = event.button.x, mouse_y = event.button.y;
      printf("\nMouse has moved  : Mouse coordinates relative to window : x = %d, y = %d", mouse_x, mouse_y);
      break;
    case SDL_MOUSEWHEEL:
    scrolling = event.wheel.y;
      if(scrolling < 0)
        printf("\nScrolling down");
      if(scrolling > 0)
        printf("\nScrolling up");
      
      break;

      //gestion du clavier
    case SDL_KEYDOWN://touche appuyée
      printf("\nKey pressed"), 
        key_code = SDL_GetScancodeName(event.key.keysym.scancode),
        key_name = SDL_GetKeyName(event.key.keysym.sym),
        printf("\nKey %s : %s has been pressed", key_name, key_code);
      break;
    case SDL_KEYUP://touche relachée
      printf("\nKey released"),
        key_code = SDL_GetScancodeName(event.key.keysym.scancode),
        key_name = SDL_GetKeyName(event.key.keysym.sym),
        printf("\nKey %s : %s has been released", key_name, key_code);// key_name touche correspondant clavier azerty | key_code = clavier qwerty
      break;

      //gestion de la fenetre

    case SDL_WINDOWEVENT:
      switch (event.window.event) {
      case SDL_WINDOWEVENT_CLOSE:
        return 1;
        break;
      case SDL_WINDOWEVENT_SHOWN:
        printf("\nWindow shown");
        break;
      case SDL_WINDOWEVENT_HIDDEN:
        printf("\nWindow hidden");
        break;
      case SDL_WINDOWEVENT_MAXIMIZED:
        printf("\nWindow maximized");
        break;
      case SDL_WINDOWEVENT_MINIMIZED:
        printf("\nWindow minimized");
        break;
      case SDL_WINDOWEVENT_MOVED:
        printf("\nWindow moved");
        break;
      case SDL_WINDOWEVENT_ENTER:
        printf("\nMouse entered window");
        break;
      case SDL_WINDOWEVENT_LEAVE:
        printf("\nMouse left window");
        break;
      }
    }
  }
  return 0;
}
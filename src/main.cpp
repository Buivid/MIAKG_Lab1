#include "draw.h"

#include <SDL.h>
#include <stdio.h>
#include <string>
#include <cassert>
#include <stdio.h>

bool init();
void close();

SDL_Window *gWindow = NULL;
SDL_Renderer *gRenderer = NULL;
SDL_Texture *gTexture = NULL;
SDL_Surface *loadedSurface = NULL;

bool init()
{
  bool success = true;
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
    success = false;
  } else {
    gWindow = SDL_CreateWindow("AOKG Lab 1", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWindow == NULL) {
      printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
      success = false;
    } else {
      gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_SOFTWARE);
      if (gRenderer == NULL) {
        printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
        success = false;
      } else {
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
      }
    }
  }
  return success;
}

void close()
{
  SDL_DestroyTexture(gTexture);
  gTexture = NULL;
  SDL_DestroyRenderer(gRenderer);
  SDL_DestroyWindow(gWindow);
  gWindow = NULL;
  gRenderer = NULL;
  SDL_Quit();
}

int main(int argc, char *argv[])
{
  if (!init()) {
    printf("Failed to initialize!\n");
  } else {
    loadedSurface = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32,
      0x00FF0000,// R
      0x0000FF00,// G
      0x000000FF,// B
      0x00000000);// alpha

    gTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);

    if (NULL == gTexture) {
      printf("Failed to load media!\n");
    } else {
      bool quit = false;
      Drawing graphic(SCREEN_WIDTH/2,SCREEN_HEIGHT/2);
      int a = SCREEN_WIDTH/4;
      float t = 5;
      // glm:: vec3 object_syst_coord = {SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 1.0f};
      // glm:: vec3 observer_syst_coord = {SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 1.0f};
      SDL_Event e;

      while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
          if (SDL_QUIT == e.type) {
            quit = true;
          }
          if (SDL_KEYDOWN == e.type) {
            switch (e.key.keysym.scancode) {
            case SDL_SCANCODE_KP_PLUS:
              printf("SDL_SCANCODE_KP_PLUS have been presssed\n");
              graphic.scale_koef+= 0.1;
              break;
            case SDL_SCANCODE_KP_MINUS:
              printf("SDL_SCANCODE_KP_MINUS have been presssed\n");
              if(graphic.scale_koef>0.1)
                graphic.scale_koef -= 0.1;
              break;
            case SDL_SCANCODE_DOWN:
              printf("SDL_SCANCODE_DOWN have been presssed\n");
              graphic.Ty-=5;

              break;
            case SDL_SCANCODE_UP:
              printf("SDL_SCANCODE_UP have been presssed\n");
              graphic.Ty+=5;

              break;
            case SDL_SCANCODE_LEFT:
              printf("SDL_SCANCODE_LEFT have been presssed\n");
              graphic.Tx+=5;
              break;
            case SDL_SCANCODE_RIGHT:
              printf("SDL_SCANCODE_RIGTH have been presssed\n");
              graphic.Tx-=5;
              break;
            case SDL_SCANCODE_KP_1:
              printf("SDL_SCANCODE_1 have been presssed\n");
              graphic.phi+=10;
              break;
            case SDL_SCANCODE_KP_2:
              printf("SDL_SCANCODE_2 have been presssed\n");
              graphic.phi-=10;
              break;
            case SDL_SCANCODE_A:
              printf("SDL_SCANCODE_A have been presssed\n");
              a+= 10;

             break;
            case SDL_SCANCODE_Q:
               int x, y;
              SDL_GetMouseState(&x,&y);
              printf("%d %d \n",x,y);
              graphic.get_observer_coord(x,y);





             break;
            case SDL_SCANCODE_S:
              printf("SDL_SCANCODE_S have been presssed\n");
              a-= 10;
              break;
            case SDL_SCANCODE_T:
              printf("SDL_SCANCODE_T have been presssed\n");
              t+= 1;
              break;
            case SDL_SCANCODE_Y:
              printf("SDL_SCANCODE_Y have been presssed\n");
              t-= 1;
              break;

            case SDL_SCANCODE_ESCAPE:
              quit = true;
              break;
            default:
              break;
            }
          }

        }
        SDL_RenderClear(gRenderer);

        draw(loadedSurface, graphic, a, t);

        SDL_UpdateTexture(gTexture, NULL, loadedSurface->pixels, loadedSurface->pitch);
        SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);
        SDL_RenderPresent(gRenderer);
      }
    }
  }
  close();
  return 0;
}

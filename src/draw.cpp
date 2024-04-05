#include "draw.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/ext.hpp>


#define RGB32(r, g, b) static_cast<uint32_t>((((static_cast<uint32_t>(b) << 8) | g) << 8) | r)



void put_pixel32(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
  assert(NULL != surface);
  assert(x < SCREEN_WIDTH);
  assert(y < SCREEN_HEIGHT);

  Uint32 *pixels = (Uint32 *)surface->pixels;
  pixels[(y * surface->w) + x] = pixel;

}


Uint32 get_pixel32(SDL_Surface *surface, int x, int y)
{
  assert(NULL != surface);
  assert(x < SCREEN_WIDTH);
  assert(y < SCREEN_HEIGHT);

  Uint32 *pixels = (Uint32 *)surface->pixels;
  return pixels[(y * surface->w) + x];
}

void draw(SDL_Surface *s, Drawing graphic, int a, float par_t)
{
  // glm::vec4 Position = glm::vec4(glm::vec3(0.0f), 1.0f);
  // glm::mat4 Model = glm::translate(    glm::mat4(1.0f), glm::vec3(1.0f));
  // glm::vec4 Transformed = Model * Position;

  Transform p2;
  p2.phi=0;
  p2.scale_koef=1;
  p2.Tx=SCREEN_WIDTH/2;
  p2.Ty=SCREEN_HEIGHT/2;
  glm::vec3 axes;

  for(int i =0; i<SCREEN_WIDTH; i++)
  {
    for(int j = 0; j < SCREEN_HEIGHT; j++)
    {
       put_pixel32(s, i, j, 0x00FFFFFF);
    }
  }

  for(int i =-SCREEN_WIDTH, j = 0; i<SCREEN_WIDTH; i++)
  {
    axes = p2.transform(i,j);
     if(axes.x<0||axes.x>=SCREEN_WIDTH||axes.y>=SCREEN_HEIGHT||axes.y<0)
      continue;
      else
        put_pixel32(s, axes.x, axes.y, 0x00000000);
  }
  for(int j = -SCREEN_HEIGHT, i = 0; j < SCREEN_HEIGHT; j++)
  {
    axes = p2.transform(i,j);
     if(axes.x<0||axes.x>=SCREEN_WIDTH||axes.y>=SCREEN_HEIGHT||axes.y<0)
      continue;
      else
        put_pixel32(s, axes.x, axes.y, 0x00000000);
  }


  // Ваш код
  // ...

  glm::vec3 vector;
  int x_rounded, y_rounded;
  float x, y, x_rot, y_rot;
  for(float t = -par_t; t<par_t; t+=0.001)
  {
    x =  (a*t*t/(1+t*t));
    y = a*t*t*t/(1+t*t);
    //glm::vec3 vector = {x, y, 1.0f};

    graphic.get_vector(x, y);
    graphic.get_vector_shift();
    vector = graphic.transform();



    //p.Tx=object_syst


   // vector = p.transform(vector.x+p.x_sh, vector.y+p.y_sh);





    x_rounded = round(vector.x);
    y_rounded = round(vector.y);

    if(x_rounded<0||x_rounded>=SCREEN_WIDTH||y_rounded>=SCREEN_HEIGHT||y_rounded<0)
      continue;
      else
        put_pixel32(s, vector.x, vector.y, 0x00000000);
  }


  // for (int i = 30; i < 100; i++)
  //   for (int j = 30; j < 100; j++)
  //     put_pixel32(s, i, j, 0x00FF0000);

  // // Формат цвета в HEX коде:
  // //     0x00RRGGBB
  // //  где R: от 00 до FF
  // //      G: от 00 до FF
  // //      B: от 00 до FF

  // for (int i = 100; i < 200; i++)
  //   for (int j = 100; j < 180; j++)
  //     put_pixel32(s, i, j, RGB32(0, 255, 0));

  // или использу¤ макрос можно получить код цвета:
  //   RGB32(0, 255, 0) эквивалентно записи 0x0000FF00
}


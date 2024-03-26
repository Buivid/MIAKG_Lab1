#pragma once
#include <SDL.h>
#include <cassert>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/ext.hpp>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 640;
class Pixel
{
private:

public:
int x_sh;
int y_sh;
float scale_koef;
float phi;
glm::mat4 Translate = glm::translate(   glm::mat4(1.0f), glm::vec3(x_sh, y_sh, 1.0f));
glm::mat4 Rotate = glm::rotate(glm::mat4(1.0f), glm::radians(phi), glm::vec3(0.0, 0.0, 1.0));
glm::mat4 Scale = glm::scale(glm::mat4(1.0f), glm::vec3(scale_koef, scale_koef, 1));
Pixel (): x_sh(SCREEN_WIDTH/2), y_sh(SCREEN_HEIGHT/2), scale_koef(1), phi(0)
{}
glm::vec3 transform(float x, float y)
{
  glm::vec4 Vector = {x, y, 1.0f, 1.0f};



  glm::mat4 transf_matr = Translate * Rotate * Scale;
  // transf_matr = transf_matr

  glm::vec4 Transformed = transf_matr * Vector;

  return Transformed;
}
};
void draw(SDL_Surface *s, Pixel p, int a, float t);

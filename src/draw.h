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
class Transform
{
private:
glm::mat4 Translate;
glm::mat4 Rotate;
glm::mat4 Scale;
void get_translate()
{
  Translate = glm::translate(   glm::mat4(1.0f), glm::vec3(Tx, Ty, 1.0f));
}
void get_rotate()
{
  Rotate = glm::rotate(glm::mat4(1.0f), glm::radians(phi), glm::vec3(0.0, 0.0, 1.0));
}
void get_scale()
{
  Scale = glm::scale(glm::mat4(1.0f), glm::vec3(scale_koef, scale_koef, 1));
}
public:
int Tx;
int Ty;
int x_sh;
int y_sh;
float scale_koef;
float phi;

Transform (): Tx(0), Ty(0), x_sh(0), y_sh(0), scale_koef(1), phi(0)
{
}

glm::vec3 transform(float x, float y)
{
  get_translate();
  get_rotate();
  get_scale();
  glm::vec4 Vector = {x, y, 1.0f, 1.0f};
  glm::vec4 Transformed =  Translate * Rotate * Scale * Vector;
  return Transformed;
}
glm::vec3 translate(glm::vec3 v)
{
  get_translate();
  glm::vec4 Vector = {v, 1.0f};
  glm::vec4 Translated;
}
glm::vec3 rotate(glm::vec3 v)
{
  get_rotate();
  glm::vec4 Vector = {v, 1.0f};
  glm::vec4 Rotated;
}
glm::vec3 scale(glm::vec3 v)
{
  get_scale();
  glm::vec4 Vector = {v, 1.0f};
  glm::vec4 Scaled;
}

};

class Drawing: public Transform
{
  protected:
  glm::vec3 vector;
  glm::vec3 observer_syst_coord;
  glm::vec3 object_syst_coord;
  public:
  Drawing(int x, int y)
  {
    observer_syst_coord.x=x;
    observer_syst_coord.y=y;
    object_syst_coord.x=x;
    object_syst_coord.y=y;
    Transform::Tx=x;
    Transform::Ty=y;
  }
  void get_vector(int x, int y)
  {
    vector = {x, y, 1.0f};
  }
  void get_observer_coord(int x, int y)
  {
    observer_syst_coord = {x, y, 1.0f};
    Tx=x;
    Ty=y;
  }
  void get_vector_shift()
  {
    vector=vector+object_syst_coord-observer_syst_coord;
    //vector=vector-observer_syst_coord;
    //vector=vector-(object_syst_coord-observer_syst_coord);
  }
  glm::vec3 transform()
  {
    vector = Transform::transform(vector.x, vector.y);
    return vector;
  }




};
void draw(SDL_Surface *s, Drawing p, int a, float t);

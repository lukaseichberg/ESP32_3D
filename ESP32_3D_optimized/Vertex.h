#ifndef VERTEX_CLASS
#define VERTEX_CLASS

#include "Vec4.h"
#include "Vec2.h"

class Vertex {
  public:
    Vertex operator+(Vertex v);
    Vertex operator-(Vertex v);
    Vertex operator*(float value);
    Vertex operator/(float value);
    void operator+=(Vertex v);
    void operator*=(float value);
    void operator/=(float value);
    Vertex lerp(Vertex v, float value);

    Vec4 pos;
    Vec2 uv;
};

#endif
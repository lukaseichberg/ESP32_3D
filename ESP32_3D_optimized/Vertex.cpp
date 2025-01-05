#include "Vertex.h"

Vertex Vertex::operator+(Vertex v) {
  Vertex tmp;
  tmp.pos = pos + v.pos;
  tmp.uv = uv + v.uv;
  return tmp;
}

Vertex Vertex::operator-(Vertex v) {
  Vertex tmp;
  tmp.pos = pos - v.pos;
  tmp.uv = uv - v.uv;
  return tmp;
}

Vertex Vertex::operator*(float value) {
  Vertex tmp;
  tmp.pos = pos * value;
  tmp.uv = uv * value;
  return tmp;
}

Vertex Vertex::operator/(float value) {
  Vertex tmp;
  tmp.pos = pos / value;
  tmp.uv = uv / value;
  return tmp;
}

void Vertex::operator+=(Vertex v) {
  pos += v.pos;
  uv += v.uv;
}

void Vertex::operator*=(float value) {
  pos *= value;
  uv *= value;
}

void Vertex::operator/=(float value) {
  pos /= value;
  uv /= value;
}

Vertex Vertex::lerp(Vertex v, float value) {
  Vertex newVertex;
  newVertex.pos = pos.lerp(v.pos, value);
  newVertex.uv = uv.lerp(v.uv, value);
  return newVertex;
}
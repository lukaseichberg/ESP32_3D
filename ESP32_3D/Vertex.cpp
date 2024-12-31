#include "Vertex.h"

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
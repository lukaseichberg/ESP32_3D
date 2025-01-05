#ifndef CUBE_MODEL
#define CUBE_MODEL

#include <stdint.h>

Vec4 cubeVertices[] = {
  Vec4(-0.5f, -0.5f, -0.5f, 1.0f),
  Vec4(-0.5f, -0.5f, 0.5f, 1.0f),
  Vec4(-0.5f, 0.5f, -0.5f, 1.0f),
  Vec4(-0.5f, 0.5f, 0.5f, 1.0f),
  Vec4(0.5f, -0.5f, -0.5f, 1.0f),
  Vec4(0.5f, -0.5f, 0.5f, 1.0f),
  Vec4(0.5f, 0.5f, -0.5f, 1.0f),
  Vec4(0.5f, 0.5f, 0.5f, 1.0f)
};

Vec2 cubeUVs[] = {
  Vec2(0, 0),
  Vec2(0, 1),
  Vec2(1, 0),
  Vec2(1, 1)
};

uint16_t cubeIndices[] = {
//Vertices,     UVs
  0, 2, 4,      1, 0, 3,
  2, 6, 4,      0, 2, 3,
  4, 6, 5,      1, 0, 3,
  6, 7, 5,      0, 2, 3,
  5, 7, 1,      1, 0, 3,
  7, 3, 1,      0, 2, 3,
  1, 3, 0,      1, 0, 3,
  3, 2, 0,      0, 2, 3,
  0, 4, 5,      0, 2, 3,
  0, 5, 1,      0, 3, 1,
  3, 6, 2,      0, 3, 1,
  3, 7, 6,      0, 2, 3
};

#endif
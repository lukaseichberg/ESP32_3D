#include <TFT_eSPI.h>
#include <SPI.h>

#include "Vec2.h"
#include "Vec3.h"
#include "Vec4.h"
#include "Mat3.h"
#include "Mat4.h"
#include "Vertex.h"

#include "CubeModel.h"
#include "crateTexture.c"

#define PERSPECTIVE_CORRECTION
#define BACKFACE_CULLING

TFT_eSPI tft = TFT_eSPI();

const uint16_t width = 128;
const uint16_t height = 128;
uint16_t colorBuffer[width * height];
float depthBuffer[width * height];
Vec2 screenSize(width, height);

float near = 0.3f;
float far = 15.0f;

int fps = 0;
int frames = 0;
unsigned long lastTime = millis();

float rotation = 0;

Mat4 translate = Mat4::translate(0.0f, 0.0f, 1.75f);
Mat4 mat = Mat4::identity();

void setup(void) {
  tft.init();
  tft.setSwapBytes(true);
  tft.fillScreen(TFT_BLACK);
}

void loop() {
  frames++;
  unsigned long thisTime = millis();
  if (thisTime - lastTime >= 1000) {
    fps = frames;
    frames = 0;
    lastTime = thisTime;

    tft.fillRect(0, 128, 128, 16, TFT_BLACK);
    tft.setCursor(1, 129);
    tft.setTextColor(TFT_WHITE);
    tft.print("FPS: ");
    tft.println(fps);
  }

  rotation += 1.0f;

  clear();
  Mat4 rotX = Mat4::rotateX(rotation);
  Mat4 rotY = Mat4::rotateY(rotation);
  mat = translate * rotY * rotX;
  renderModel(cubeVertices, cubeUVs, cubeIndices, 12);
  update();
}

void renderModel(Vec4* vertices, Vec2* uvs, uint16_t* indices, int triangleCount) {
  for (int i = 0; i < triangleCount; i++) {
    Vertex v0;
    Vertex v1;
    Vertex v2;
    v0.pos = vertices[indices[i*6]] * mat;
    v1.pos = vertices[indices[i*6+1]] * mat;
    v2.pos = vertices[indices[i*6+2]] * mat;
    v0.uv = uvs[indices[i*6+3]];
    v1.uv = uvs[indices[i*6+4]];
    v2.uv = uvs[indices[i*6+5]];

    renderTriangle(v0, v1, v2);
  }
}

void renderTriangle(Vertex v0, Vertex v1, Vertex v2) {
  #ifdef BACKFACE_CULLING
    Vec3 tv0 = v0.pos.xyz();
    Vec3 tv1 = v1.pos.xyz();
    Vec3 tv2 = v2.pos.xyz();

    Vec3 normal = (tv1 - tv0).cross(tv2 - tv0).normal();
    Vec3 toV0 = tv0.normal();
    if (toV0.dot(normal) > 0) return;
  #endif

  Vertex clip[10] = {v0, v1, v2};
  int vertexCount = 3;
  vertexCount = clipNear(&clip[0], vertexCount);
  vertexCount = clipFar(&clip[0], vertexCount);

  projectToScreen(&clip[0], vertexCount);

  vertexCount = clipLeft(&clip[0], vertexCount);
  vertexCount = clipBottom(&clip[0], vertexCount);
  vertexCount = clipRight(&clip[0], vertexCount);
  vertexCount = clipTop(&clip[0], vertexCount);

  // Triangle Fan
  for (int i = 1; i < vertexCount - 1; i++) {
    fillTriangle(clip[0], clip[i], clip[i + 1]);
  }
}

void projectToScreen(Vertex* list, int vertexCount) {
  for (int i = 0; i < vertexCount; i++) {
    Vertex v = list[i];
    #ifdef PERSPECTIVE_CORRECTION
      v *= 1.0f / v.pos.z;
    #else
      v.pos *= 1.0f / v.pos.z;
    #endif

    v.pos.x = (v.pos.x * 0.5f + 0.5f) * screenSize.x;
    v.pos.y = (-v.pos.y * 0.5f + 0.5f) * screenSize.y;

    list[i] = v;
  }
}

int clipNear(Vertex* list, int vertexCount) {
  Vertex tmp = list[0];
  int index = 0;
  for (int i = 0; i < vertexCount; i++) {
    int nextI = (i + 1) % vertexCount;
    
    Vertex v = list[i];
    Vertex nextV;
    if (nextI == 0) {
      nextV = tmp;
    } else {
      nextV = list[nextI];
    }

    if (v.pos.z < near) {
      if (nextV.pos.z >= near) {
        float value = (near - v.pos.z) / (nextV.pos.z - v.pos.z);
        list[index++] = v.lerp(nextV, value);
        list[index++] = nextV;
      }
    } else {
      if (nextV.pos.z >= near) {
        list[index++] = nextV;
      } else {
        float value = (near - v.pos.z) / (nextV.pos.z - v.pos.z);
        list[index++] = v.lerp(nextV, value);
      }
    }
  }
  return index;
}

int clipFar(Vertex* list, int vertexCount) {
  Vertex tmp = list[0];
  int index = 0;
  for (int i = 0; i < vertexCount; i++) {
    int nextI = (i + 1) % vertexCount;
    
    Vertex v = list[i];
    Vertex nextV;
    if (nextI == 0) {
      nextV = tmp;
    } else {
      nextV = list[nextI];
    }

    if (v.pos.z > far) {
      if (nextV.pos.z <= far) {
        float value = (far - v.pos.z) / (nextV.pos.z - v.pos.z);
        list[index++] = v.lerp(nextV, value);
        list[index++] = nextV;
      }
    } else {
      if (nextV.pos.z <= far) {
        list[index++] = nextV;
      } else {
        float value = (far - v.pos.z) / (nextV.pos.z - v.pos.z);
        list[index++] = v.lerp(nextV, value);
      }
    }
  }
  return index;
}

int clipLeft(Vertex* list, int vertexCount) {
  float left = 0.0f;
  Vertex tmp = list[0];
  int index = 0;
  for (int i = 0; i < vertexCount; i++) {
    int nextI = (i + 1) % vertexCount;
    
    Vertex v = list[i];
    Vertex nextV;
    if (nextI == 0) {
      nextV = tmp;
    } else {
      nextV = list[nextI];
    }
    
    if (v.pos.x <= left) {
      if (nextV.pos.x > left) {
        float value = (left - v.pos.x) / (nextV.pos.x - v.pos.x);
        list[index++] = v.lerp(nextV, value);
        list[index++] = nextV;
      }
    } else {
      if (nextV.pos.x > left) {
        list[index++] = nextV;
      } else {
        float value = (left - v.pos.x) / (nextV.pos.x - v.pos.x);
        list[index++] = v.lerp(nextV, value);
      }
    }
  }
  return index;
}

int clipRight(Vertex* list, int vertexCount) {
  float right = float(width);
  Vertex tmp = list[0];
  int index = 0;
  for (int i = 0; i < vertexCount; i++) {
    int nextI = (i + 1) % vertexCount;
    
    Vertex v = list[i];
    Vertex nextV;
    if (nextI == 0) {
      nextV = tmp;
    } else {
      nextV = list[nextI];
    }
    
    if (v.pos.x > right) {
      if (nextV.pos.x <= right) {
        float value = (right - v.pos.x) / (nextV.pos.x - v.pos.x);
        list[index++] = v.lerp(nextV, value);
        list[index++] = nextV;
      }
    } else {
      if (nextV.pos.x <= right) {
        list[index++] = nextV;
      } else {
        float value = (right - v.pos.x) / (nextV.pos.x - v.pos.x);
        list[index++] = v.lerp(nextV, value);
      }
    }
  }
  return index;
}

int clipTop(Vertex* list, int vertexCount) {
  float top = float(height);
  Vertex tmp = list[0];
  int index = 0;
  for (int i = 0; i < vertexCount; i++) {
    int nextI = (i + 1) % vertexCount;
    
    Vertex v = list[i];
    Vertex nextV;
    if (nextI == 0) {
      nextV = tmp;
    } else {
      nextV = list[nextI];
    }
    
    if (v.pos.y > top) {
      if (nextV.pos.y <= top) {
        float value = (top - v.pos.y) / (nextV.pos.y - v.pos.y);
        list[index++] = v.lerp(nextV, value);
        list[index++] = nextV;
      }
    } else {
      if (nextV.pos.y <= top) {
        list[index++] = nextV;
      } else {
        float value = (top - v.pos.y) / (nextV.pos.y - v.pos.y);
        list[index++] = v.lerp(nextV, value);
      }
    }
  }
  return index;
}

int clipBottom(Vertex* list, int vertexCount) {
  float bottom = 0;
  Vertex tmp = list[0];
  int index = 0;
  for (int i = 0; i < vertexCount; i++) {
    int nextI = (i + 1) % vertexCount;
    
    Vertex v = list[i];
    Vertex nextV;
    if (nextI == 0) {
      nextV = tmp;
    } else {
      nextV = list[nextI];
    }
    
    if (v.pos.y < bottom) {
      if (nextV.pos.y >= bottom) {
        float value = (bottom - v.pos.y) / (nextV.pos.y - v.pos.y);
        list[index++] = v.lerp(nextV, value);
        list[index++] = nextV;
      }
    } else {
      if (nextV.pos.y >= bottom) {
        list[index++] = nextV;
      } else {
        float value = (bottom - v.pos.y) / (nextV.pos.y - v.pos.y);
        list[index++] = v.lerp(nextV, value);
      }
    }
  }
  return index;
}

void fillTriangle(Vertex v0, Vertex v1, Vertex v2) {
  Vertex* pv0 = &v0;
  Vertex* pv1 = &v1;
  Vertex* pv2 = &v2;

  if (pv0->pos.y > pv1->pos.y) std::swap(pv0, pv1);
  if (pv1->pos.y > pv2->pos.y) std::swap(pv1, pv2);
  if (pv0->pos.y > pv1->pos.y) std::swap(pv0, pv1);

  if (pv0->pos.y == pv1->pos.y) {
    if (pv0->pos.x > pv1->pos.x) std::swap(pv0, pv1);
    fillTopFlatTriangle(*pv0, *pv1, *pv2);
  } else if (pv1->pos.y == pv2->pos.y) {
    if (pv1->pos.x > pv2->pos.x) std::swap(pv1, pv2);
    fillBottomFlatTriangle(*pv0, *pv1, *pv2);
  } else {
    float value = (pv1->pos.y - pv0->pos.y) / (pv2->pos.y - pv0->pos.y);
    Vertex vi = (*pv0).lerp(*pv2, value);

    if (vi.pos.x > pv1->pos.x) {
      fillBottomFlatTriangle(*pv0, *pv1, vi);
      fillTopFlatTriangle(*pv1, vi, *pv2);
    } else {
      fillBottomFlatTriangle(*pv0, vi, *pv1);
      fillTopFlatTriangle(vi, *pv1, *pv2);
    }
  }
}

void fillBottomFlatTriangle(Vertex v0, Vertex v1, Vertex v2) {
  int yStart = (int) ceil(v0.pos.y - 0.5f);
  int yEnd = (int) ceil(v2.pos.y - 0.5f);

  if (yStart == yEnd) return;

  Vertex leftDif = v1 - v0;
  Vertex rightDif = v2 - v0;
  float oneOverHeight = 1.0f / leftDif.pos.y;
  float value = (yStart + 0.5f - v0.pos.y);
  Vertex leftStep = leftDif * oneOverHeight;
  Vertex rightStep = rightDif * oneOverHeight;
  Vertex leftTop = v0 + leftStep * value;
  Vertex rightTop = v0 + rightStep * value;

  for (int y = yStart; y < yEnd; y++) {
    fillHorizontalLine(leftTop, rightTop);
    leftTop += leftStep;
    rightTop += rightStep;
  }
}

void fillTopFlatTriangle(Vertex v0, Vertex v1, Vertex v2) {
  int yStart = (int) ceil(v0.pos.y - 0.5f);
  int yEnd = (int) ceil(v2.pos.y - 0.5f);

  if (yStart == yEnd) return;

  Vertex leftDif = v2 - v0;
  Vertex rightDif = v2 - v1;
  float oneOverHeight = 1.0f / leftDif.pos.y;
  float value = (yStart + 0.5f - v0.pos.y);
  Vertex leftStep = leftDif * oneOverHeight;
  Vertex rightStep = rightDif * oneOverHeight;
  Vertex leftTop = v0 + leftStep * value;
  Vertex rightTop = v1 + rightStep * value;

  for (int y = yStart; y < yEnd; y++) {
    fillHorizontalLine(leftTop, rightTop);
    leftTop += leftStep;
    rightTop += rightStep;
  }
}

void fillHorizontalLine(Vertex v0, Vertex v1) {
  int xStart = (int) ceil(v0.pos.x - 0.5f);
  int xEnd = (int) ceil(v1.pos.x - 0.5f);

  if (xStart == xEnd) return;

  Vertex dif = v1 - v0;
  float oneOverWidth = 1.0f / dif.pos.x;
  float value = (xStart + 0.5f - v0.pos.x);
  Vertex step = dif * oneOverWidth;
  Vertex left = v0 + step * value;

  for (int x = xStart; x < xEnd; x++) {
    fillPixel(left);
    left += step;
  }
}

void fillPixel(Vertex v) {
  int x = v.pos.x;
  int y = v.pos.y;
  float z = v.pos.w;

  int pixelIndex = x + y * width;

  if (z > depthBuffer[pixelIndex]) {
    #ifdef PERSPECTIVE_CORRECTION
      v *= 1.0f / z;
    #else
      v.pos *= 1.0f / z;
    #endif

    uint16_t tx = v.uv.x * 32;
    uint16_t ty = v.uv.y * 32;
    uint16_t c = crate32x32[tx + ty * 32];

    depthBuffer[pixelIndex] = z;
    colorBuffer[pixelIndex] = c;
  }
}

void setDepth(int x, int y, float z) {
  depthBuffer[x + y * width] = z;
}

float getDepth(int x, int y) {
  return depthBuffer[x + y * width];
}

void setColor(int x, int y, uint16_t c) {
  colorBuffer[x + y * width] = c;
}

void clear() {
  for (int i = 0; i < width * height; i++) {
    colorBuffer[i] = TFT_BLACK;
    depthBuffer[i] = 0;
  }
}

void update() {
  tft.pushImage(0, 0, width, height, &colorBuffer[0]);
}
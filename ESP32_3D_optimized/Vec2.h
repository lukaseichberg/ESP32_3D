#ifndef VEC2_CLASS
#define VEC2_CLASS

#include "Math.h"

class Vec2 {
  public:
    Vec2();
    Vec2(float value);
    Vec2(float x, float y);

    Vec2 operator+(Vec2 v);
    Vec2 operator-(Vec2 v);
    Vec2 operator*(Vec2 v);
    Vec2 operator/(Vec2 v);
    Vec2 operator+(float value);
    Vec2 operator-(float value);
    Vec2 operator*(float scalar);
    Vec2 operator/(float scalar);

    void operator+=(Vec2 v);
    void operator-=(Vec2 v);
    void operator*=(Vec2 v);
    void operator/=(Vec2 v);
    void operator+=(float value);
    void operator-=(float value);
    void operator*=(float scalar);
    void operator/=(float scalar);

    float dot(Vec2 v);
    float invMag();
    float mag();
    float magSq();
    Vec2 normal();
    void normalize();

    Vec2 lerp(Vec2 v, float value);

    Vec2 min(Vec2 v);
    Vec2 max(Vec2 v);

    float min();
    float max();

    float x, y;
};

#endif
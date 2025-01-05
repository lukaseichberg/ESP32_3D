#ifndef VEC4_CLASS
#define VEC4_CLASS

#include "Math.h"
#include "Vec2.h"
#include "Vec3.h"
#include "Mat4.h"

class Vec4 {
  public:
    Vec4();
    Vec4(float value);
    Vec4(Vec2 v0, Vec2 v1);
    Vec4(Vec2 v, float z, float w);
    Vec4(float x, Vec2 v, float w);
    Vec4(float x, float y, Vec2 v);
    Vec4(Vec3 v, float w);
    Vec4(float x, Vec3 v);
    Vec4(float x, float y, float z, float w);

    Vec4 operator+(Vec4 v);
    Vec4 operator-(Vec4 v);
    Vec4 operator*(Vec4 v);
    Vec4 operator/(Vec4 v);
    Vec4 operator+(float value);
    Vec4 operator-(float value);
    Vec4 operator*(float scalar);
    Vec4 operator/(float scalar);

    void operator+=(Vec4 v);
    void operator-=(Vec4 v);
    void operator*=(Vec4 v);
    void operator/=(Vec4 v);
    void operator+=(float value);
    void operator-=(float value);
    void operator*=(float scalar);
    void operator/=(float scalar);

    Vec4 operator*(Mat4 mat);

    float dot(Vec4 v);
    float invMag();
    float mag();
    float magSq();
    Vec4 normal();
    void normalize();

    Vec4 lerp(Vec4 v, float value);

    Vec4 min(Vec4 v);
    Vec4 max(Vec4 v);

    float min();
    float max();

    Vec3 xyz();

    float x, y, z, w;
};

#endif
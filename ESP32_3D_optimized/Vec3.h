#ifndef VEC3_CLASS
#define VEC3_CLASS

#include "Math.h"
#include "Vec2.h"

class Vec3 {
  public:
    Vec3();
    Vec3(float value);
    Vec3(Vec2 v, float z);
    Vec3(float x, Vec2 v);
    Vec3(float x, float y, float z);

    Vec3 operator+(Vec3 v);
    Vec3 operator-(Vec3 v);
    Vec3 operator*(Vec3 v);
    Vec3 operator/(Vec3 v);
    Vec3 operator+(float value);
    Vec3 operator-(float value);
    Vec3 operator*(float scalar);
    Vec3 operator/(float scalar);

    void operator+=(Vec3 v);
    void operator-=(Vec3 v);
    void operator*=(Vec3 v);
    void operator/=(Vec3 v);
    void operator+=(float value);
    void operator-=(float value);
    void operator*=(float scalar);
    void operator/=(float scalar);

    Vec3 cross(Vec3 v);
    float dot(Vec3 v);
    float invMag();
    float mag();
    float magSq();
    Vec3 normal();
    void normalize();

    Vec3 lerp(Vec3 v, float value);

    Vec3 min(Vec3 v);
    Vec3 max(Vec3 v);

    float min();
    float max();

    Vec2 xx();
    Vec2 xy();
    Vec2 xz();
    Vec2 yx();
    Vec2 yy();
    Vec2 yz();
    Vec2 zx();
    Vec2 zy();
    Vec2 zz();

    float x, y, z;
};

#endif
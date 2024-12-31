#include "Vec4.h"

Vec4::Vec4() {
  x = y = z = w = 0;
}

Vec4::Vec4(float value) {
  x = y = z = w = value;
}

Vec4::Vec4(Vec2 v0, Vec2 v1) {
  x = v0.x;
  y = v0.y;
  z = v1.x;
  w = v1.y;
}

Vec4::Vec4(Vec2 v, float z, float w) {
  x = v.x;
  y = v.y;
  this->z = z;
  this->w = w;
}

Vec4::Vec4(float x, Vec2 v, float w) {
  this->x = x;
  y = v.x;
  z = v.y;
  this->w = w;
}

Vec4::Vec4(float x, float y, Vec2 v) {
  this->x = x;
  this->y = y;
  z = v.x;
  w = v.y;
}

Vec4::Vec4(Vec3 v, float w) {
  x = v.x;
  y = v.y;
  z = v.z;
  this->w = w;
}

Vec4::Vec4(float x, Vec3 v) {
  this->x = x;
  y = v.x;
  z = v.y;
  w = v.z;
}

Vec4::Vec4(float x, float y, float z, float w) {
  this->x = x;
  this->y = y;
  this->z = z;
  this->w = w;
}

Vec4 Vec4::operator+(Vec4 v) {
  return Vec4(
    x + v.x,
    y + v.y,
    z + v.z,
    w + v.w
  );
}

Vec4 Vec4::operator-(Vec4 v) {
  return Vec4(
    x - v.x,
    y - v.y,
    z - v.z,
    w - v.w
  );
}

Vec4 Vec4::operator*(Vec4 v) {
  return Vec4(
    x * v.x,
    y * v.y,
    z * v.z,
    w * v.w
  );
}

Vec4 Vec4::operator/(Vec4 v) {
  return Vec4(
    x / v.x,
    y / v.y,
    z / v.z,
    w / v.w
  );
}

Vec4 Vec4::operator+(float value) {
  return Vec4(
    x + value,
    y + value,
    z + value,
    w + value
  );
}

Vec4 Vec4::operator-(float value) {
  return Vec4(
    x - value,
    y - value,
    z - value,
    w - value
  );
}

Vec4 Vec4::operator*(float scalar) {
  return Vec4(
    x * scalar,
    y * scalar,
    z * scalar,
    w * scalar
  );
}

Vec4 Vec4::operator/(float scalar) {
  return Vec4(
    x / scalar,
    y / scalar,
    z / scalar,
    w / scalar
  );
}

void Vec4::operator+=(Vec4 v) {
  x += v.x;
  y += v.y;
  z += v.z;
  w += v.w;
}

void Vec4::operator-=(Vec4 v) {
  x -= v.x;
  y -= v.y;
  z -= v.z;
  w -= v.w;
}

void Vec4::operator*=(Vec4 v) {
  x *= v.x;
  y *= v.y;
  z *= v.z;
  w *= v.w;
}

void Vec4::operator/=(Vec4 v) {
  x /= v.x;
  y /= v.y;
  z /= v.z;
  w /= v.w;
}

void Vec4::operator+=(float value) {
  x += value;
  y += value;
  z += value;
  w += value;
}

void Vec4::operator-=(float value) {
  x -= value;
  y -= value;
  z -= value;
  w -= value;
}

void Vec4::operator*=(float scalar) {
  x *= scalar;
  y *= scalar;
  z *= scalar;
  w *= scalar;
}

void Vec4::operator/=(float scalar) {
  x /= scalar;
  y /= scalar;
  z /= scalar;
  w /= scalar;
}

Vec4 Vec4::operator*(Mat4 mat) {
  return Vec4(
    x * mat.m00 + y * mat.m01 + z * mat.m02 + w * mat.m03,
    x * mat.m10 + y * mat.m11 + z * mat.m12 + w * mat.m13,
    x * mat.m20 + y * mat.m21 + z * mat.m22 + w * mat.m23,
    x * mat.m30 + y * mat.m31 + z * mat.m32 + w * mat.m33
  );
}

float Vec4::dot(Vec4 v) {
  return x * v.x + y * v.y + z * v.z + w * v.w;
}

float Vec4::invMag() {
  return Math::invSqrt(x * x + y * y + z * z + w * w);
}

float Vec4::mag() {
  return 1.0f / Math::invSqrt(x * x + y * y + z * z + w * w);
}

float Vec4::magSq() {
  return x * x + y * y + z * z + w * w;
}

Vec4 Vec4::normal() {
  float invLen = invMag();
  return Vec4(
    x * invLen,
    y * invLen,
    z * invLen,
    w * invLen
  );
}

void Vec4::normalize() {
  float invLen = invMag();
  x *= invLen;
  y *= invLen;
  z *= invLen;
  w *= invLen;
}

Vec4 Vec4::lerp(Vec4 v, float value) {
  return Vec4(
    Math::lerp(x, v.x, value),
    Math::lerp(y, v.y, value),
    Math::lerp(z, v.z, value),
    Math::lerp(w, v.w, value)
  );
}

Vec4 Vec4::min(Vec4 v) {
  return Vec4(
    Math::min(x, v.x),
    Math::min(y, v.y),
    Math::min(z, v.z),
    Math::min(w, v.w)
  );
}

Vec4 Vec4::max(Vec4 v) {
  return Vec4(
    Math::max(x, v.x),
    Math::max(y, v.y),
    Math::max(z, v.z),
    Math::max(w, v.w)
  );
}

float Vec4::min() {
  return Math::min(Math::min(Math::min(x, y), z), w);
}

float Vec4::max() {
  return Math::max(Math::max(Math::max(x, y), z), w);
}

Vec3 Vec4::xyz() {
  return Vec3(x, y, z);
}

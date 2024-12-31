#include "Vec3.h"

Vec3::Vec3() {
  x = y = z = 0;
}

Vec3::Vec3(float value) {
  x = y = z = value;
}

Vec3::Vec3(Vec2 v, float z) {
  x = v.x;
  y = v.y;
  this->z = z;
}

Vec3::Vec3(float x, Vec2 v) {
  this->x = x;
  y = v.x;
  z = v.y;
}

Vec3::Vec3(float x, float y, float z) {
  this->x = x;
  this->y = y;
  this->z = z;
}

Vec3 Vec3::operator+(Vec3 v) {
  return Vec3(
    x + v.x,
    y + v.y,
    z + v.z
  );
}

Vec3 Vec3::operator-(Vec3 v) {
  return Vec3(
    x - v.x,
    y - v.y,
    z - v.z
  );
}

Vec3 Vec3::operator*(Vec3 v) {
  return Vec3(
    x * v.x,
    y * v.y,
    z * v.z
  );
}

Vec3 Vec3::operator/(Vec3 v) {
  return Vec3(
    x / v.x,
    y / v.y,
    z / v.z
  );
}

Vec3 Vec3::operator+(float value) {
  return Vec3(
    x + value,
    y + value,
    z + value
  );
}

Vec3 Vec3::operator-(float value) {
  return Vec3(
    x - value,
    y - value,
    z - value
  );
}

Vec3 Vec3::operator*(float scalar) {
  return Vec3(
    x * scalar,
    y * scalar,
    z * scalar
  );
}

Vec3 Vec3::operator/(float scalar) {
  return Vec3(
    x / scalar,
    y / scalar,
    z / scalar
  );
}

void Vec3::operator+=(Vec3 v) {
  x += v.x;
  y += v.y;
  z += v.z;
}

void Vec3::operator-=(Vec3 v) {
  x -= v.x;
  y -= v.y;
  z -= v.z;
}

void Vec3::operator*=(Vec3 v) {
  x *= v.x;
  y *= v.y;
  z *= v.z;
}

void Vec3::operator/=(Vec3 v) {
  x /= v.x;
  y /= v.y;
  z /= v.z;
}

void Vec3::operator+=(float value) {
  x += value;
  y += value;
  z += value;
}

void Vec3::operator-=(float value) {
  x -= value;
  y -= value;
  z -= value;
}

void Vec3::operator*=(float scalar) {
  x *= scalar;
  y *= scalar;
  z *= scalar;
}

void Vec3::operator/=(float scalar) {
  x /= scalar;
  y /= scalar;
  z /= scalar;
}

Vec3 Vec3::cross(Vec3 v) {
  return Vec3(
    y * v.z - z * v.y,
    z * v.x - x * v.z,
    x * v.y - y * v.x
  );
}

float Vec3::dot(Vec3 v) {
  return x * v.x + y * v.y + z * v.z;
}

float Vec3::invMag() {
  return Math::invSqrt(x * x + y * y + z * z);;
}

float Vec3::mag() {
  return 1.0f / Math::invSqrt(x * x + y * y + z * z);
}

float Vec3::magSq() {
  return x * x + y * y + z * z;
}

Vec3 Vec3::normal() {
  float invLen = invMag();
  return Vec3(
    x * invLen,
    y * invLen,
    z * invLen
  );
}

void Vec3::normalize() {
  float invLen = invMag();
  x *= invLen;
  y *= invLen;
  z *= invLen;
}

Vec3 Vec3::lerp(Vec3 v, float value) {
  return Vec3(
    Math::lerp(x, v.x, value),
    Math::lerp(y, v.y, value),
    Math::lerp(z, v.z, value)
  );
}

Vec3 Vec3::min(Vec3 v) {
  return Vec3(
    Math::min(x, v.x),
    Math::min(y, v.y),
    Math::min(z, v.z)
  );
}

Vec3 Vec3::max(Vec3 v) {
  return Vec3(
    Math::max(x, v.x),
    Math::max(y, v.y),
    Math::max(z, v.z)
  );
}

float Vec3::min() {
  return Math::min(Math::min(x, y), z);
}

float Vec3::max() {
  return Math::max(Math::max(x, y), z);
}

Vec2 Vec3::xx() { return Vec2(x, x); }
Vec2 Vec3::xy() { return Vec2(x, y); }
Vec2 Vec3::xz() { return Vec2(x, z); }
Vec2 Vec3::yx() { return Vec2(y, x); }
Vec2 Vec3::yy() { return Vec2(y, y); }
Vec2 Vec3::yz() { return Vec2(y, z); }
Vec2 Vec3::zx() { return Vec2(z, x); }
Vec2 Vec3::zy() { return Vec2(z, y); }
Vec2 Vec3::zz() { return Vec2(z, z); }






















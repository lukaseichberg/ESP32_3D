#include "Vec2.h"

Vec2::Vec2() {
  x = y = 0;
}

Vec2::Vec2(float value) {
  x = y = value;
}

Vec2::Vec2(float x, float y) {
  this->x = x;
  this->y = y;
}

Vec2 Vec2::operator+(Vec2 v) {
  return Vec2(
    x + v.x,
    y + v.y
  );
}

Vec2 Vec2::operator-(Vec2 v) {
  return Vec2(
    x - v.x,
    y - v.y
  );
}

Vec2 Vec2::operator*(Vec2 v) {
  return Vec2(
    x * v.x,
    y * v.y
  );
}

Vec2 Vec2::operator/(Vec2 v) {
  return Vec2(
    x / v.x,
    y / v.y
  );
}

Vec2 Vec2::operator+(float value) {
  return Vec2(
    x + value,
    y + value
  );
}

Vec2 Vec2::operator-(float value) {
  return Vec2(
    x - value,
    y - value
  );
}

Vec2 Vec2::operator*(float scalar) {
  return Vec2(
    x * scalar,
    y * scalar
  );
}

Vec2 Vec2::operator/(float scalar) {
  return Vec2(
    x / scalar,
    y / scalar
  );
}

void Vec2::operator+=(Vec2 v) {
  x += v.x;
  y += v.y;
}

void Vec2::operator-=(Vec2 v) {
  x -= v.x;
  y -= v.y;
}

void Vec2::operator*=(Vec2 v) {
  x *= v.x;
  y *= v.y;
}

void Vec2::operator/=(Vec2 v) {
  x /= v.x;
  y /= v.y;
}

void Vec2::operator+=(float value) {
  x += value;
  y += value;
}

void Vec2::operator-=(float value) {
  x -= value;
  y -= value;
}

void Vec2::operator*=(float scalar) {
  x *= scalar;
  y *= scalar;
}

void Vec2::operator/=(float scalar) {
  x /= scalar;
  y /= scalar;
}

float Vec2::dot(Vec2 v) {
  return x * v.x + y * v.y;
}

float Vec2::invMag() {
  return Math::invSqrt(x * x + y * y);
}

float Vec2::mag() {
  return 1.0f / Math::invSqrt(x * x + y * y);
}

float Vec2::magSq() {
  return x * x + y * y;
}

Vec2 Vec2::normal() {
  float invLen = invMag();
  return Vec2(
    x * invLen,
    y * invLen
  );
}

void Vec2::normalize() {
  float invLen = invMag();
  x *= invLen;
  y *= invLen;
}

Vec2 Vec2::lerp(Vec2 v, float value) {
  return Vec2(
    Math::lerp(x, v.x, value),
    Math::lerp(y, v.y, value)
  );
}

Vec2 Vec2::min(Vec2 v) {
  return Vec2(
    Math::min(x, v.x),
    Math::min(y, v.y)
  );
}

Vec2 Vec2::max(Vec2 v) {
  return Vec2(
    Math::max(x, v.x),
    Math::max(y, v.y)
  );
}

float Vec2::min() {
  return Math::min(x, y);
}

float Vec2::max() {
  return Math::max(x, y);
}
























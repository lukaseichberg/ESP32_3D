#include <cmath>
#include "Mat4.h"

const float PI = 3.14159265358979323846;

float Mat4::toRadians(float deg) {
  return deg * PI / 180.0f;
}

Mat4::Mat4() {
  this->m00 = 1.0f;
  this->m01 = 0.0f;
  this->m02 = 0.0f;
  this->m03 = 0.0f;
  this->m10 = 0.0f;
  this->m11 = 1.0f;
  this->m12 = 0.0f;
  this->m13 = 0.0f;
  this->m20 = 0.0f;
  this->m21 = 0.0f;
  this->m22 = 1.0f;
  this->m23 = 0.0f;
  this->m30 = 0.0f;
  this->m31 = 0.0f;
  this->m32 = 0.0f;
  this->m33 = 1.0f;
}

Mat4::Mat4(
  float m00, float m01, float m02, float m03,
  float m10, float m11, float m12, float m13,
  float m20, float m21, float m22, float m23,
  float m30, float m31, float m32, float m33
) {
  this->m00 = m00;
  this->m01 = m01;
  this->m02 = m02;
  this->m03 = m03;
  this->m10 = m10;
  this->m11 = m11;
  this->m12 = m12;
  this->m13 = m13;
  this->m20 = m20;
  this->m21 = m21;
  this->m22 = m22;
  this->m23 = m23;
  this->m30 = m30;
  this->m31 = m31;
  this->m32 = m32;
  this->m33 = m33;
}

Mat4 Mat4::operator*(Mat4 mat) {
  return Mat4(
    m00 * mat.m00 + m01 * mat.m10 + m02 * mat.m20 + m03 * mat.m30,
    m00 * mat.m01 + m01 * mat.m11 + m02 * mat.m21 + m03 * mat.m31,
    m00 * mat.m02 + m01 * mat.m12 + m02 * mat.m22 + m03 * mat.m32,
    m00 * mat.m03 + m01 * mat.m13 + m02 * mat.m23 + m03 * mat.m33,
    m10 * mat.m00 + m11 * mat.m10 + m12 * mat.m20 + m13 * mat.m30,
    m10 * mat.m01 + m11 * mat.m11 + m12 * mat.m21 + m13 * mat.m31,
    m10 * mat.m02 + m11 * mat.m12 + m12 * mat.m22 + m13 * mat.m32,
    m10 * mat.m03 + m11 * mat.m13 + m12 * mat.m23 + m13 * mat.m33,
    m20 * mat.m00 + m21 * mat.m10 + m22 * mat.m20 + m23 * mat.m30,
    m20 * mat.m01 + m21 * mat.m11 + m22 * mat.m21 + m23 * mat.m31,
    m20 * mat.m02 + m21 * mat.m12 + m22 * mat.m22 + m23 * mat.m32,
    m20 * mat.m03 + m21 * mat.m13 + m22 * mat.m23 + m23 * mat.m33,
    m30 * mat.m00 + m31 * mat.m10 + m32 * mat.m20 + m33 * mat.m30,
    m30 * mat.m01 + m31 * mat.m11 + m32 * mat.m21 + m33 * mat.m31,
    m30 * mat.m02 + m31 * mat.m12 + m32 * mat.m22 + m33 * mat.m32,
    m30 * mat.m03 + m31 * mat.m13 + m32 * mat.m23 + m33 * mat.m33
  );
}

Mat4 Mat4::rotateX(float deg) {
  float rad = toRadians(deg);
  return Mat4(
    1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, cos(rad), -sin(rad), 0.0f,
    0.0f, sin(rad), cos(rad), 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f
  );
}
	
Mat4 Mat4::rotateY(float deg) {
  float rad = toRadians(deg);
  return Mat4(
    cos(rad), 0.0f, sin(rad), 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f,
    -sin(rad), 0.0f, cos(rad), 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f
  );
}
	
Mat4 Mat4::rotateZ(float deg) {
  float rad = toRadians(deg);
  return Mat4(
    cos(rad), -sin(rad), 0.0f, 0.0f,
    sin(rad), cos(rad), 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f
  );
}
	
Mat4 Mat4::translate(float x, float y, float z) {
  return Mat4(
    1.0f, 0.0f, 0.0f, x,
    0.0f, 1.0f, 0.0f, y,
    0.0f, 0.0f, 1.0f, z,
    0.0f, 0.0f, 0.0f, 1.0f
  );
}

Mat4 Mat4::scale(float x, float y, float z) {
  return Mat4(
    x, 0.0f, 0.0f, 0.0f,
    0.0f, y, 0.0f, 0.0f,
    0.0f, 0.0f, z, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f
  );
}

Mat4 Mat4::identity() {
  return Mat4(
    1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f
  );
}
#ifndef MAT4_CLASS
#define MAT4_CLASS

class Mat4 {
  public:
    float m00, m01, m02, m03, m10, m11, m12, m13, m20, m21, m22, m23, m30, m31, m32, m33;

    Mat4();

    Mat4(
      float m00, float m01, float m02, float m03,
      float m10, float m11, float m12, float m13,
      float m20, float m21, float m22, float m23,
      float m30, float m31, float m32, float m33
    );

    Mat4 operator*(Mat4 mat);

    static Mat4 rotateX(float deg);
    static Mat4 rotateY(float deg);
    static Mat4 rotateZ(float deg);
    static Mat4 translate(float x, float y, float z);
    static Mat4 scale(float x, float y, float z);
    static Mat4 identity();

  private:
    static float toRadians(float deg);
};

#endif
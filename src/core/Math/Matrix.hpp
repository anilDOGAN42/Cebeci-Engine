#pragma once
#include "vector.hpp"

namespace CebeciEngine::Core::Math {


union Mat2;
union Mat3;
union Mat4;

typedef union Mat2{
    float m[2][2];
    float v[4]={0,0,0,0};

    float* operator[](int row);
    const float* operator[](int row) const;

    Mat2 operator+(const Mat2& o) const;
    Mat2 operator-(const Mat2& o) const;

    Mat2 operator*(float s) const;
    Mat2 operator*(const Mat2& o) const;

    Vec2 operator*(const Vec2& vec) const;

    Mat2& operator*=(const Mat2& o);
}mat2;

typedef union Mat3{
    float m[3][3];
    float v[9]={0,0,0,0,0,0,0,0,0};

    float* operator[](int row);
    const float* operator[](int row) const;

    Mat3 operator+(const Mat3& o) const;
    Mat3 operator-(const Mat3& o) const;

    Mat3 operator*(float s) const;
    Mat3 operator*(const Mat3& o) const;

    Vec3 operator*(const Vec3& vec) const;

    Mat3& operator*=(const Mat3& o);
}mat3;

typedef union Mat4{
    float m[4][4];
    float v[16]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

    float* operator[](int row);
    const float* operator[](int row) const;

    Mat4 operator+(const Mat4& o) const;
    Mat4 operator-(const Mat4& o) const;

    Mat4 operator*(float s) const;
    Mat4 operator*(const Mat4& o) const;

    Vec4 operator*(const Vec4& vec) const;

    Mat4& operator*=(const Mat4& o);
}mat4;

}

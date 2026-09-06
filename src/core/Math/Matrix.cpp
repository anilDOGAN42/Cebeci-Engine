#include "Matrix.hpp"

namespace CebeciEngine::Core::Math {

float* Mat2::operator[](int row){
    return m[row];
}

const float* Mat2::operator[](int row) const{
    return m[row];
}

Mat2  Mat2::operator+(const Mat2& o) const{
    Mat2 res;
    for (int i = 0; i < 4; ++i) res.v[i] = v[i] + o.v[i];
    return res;
}
Mat2  Mat2::operator-(const Mat2& o) const{
    Mat2 res;
    for (int i = 0; i < 4; ++i) res.v[i] = v[i] - o.v[i];
    return res;
}

Mat2  Mat2::operator*(float s) const{
    Mat2 res;
    for (int i = 0; i < 4; ++i) res.v[i] = v[i] * s;
    return res;
}
Mat2  Mat2::operator*(const Mat2& o) const{
    Mat2 res = {};
    for (int r = 0; r < 2; ++r) {
        for (int c = 0; c < 2; ++c) {
            for (int k = 0; k < 2; ++k) {
                res.m[r][c] += m[r][k] * o.m[k][c];
            }
        }
    }
    return res;
}

Vec2  Mat2::operator*(const Vec2& vec) const{
    return Vec2{
        m[0][0]*vec.x + m[0][1]*vec.y,
        m[1][0]*vec.x + m[1][1]*vec.y,

    };
}

Mat2& Mat2::operator*=(const Mat2& o){
    *this = *this * o;
    return *this;
}


float* Mat3::operator[](int row){
    return m[row];
}

const float* Mat3::operator[](int row) const{
    return m[row];
}

Mat3  Mat3::operator+(const Mat3& o) const{
    Mat3 res;
    for (int i = 0; i < 9; ++i) res.v[i] = v[i] + o.v[i];
    return res;
}
Mat3  Mat3::operator-(const Mat3& o) const{
    Mat3 res;
    for (int i = 0; i < 9; ++i) res.v[i] = v[i] - o.v[i];
    return res;
}

Mat3  Mat3::operator*(float s) const{
    Mat3 res;
    for (int i = 0; i < 9; ++i) res.v[i] = v[i] * s;
    return res;
}
Mat3  Mat3::operator*(const Mat3& o) const{
    Mat3 res = {};
    for (int r = 0; r < 3; ++r) {
        for (int c = 0; c < 3; ++c) {
            for (int k = 0; k < 3; ++k) {
                res.m[r][c] += m[r][k] * o.m[k][c];
            }
        }
    }
    return res;
}

Vec3  Mat3::operator*(const Vec3& vec) const{
    return Vec3{
        m[0][0]*vec.x + m[0][1]*vec.y + m[0][2]*vec.z,
        m[1][0]*vec.x + m[1][1]*vec.y + m[1][2]*vec.z,
        m[2][0]*vec.x + m[2][1]*vec.y + m[2][2]*vec.z
    };
}

Mat3& Mat3::operator*=(const Mat3& o){
    *this = *this * o;
    return *this;
}

float* Mat4::operator[](int row){
    return m[row];
}

const float* Mat4::operator[](int row) const{
    return m[row];
}

Mat4  Mat4::operator+(const Mat4& o) const{
    Mat4 res;
    for (int i = 0; i < 16; ++i) res.v[i] = v[i] + o.v[i];
    return res;
}
Mat4  Mat4::operator-(const Mat4& o) const{
    Mat4 res;
    for (int i = 0; i < 16; ++i) res.v[i] = v[i] - o.v[i];
    return res;
}

Mat4  Mat4::operator*(float s) const{
    Mat4 res;
    for (int i = 0; i < 16; ++i) res.v[i] = v[i] * s;
    return res;
}
Mat4  Mat4::operator*(const Mat4& o) const{
    Mat4 res = {};
    for (int r = 0; r < 4; ++r) {
        for (int c = 0; c < 4; ++c) {
            for (int k = 0; k < 4; ++k) {
                res.m[r][c] += m[r][k] * o.m[k][c];
            }
        }
    }
    return res;
}

Vec4  Mat4::operator*(const Vec4& vec) const{
    return Vec4{
        m[0][0]*vec.x + m[0][1]*vec.y + m[0][2]*vec.z + m[0][3]*vec.w,
        m[1][0]*vec.x + m[1][1]*vec.y + m[1][2]*vec.z + m[1][3]*vec.w,
        m[2][0]*vec.x + m[2][1]*vec.y + m[2][2]*vec.z + m[2][3]*vec.w,
        m[3][0]*vec.x + m[3][1]*vec.y + m[3][2]*vec.z + m[3][3]*vec.w
    };
}

Mat4& Mat4::operator*=(const Mat4& o){
    *this = *this * o;
    return *this;
}

}
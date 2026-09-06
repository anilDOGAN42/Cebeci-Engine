#pragma once
#include <cmath>
#include "glm/glm.hpp"

namespace CebeciEngine::Core::Math {

struct Vec2;
struct Vec3;
struct Vec4;

struct Vec2 {
    float x{ 0.0f }, y{ 0.0f };

    Vec2() = default;
    Vec2(float x, float y) : x(x), y(y) {}
    Vec2(float scalar) : x(scalar), y(scalar) {}

    Vec2(const glm::vec2& v) : x(v.x), y(v.y) {}
    operator glm::vec2() const { return glm::vec2(x, y); }
    operator glm::vec3() const { return glm::vec3(x, y, 0.0f); }
    operator glm::vec4() const { return glm::vec4(x, y, 0.0f, 0.0f); }

    operator Vec3() const;
    operator Vec4() const;

    Vec2 operator+(const Vec2& o) const { return Vec2(x + o.x, y + o.y); }
    Vec2 operator-(const Vec2& o) const { return Vec2(x - o.x, y - o.y); }
    Vec2 operator*(const Vec2& o) const { return Vec2(x * o.x, y * o.y); }
    Vec2 operator/(const Vec2& o) const { return Vec2(x / o.x, y / o.y); }

    Vec2 operator*(float s) const { return Vec2(x * s, y * s); }
    Vec2 operator/(float s) const { return Vec2(x / s, y / s); }

    Vec2 operator-() const { return Vec2(-x, -y); }

    Vec2& operator+=(const Vec2& o) { x += o.x; y += o.y; return *this; }
    Vec2& operator-=(const Vec2& o) { x -= o.x; y -= o.y; return *this; }
    Vec2& operator*=(const Vec2& o) { x *= o.x; y *= o.y; return *this; }
    Vec2& operator/=(const Vec2& o) { x /= o.x; y /= o.y; return *this; }
    Vec2& operator*=(float s)       { x *= s; y *= s; return *this; }
    Vec2& operator/=(float s)       { x /= s; y /= s; return *this; }

    float lengthSqr() const { return x * x + y * y; }
    float length() const    { return std::sqrt(lengthSqr()); }
    Vec2 normalized() const { float len = length(); return len > 0.0f ? *this / len : Vec2(0.0f); }
    float dot(const Vec2& o) const { return x * o.x + y * o.y; }
};

struct Vec3 {
    float x{ 0.0f }, y{ 0.0f }, z{ 0.0f };

    Vec3() = default;
    Vec3(float x, float y, float z) : x(x), y(y), z(z) {}
    Vec3(float scalar) : x(scalar), y(scalar), z(scalar) {}

    Vec3(const glm::vec3& v) : x(v.x), y(v.y), z(v.z) {}
    operator glm::vec2() const { return glm::vec2(x, y); }
    operator glm::vec3() const { return glm::vec3(x, y, z); }
    operator glm::vec4() const { return glm::vec4(x, y, z, 0.0f); }

    operator Vec2() const;
    operator Vec4() const;

    Vec3 operator+(const Vec3& o) const { return Vec3(x + o.x, y + o.y, z + o.z); }
    Vec3 operator-(const Vec3& o) const { return Vec3(x - o.x, y - o.y, z - o.z); }
    Vec3 operator*(const Vec3& o) const { return Vec3(x * o.x, y * o.y, z * o.z); }
    Vec3 operator/(const Vec3& o) const { return Vec3(x / o.x, y / o.y, z / o.z); }

    Vec3 operator*(float s) const { return Vec3(x * s, y * s, z * s); }
    Vec3 operator/(float s) const { return Vec3(x / s, y / s, z / s); }

    Vec3 operator-() const { return Vec3(-x, -y, -z); }

    Vec3& operator+=(const Vec3& o) { x += o.x; y += o.y; z += o.z; return *this; }
    Vec3& operator-=(const Vec3& o) { x -= o.x; y -= o.y; z -= o.z; return *this; }
    Vec3& operator*=(const Vec3& o) { x *= o.x; y *= o.y; z *= o.z; return *this; }
    Vec3& operator/=(const Vec3& o) { x /= o.x; y /= o.y; z /= o.z; return *this; }
    Vec3& operator*=(float s)       { x *= s; y *= s; z *= s; return *this; }
    Vec3& operator/=(float s)       { x /= s; y /= s; z /= s; return *this; }


    float lengthSqr() const { return x * x + y * y + z * z; }
    float length() const    { return std::sqrt(lengthSqr()); }
    Vec3 normalized() const { float len = length(); return len > 0.0f ? *this / len : Vec3(0.0f); }
    float dot(const Vec3& o) const { return x * o.x + y * o.y + z * o.z; }
    Vec3 cross(const Vec3& o) const {
        return Vec3(
            y * o.z - z * o.y,
            z * o.x - x * o.z,
            x * o.y - y * o.x
        );
    }
};

struct Vec4 {
    float x{ 0.0f }, y{ 0.0f }, z{ 0.0f }, w{ 0.0f };

    Vec4() = default;
    Vec4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
    Vec4(float scalar) : x(scalar), y(scalar), z(scalar), w(scalar) {}

    Vec4(const glm::vec4& v) : x(v.x), y(v.y), z(v.z), w(v.w) {}
    operator glm::vec2() const { return glm::vec2(x, y); }
    operator glm::vec3() const { return glm::vec3(x, y, z); }
    operator glm::vec4() const { return glm::vec4(x, y, z, w); }

    operator Vec2() const;
    operator Vec3() const;

    Vec4 operator+(const Vec4& o) const { return Vec4(x + o.x, y + o.y, z + o.z, w + o.w); }
    Vec4 operator-(const Vec4& o) const { return Vec4(x - o.x, y - o.y, z - o.z, w - o.w); }
    Vec4 operator*(const Vec4& o) const { return Vec4(x * o.x, y * o.y, z * o.z, w * o.w); }
    Vec4 operator/(const Vec4& o) const { return Vec4(x / o.x, y / o.y, z / o.z, w / o.w); }

    Vec4 operator*(float s) const { return Vec4(x * s, y * s, z * s, w * s); }
    Vec4 operator/(float s) const { return Vec4(x / s, y / s, z / s, w / s); }


    Vec4 operator-() const { return Vec4(-x, -y, -z, -w); }

    Vec4& operator+=(const Vec4& o) { x += o.x; y += o.y; z += o.z; w += o.w; return *this; }
    Vec4& operator-=(const Vec4& o) { x -= o.x; y -= o.y; z -= o.z; w -= o.w; return *this; }
    Vec4& operator*=(const Vec4& o) { x *= o.x; y *= o.y; z *= o.z; w *= o.w; return *this; }
    Vec4& operator/=(const Vec4& o) { x /= o.x; y /= o.y; z /= o.z; w /= o.w; return *this; }
    Vec4& operator*=(float s)       { x *= s; y *= s; z *= s; w *= s; return *this; }
    Vec4& operator/=(float s)       { x /= s; y /= s; z /= s; w /= s; return *this; }


    float lengthSqr() const { return x * x + y * y + z * z + w * w; }
    float length() const    { return std::sqrt(lengthSqr()); }
    Vec4 normalized() const { float len = length(); return len > 0.0f ? *this / len : Vec4(0.0f); }
    float dot(const Vec4& o) const { return x * o.x + y * o.y + z * o.z + w * o.w; }
};
    
inline Vec2 operator*(float s, const Vec2& v) { return v * s; }
inline Vec3 operator*(float s, const Vec3& v) { return v * s; }
inline Vec4 operator*(float s, const Vec4& v) { return v * s; }


using vec2 = Vec2;
using vec3 = Vec3;
using vec4 = Vec4;

} 
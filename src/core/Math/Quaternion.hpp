#pragma once
#include "vector.hpp"

namespace CebeciEngine::Core::Math {

class Quaternion {
public:
    Vec4 v{0.0f, 0.0f, 0.0f, 1.0f};

    Quaternion() = default;

    Quaternion(float x, float y, float z, float w)
        : v{x, y, z, w} {}

    explicit Quaternion(const Vec4& vec)
        : v(vec) {}

    static Quaternion Identity();

    static Quaternion FromAxisAngle(
        const Vec3& axis,
        float angleRadians
    );

    static Quaternion FromEuler(
        const Vec3& eulerDegrees
    );

    Vec3 toEuler() const;

    Quaternion operator*(const Quaternion& q) const;

    Vec3 operator*(const Vec3& vec) const;

    float lengthSqr() const {
        return v.lengthSqr();
    }

    float length() const {
        return v.length();
    }

    void normalize();

    Quaternion normalized() const;

    Quaternion conjugate() const;
};

}
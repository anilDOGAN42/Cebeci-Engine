#include "Quaternion.hpp"
#include "MathUtils.hpp"
#include <cmath>

namespace CebeciEngine::Core::Math {

Quaternion Quaternion::Identity() {
    return Quaternion(0.0f, 0.0f, 0.0f, 1.0f);
}

Quaternion Quaternion::FromAxisAngle(
    const Vec3& axis,
    float angleRadians
) {
    Vec3 normAxis = axis.normalized();

    float halfAngle = angleRadians * 0.5f;

    float sinHalf = std::sin(halfAngle);
    float cosHalf = std::cos(halfAngle);

    return Quaternion(
        normAxis.x * sinHalf,
        normAxis.y * sinHalf,
        normAxis.z * sinHalf,
        cosHalf
    );
}

Quaternion Quaternion::FromEuler(
    const Vec3& eulerDegrees
) {
    float pitch = ToRadians(eulerDegrees.x) * 0.5f;
    float yaw   = ToRadians(eulerDegrees.y) * 0.5f;
    float roll  = ToRadians(eulerDegrees.z) * 0.5f;

    float cx = std::cos(pitch);
    float sx = std::sin(pitch);

    float cy = std::cos(yaw);
    float sy = std::sin(yaw);

    float cz = std::cos(roll);
    float sz = std::sin(roll);

    float w =
        cy * cx * cz +
        sy * sx * sz;

    float x =
        cy * sx * cz +
        sy * cx * sz;

    float y =
        sy * cx * cz -
        cy * sx * sz;

    float z =
        cy * cx * sz -
        sy * sx * cz;

    return Quaternion(x, y, z, w);
}

Quaternion Quaternion::operator*(
    const Quaternion& q
) const {
    return Quaternion(
        v.w * q.v.x +
        v.x * q.v.w +
        v.y * q.v.z -
        v.z * q.v.y,

        v.w * q.v.y -
        v.x * q.v.z +
        v.y * q.v.w +
        v.z * q.v.x,

        v.w * q.v.z +
        v.x * q.v.y -
        v.y * q.v.x +
        v.z * q.v.w,

        v.w * q.v.w -
        v.x * q.v.x -
        v.y * q.v.y -
        v.z * q.v.z
    );
}

Vec3 Quaternion::operator*(const Vec3& vec) const {
    Vec3 qv(v.x, v.y, v.z);

    Vec3 t = 2.0f * qv.cross(vec);

    return vec +
           (t * v.w) +
           qv.cross(t);
}

void Quaternion::normalize() {
    float len = length();

    if (len > Constants::EPSILON) {
        v /= len;
    } else {
        *this = Identity();
    }
}

Quaternion Quaternion::normalized() const {
    Quaternion q = *this;
    q.normalize();
    return q;
}

Quaternion Quaternion::conjugate() const {
    return Quaternion(
        -v.x,
        -v.y,
        -v.z,
         v.w
    );
}

Vec3 Quaternion::toEuler() const {
    Quaternion q = normalized();

    float x = q.v.x;
    float y = q.v.y;
    float z = q.v.z;
    float w = q.v.w;

    float sinp = 2.0f * (w * x - y * z);

    float pitch;

    if (std::abs(sinp) >= 1.0f) {
        pitch = std::copysign(
            Constants::HALF_PI,
            sinp
        );
    } else {
        pitch = std::asin(sinp);
    }

    float yaw = std::atan2(
        2.0f * (w * y + z * x),
        1.0f - 2.0f * (x * x + y * y)
    );

    float roll = std::atan2(
        2.0f * (w * z + x * y),
        1.0f - 2.0f * (x * x + z * z)
    );

    return Vec3(
        ToDegrees(pitch),
        ToDegrees(yaw),
        ToDegrees(roll)
    );
}

}
#pragma once
#include <cmath>

namespace CebeciEngine::Core::Math {

namespace Constants {
    inline constexpr float PI         = 3.14159265358979323846f;
    inline constexpr float TWO_PI     = 6.28318530717958647692f;
    inline constexpr float HALF_PI    = 1.57079632679489661923f;
    inline constexpr float SQRT_2     = 1.41421356237309504880f;

    inline constexpr float DEG2RAD    = PI / 180.0f;
    inline constexpr float RAD2DEG    = 180.0f / PI;

    inline constexpr float EPSILON    = 0.00001f;
}

inline constexpr float ToRadians(float degrees) {
    return degrees * Constants::DEG2RAD;
}

inline constexpr float ToDegrees(float radians) {
    return radians * Constants::RAD2DEG;
}

inline constexpr float DegToRad(float degrees) { return ToRadians(degrees); }
inline constexpr float RadToDeg(float radians) { return ToDegrees(radians); }

template <typename T>
inline constexpr T Clamp(T val, T min, T max) {
    return (val < min) ? min : ((val > max) ? max : val);
}

template <typename T>
inline constexpr T Lerp(T a, T b, float t) {
    return a + static_cast<T>((b - a) * t);
}

inline constexpr float InverseLerp(float a, float b, float value) {
    return (std::abs(b - a) > Constants::EPSILON) ? (value - a) / (b - a) : 0.0f;
}

inline float SmoothStep(float edge0, float edge1, float x) {
    float t = Clamp(InverseLerp(edge0, edge1, x), 0.0f, 1.0f);
    return t * t * (3.0f - 2.0f * t);
}

inline bool Equals(float a, float b, float maxDiff = Constants::EPSILON) {
    return std::abs(a - b) <= maxDiff;
}

}
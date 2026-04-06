#include "vector.hpp"

vec2::operator vec3() {
    return {x, y, 0.0f};
}

vec2::operator vec4() {
    return {x, y, 0.0f, 0.0f};
}

vec3::operator vec2() {
    return {x, y};
}

vec3::operator vec4() {
    return {x, y, z, 0.0f};
}

vec4::operator vec3() {
    return {x, y, z};
}

vec4::operator vec2() {
    return {x, y};
}


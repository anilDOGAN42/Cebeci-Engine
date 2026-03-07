#include "vector.hpp"

vec2::vec2(float x, float y): x(x),y(y){}
vec3::vec3(float x, float y,float z): x(x),y(y),z(z){}
vec4::vec4(float x, float y,float z, float w): x(x),y(y),z(z),w(w){}

vec2::operator vec3() {
    return vec3(x, y, 0.0f);
}

vec2::operator vec4() {
    return vec4(x, y, 0.0f, 0.0f);
}

vec3::operator vec2() {
    return vec2(x, y);
}

vec3::operator vec4() {
    return vec4(x, y, z, 0.0f);
}

vec4::operator vec3() {
    return vec3(x, y, z);
}

vec4::operator vec2() {
    return vec2(x, y);
}


#pragma once
#include "glm/glm.hpp"

struct Vec2;
struct Vec3;
struct Vec4;

typedef struct Vec2{
public:
    float x,y;
    operator glm::vec2() {
        return glm::vec2(x,y);
    }
    operator glm::vec3() {
        return glm::vec3(x,y,0);
    }
    operator glm::vec4() {
        return glm::vec4(x,y,0,0);
    }
    operator Vec3() ;
    operator Vec4() ;

}vec2;

typedef struct Vec3{
public:

    float x,y,z;
    operator glm::vec2() {
        return glm::vec2(x,y);
    }
    operator glm::vec3() {
        return glm::vec3(x,y,z);
    }
    operator glm::vec4() {
        return glm::vec4(x,y,z,0);
    }
    operator Vec2();
    operator Vec4();

}vec3;
typedef struct Vec4{
public:
    
    float x,y,z,w;
    operator glm::vec2() {
        return glm::vec2(x,y);
    }
    operator glm::vec3() {
        return glm::vec3(x,y,z);
    }
    operator glm::vec4() {
        return glm::vec4(x,y,z,w);
    }
    operator Vec2();
    operator Vec3();
}vec4;
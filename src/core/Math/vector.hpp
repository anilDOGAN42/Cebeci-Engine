#pragma once
#include "glm/glm.hpp"


class vec2;
class vec3;
class vec4;

class vec2{
public:
    vec2(float x=0,float y=0);
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
    operator vec3() ;
    operator vec4() ;

};

class vec3{
public:
    vec3(float x=0,float y=0,float z=0);
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
    operator vec2();
    operator vec4();

};

class vec4{
public:
    vec4(float x=0,float y=0,float z=0,float w=0);
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
    operator vec2();
    operator vec3();
};
#pragma once
#include "glm/fwd.hpp"
#include <glm/glm.hpp>
#include <glad/glad.h>
#include <Object.hpp>

namespace CebeciEngine::Render::Camera{
class camera:public CebeciEngine::Core::App::Object::Object{
public:
    virtual void calculate();

    virtual glm::mat4 getProjection();
    virtual glm::mat4 getView();

    glm::vec3 camPosition={0,0,0};

    glm::vec3 camRotation={0,0,0};

    glm::mat4 projection;
    glm::mat4 view;


    virtual ~camera();
};

class camera3D: public camera {
public:
    camera3D(float zFar,float pov);
    ~camera3D()=default;

    void calculate() override;
    glm::mat4 getProjection() override;
    glm::mat4 getView() override;

    float zFar;
    float pov;

};

class camera2D: public camera {
public:
    camera2D(float left,float right,float top,float bottom,float zFar);
    ~camera2D()=default;

    void calculate() override;
    glm::mat4 getProjection() override;
    glm::mat4 getView() override;

    float left;
    float right;
    float top;
    float bottom;
    float zFar;

};
}
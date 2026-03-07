#pragma once
#include "glm/fwd.hpp"
#include <glm/glm.hpp>
#include <glad/glad.h>

class camera{
public:
    virtual void calculate();

    virtual glm::mat4 getProjection();
    virtual glm::mat4 getView();

    glm::vec3 camPosition={0,0,0};

    glm::vec3 camRotation={0,0,0};

    glm::mat4 projection;
    glm::mat4 view;

};

class camera3D: public camera {
public:
    camera3D(float zFar);

    void calculate() override;
    glm::mat4 getProjection() override;
    glm::mat4 getView() override;

private:
    float zFar;

};

class camera2D: public camera {
public:
    camera2D(float zFar);

    void calculate() override;
    glm::mat4 getProjection() override;
    glm::mat4 getView() override;

private:
    float zFar;

};

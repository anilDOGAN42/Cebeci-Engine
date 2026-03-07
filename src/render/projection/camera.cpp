#include "camera.hpp"
#include "glm/fwd.hpp"
#include "glm/geometric.hpp"
#include "glm/trigonometric.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "application.hpp"

void camera::calculate() {}

glm::mat4 camera::getProjection() { 
    return glm::mat4(1.0f);
}

glm::mat4 camera::getView() { 
    return glm::mat4(1.0f);
}

camera3D::camera3D(float zFar){
    this->zFar=zFar;
}

void camera3D::calculate() {
    glm::vec3 forward;

    float pitch = glm::radians(camRotation.x);
    float yaw   = glm::radians(camRotation.y);

    forward.x = cos(pitch) * sin(yaw);
    forward.y = sin(pitch);
    forward.z = cos(pitch) * cos(yaw);

    forward = glm::normalize(forward);

    glm::vec3 sum = camPosition + forward;

    view = glm::lookAt(camPosition,sum,glm::vec3(0.0f, 1.0f, 0.0f));

    projection = glm::perspective(glm::radians(45.0f), App::instance().getScreenRatio(),0.1f,zFar);
}

glm::mat4 camera3D::getProjection(){
    return projection;
}

glm::mat4 camera3D::getView(){
    return view;
}

void camera2D::calculate() {
    glm::vec3 forward;

    float pitch = glm::radians(camRotation.x);
    float yaw   = glm::radians(camRotation.y);

    forward.x = cos(pitch) * sin(yaw);
    forward.y = sin(pitch);
    forward.z = cos(pitch) * cos(yaw);

    forward = glm::normalize(forward);

    glm::vec3 sum = camPosition + forward;

    view = glm::lookAt(camPosition,sum,glm::vec3(0.0f, 1.0f, 0.0f));

    projection = glm::perspective(glm::radians(45.0f), App::instance().getScreenRatio(),0.1f,zFar);
}

glm::mat4 camera2D::getProjection(){
    return projection;
}

glm::mat4 camera2D::getView(){
    return view;
}
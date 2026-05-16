#include "camera.hpp"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/fwd.hpp"
#include "glm/geometric.hpp"
#include "glm/matrix.hpp"
#include "glm/trigonometric.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "application.hpp"

namespace CebeciEngine::Render::Camera{
void camera::calculate() {}

camera::~camera(){
    
}

glm::mat4 camera::getProjection() { 
    return glm::mat4(1.0f);
}

glm::mat4 camera::getView() { 
    return glm::mat4(1.0f);
}

camera3D::camera3D(float zFar,float pov){
    this->zFar=zFar;
    this->pov=pov;
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

    projection = glm::perspective(glm::radians(pov), Core::App::App::instance().getScreenRatio(),0.1f,zFar);
}

glm::mat4 camera3D::getProjection(){
    return projection;
}

glm::mat4 camera3D::getView(){
    return view;
}

camera2D::camera2D(float left,float right,float top,float bottom,float zFar):left(left),right(right),top(top),bottom(bottom),zFar(zFar){}

void camera2D::calculate() {

    projection = glm::ortho<float>(left,right,bottom,top,-10.0f,zFar);

    glm::mat4 transform = glm::translate(glm::mat4(1.0f), camPosition) *
    glm::rotate(glm::mat4(1.0f), glm::radians(camRotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    
    view=glm::inverse(transform);
}

glm::mat4 camera2D::getProjection(){
    return projection;
}

glm::mat4 camera2D::getView(){
    return view;
}
}
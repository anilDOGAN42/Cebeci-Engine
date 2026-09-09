#include <Mesh.hpp>
#include "Matrix.hpp"
#include "ObjectManager.hpp"
#include "VBO.hpp"
#include "camera.hpp"
#include "texture.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include "application.hpp"
#include "transform.hpp"

static CebeciEngine::Core::App::App& app=CebeciEngine::Core::App::App::instance();

namespace CebeciEngine::Render {
Mesh::Mesh(std::vector<vertex> verticies){
    isSingleton=true;
    this->shaderProgram=app.getShaderProgramID();

    this->verticies=verticies;
    this->changeVerticies(&this->verticies);
}

Mesh::~Mesh(){
}


void Mesh::changeTexture(Texture::Texture2D* texture){
    this->texture=texture;
}

void Mesh::draw(){
    Core::Transform* t=this->getParent()->getChildByType<Core::Transform>();

    Mat4 transform=t->getWorldMatrix();
    Camera::camera* cam=app.getActiveScenes().at(0)->getActiveCamera();

    GLint transformLoc = glGetUniformLocation(shaderProgram, "transform");    
    glUniformMatrix4fv(transformLoc,1,GL_TRUE,transform.v);

    GLint uTextureLoc=glGetUniformLocation(shaderProgram, "uTexture");
    glUniform1i(uTextureLoc,0);

    cam->lock();

    GLint projection = glGetUniformLocation(shaderProgram, "projection");    
    glUniformMatrix4fv(projection,1,GL_FALSE,glm::value_ptr(cam->getProjection()));

    GLint view = glGetUniformLocation(shaderProgram, "view");    
    glUniformMatrix4fv(view,1,GL_FALSE,glm::value_ptr(cam->getView()));

    cam->unlock();

    texture->bind();

    vao.use();
    vbo.draw();
}

void Mesh::changeVerticies(std::vector<vertex>* verticies){
    vao.use();
    vbo.changeData(verticies->data(), verticies->size());
    vao.attribute();
}

std::vector<vertex>* Mesh::getVerticies(){
    return &this->verticies;
}
}
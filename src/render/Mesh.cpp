#include <Mesh.hpp>
#include "ObjectManager.hpp"
#include "SSBO.hpp"
#include "VBO.hpp"
#include "camera.hpp"
#include "glm/fwd.hpp"
#include "texture.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include "application.hpp"
#include "transform.hpp"

static CebeciEngine::Core::App::App& app=CebeciEngine::Core::App::App::instance();

namespace CebeciEngine::Render {
Mesh::Mesh(std::vector<vertex> verticies){
    isSingleton=true;
    transforms=new SSBO(0);
    this->shaderProgram=app.getShaderProgramID();

    this->verticies=verticies;
    this->changeVerticies(&this->verticies);
}

Mesh::~Mesh(){
    delete transforms;
}


void Mesh::changeTexture(Texture::Texture2D* texture){
    this->texture=texture;
}

void Mesh::draw(){
    std::vector<glm::mat4> Transforms;
    node* parent=dynamic_cast<node*>(this->getParent());

    Camera::camera* cam=app.getActiveScene()->getActiveCamera();

    do {
        Transforms.push_back(*(parent)->getComponentByType<Core::transform>());
        Object* p=parent->getParent();
        if(p!=nullptr){
            parent=dynamic_cast<node*>(p);
        }
        else break;
    }while(parent!=nullptr);

    transforms->changeData<glm::mat4,glm::mat4>(&Transforms);
    transforms->bind();

    GLint transformCountLoc = glGetUniformLocation(shaderProgram, "transformCount");    
    glUniform1i(transformCountLoc, Transforms.size());

    GLint uTextureLoc=glGetUniformLocation(shaderProgram, "uTexture");
    glUniform1i(uTextureLoc,0);

    GLint projection = glGetUniformLocation(shaderProgram, "projection");    
    glUniformMatrix4fv(projection,1,GL_FALSE,glm::value_ptr(cam->getProjection()));

    GLint view = glGetUniformLocation(shaderProgram, "view");    
    glUniformMatrix4fv(view,1,GL_FALSE,glm::value_ptr(cam->getView()));

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
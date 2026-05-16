#include "node.hpp"
#include "Mesh.hpp"
#include "transform.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include "application.hpp"

static CebeciEngine::Core::App::App& app=CebeciEngine::Core::App::App::instance();
namespace CebeciEngine::Core {

node::~node(){
    
}

void node::changeMesh(Mesh* mesh){
    this->mesh=mesh;
    mesh->changeNode(this);
}

Mesh* node::getMesh(){
    return mesh;
}

node* node::getParent(){
    return Parent;
}

void node::setParent(node* Parent){
    this->Parent=Parent;
    Parent->addChild(this);
}
    
transform* node::getTransform(){
    return &(this->Transform);
}

void node::addChild(node* Child){
    this->childs.push_back(Child);
}
}
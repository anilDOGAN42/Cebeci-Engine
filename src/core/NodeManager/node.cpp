#include "node.hpp"
#include "Mesh.hpp"
#include "transform.hpp"
#include <Object.hpp>


namespace CebeciEngine::Core {

node::node(){
    transform* Transform = new transform;
    this->addComponent(Transform);
    
}
bool node::addComponent(Object* object){

    if(!object->canBeAddedToNode()) return false;

    Object::addComponent(object);

    return true;
}

}
#include "node.hpp"
#include "Mesh.hpp"
#include "transform.hpp"
#include <Object.hpp>


namespace CebeciEngine::Core {

node::node(){
    transform* Transform = new transform;
    this->addChild(Transform);
    
}
bool node::addChild(Object* object){

    if(!object->canBeAddedToNode()) return false;

    Object::addChild(object);

    return true;
}

}
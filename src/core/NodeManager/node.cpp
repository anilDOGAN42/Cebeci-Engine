#include "node.hpp"
#include "Mesh.hpp"
#include "transform.hpp"
#include <Object.hpp>


namespace CebeciEngine::Core {

node::node(){
    Transform* transform = new Transform;
    this->addChild(transform);
    
}
bool node::addChild(Object* object){

    if(!object->canBeAddedToNode()) return false;

    Object::addChild(object);

    return true;
}

}
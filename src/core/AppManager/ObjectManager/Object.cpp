#include <ObjectManager.hpp>
#include <Object.hpp>
#include <algorithm>
#include <vector>

static CebeciEngine::Core::App::Object::ObjectManager& objectManager=CebeciEngine::Core::App::Object::ObjectManager::instance();

namespace CebeciEngine::Core::App::Object {
Object::Object(){
    objectManager.addObject(this);
    this->parent=nullptr;
}

Object::~Object(){
    if(this->parent != nullptr) {
        this->parent->removeComponent(this);
        this->parent=nullptr;
    }

    for(Object* component:Components){
        component->parent=nullptr;
        delete component;
    }

    Components.clear();

    objectManager.removeObject(this);
}


void Object::addTag(std::string tagName){
    this->tags.push_back(tagName);

    objectManager.ObjectsByTagList[tagName].push_back(this);
}


bool Object::removeTag(std::string tagName){
    auto tag=std::find(this->tags.begin(),this->tags.end(),tagName);

    if(tag==this->tags.end()){
        return false;
    }

    this->tags.erase(tag);

    std::vector<Object*>& tagList=objectManager.ObjectsByTagList[tagName];

    auto objectAtTagList=std::find(tagList.begin(),tagList.end(),this);

    if(objectAtTagList==tagList.end()){
        return false;
    }

    tagList.erase(objectAtTagList);

    return true;
}

bool Object::addComponent(Object* object){
    if(object->isSingleton){
        for(Object* o:Components){
            if(typeid(*o)==typeid(*object))
                return false;
        }
    }
    Components.push_back(object);
    object->parent=this;
    return true;
}

bool Object::removeComponent(Object* object){

    auto objectAtComponents=std::find(Components.begin(),Components.end(),object);

    if(objectAtComponents==Components.end())
        return false;

    Components.erase(objectAtComponents);
    
    return true;
}

Object* Object::getComponent(std::string name){
    for(Object* o:Components){
        if(o->name==name)
            return o;
    }
    return nullptr;
}

Object* Object::getComponent(unsigned int id){
    for(Object* o:Components){
        if(o->id==id)
            return o;
    }
    return nullptr;
}

Object* Object::getParent(){
    return parent;
}
    
bool Object::setParent(Object* parent){
    if(this->parent!=nullptr)
        this->parent->removeComponent(this);

    this->parent=parent;

    if(parent == nullptr)
        return true;

    return parent->addComponent(this);;
}


}
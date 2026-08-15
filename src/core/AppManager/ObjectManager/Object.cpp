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
        this->parent->removeChild(this);
        this->parent=nullptr;
    }

    for(Object* component:Childs){
        component->parent=nullptr;
        delete component;
    }

    Childs.clear();

    objectManager.removeObject(this);
}


void Object::addTag(std::string tagName){
    this->tags.push_back(tagName);

    objectManager.ObjectsByTag[tagName].push_back(this);
}


bool Object::removeTag(std::string tagName){
    auto tag=std::find(this->tags.begin(),this->tags.end(),tagName);

    if(tag==this->tags.end()){
        return false;
    }

    this->tags.erase(tag);

    std::vector<Object*>& tagList=objectManager.ObjectsByTag[tagName];

    auto objectAtTagList=std::find(tagList.begin(),tagList.end(),this);

    if(objectAtTagList==tagList.end()){
        return false;
    }

    tagList.erase(objectAtTagList);

    return true;
}

bool Object::addChild(Object* object){
    if(object->isSingleton){
        for(Object* o:Childs){
            if(typeid(*o)==typeid(*object))
                return false;
        }
    }
    Childs.push_back(object);
    object->parent=this;
    return true;
}

bool Object::removeChild(Object* object){

    auto objectAtChilds=std::find(Childs.begin(),Childs.end(),object);

    if(objectAtChilds==Childs.end())
        return false;

    Childs.erase(objectAtChilds);
    
    return true;
}

Object* Object::getChild(std::string name){
    for(Object* o:Childs){
        if(o->name==name)
            return o;
    }
    return nullptr;
}

Object* Object::getChild(unsigned int id){
    for(Object* o:Childs){
        if(o->id==id)
            return o;
    }
    return nullptr;
}

bool Object::canBeAddedToNode(){
    return isNodeComponent;
}

Object* Object::getParent(){
    return parent;
}
    
bool Object::setParent(Object* parent){
    if(this->parent!=nullptr)
        this->parent->removeChild(this);

    this->parent=parent;

    if(parent == nullptr)
        return true;

    return parent->addChild(this);;
}

void Object::lock() {
    mtx.lock();
}

void Object::unlock(){
    mtx.unlock();
}

bool Object::isActive(){
    return this->active;
}

void Object::activate(){
    this->active=true;
}
void Object::deactivate(){
    this->active=false;
}

}
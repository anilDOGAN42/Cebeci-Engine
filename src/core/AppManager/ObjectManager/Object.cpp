#include <ObjectManager.hpp>
#include <Object.hpp>
#include <algorithm>
#include <thread>
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

bool Object::canBeAddedToNode(){
    return isNodeComponent;
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

void Object::lock() {
    std::thread::id current_id = std::this_thread::get_id();
        
    if (ownerThread.load(std::memory_order_relaxed) == current_id) {
        recursionCount++;
        return;
    }

    mtx.lock();
    ownerThread.store(current_id, std::memory_order_relaxed);
    recursionCount = 1;
}

void Object::unlock(){
    recursionCount--;
    if(recursionCount==0){
        ownerThread.store(std::thread::id{},std::memory_order_release);
    }
    mtx.unlock();
}

Object* Object::operator->(){
    while(1){
        if(std::this_thread::get_id()==ownerThread || ownerThread==std::thread::id{}) return this;
        std::this_thread::yield();
    }
}

}
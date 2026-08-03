#include "ObjectManager.hpp"
#include <Object.hpp>
#include <string.h>
#include <vector>

namespace CebeciEngine::Core::App::Object {
ObjectManager& ObjectManager::instance(){
    static ObjectManager instance;
    return instance;
}

void ObjectManager::addObject(Object* object){
    ObjectsMutex.lock();

    Objects.push_back(object);
    for(std::string tag:object->tags){
        ObjectsByTag[tag].push_back(object);
    }

    object->id=this->avaibleID;
    this->avaibleID++;

    ObjectsMutex.unlock();
}

void ObjectManager::removeObject(Object* object){
    ObjectsMutex.lock();

    for(size_t i=0;i<Objects.size();i++){
        if(Objects.at(i)==object){
            Objects.erase(Objects.begin()+i);
        }
    }
    ObjectsMutex.unlock();
    

    ObjectsByTagMutex.lock();

    for(std::string tag:object->tags){
        std::vector<Object*> list=ObjectsByTag[tag];
        for(size_t i=0;i<list.size();i++){
            if(list[i]==object)
                list.erase(list.begin()+i);
        }
    }
    ObjectsByTagMutex.unlock();
}


void ObjectManager::deleteAllObjects(){   
    while(Objects.size()!=0){
        Object* obj=Objects[0];   

        delete obj;
    }
}

std::vector<Object*>& ObjectManager::getObjectsByTag(std::string tagName){
    ObjectsByTagMutex.lock();

    return ObjectsByTag[tagName];

    ObjectsByTagMutex.unlock();
}
}
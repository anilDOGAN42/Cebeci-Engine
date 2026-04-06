#include <ObjectManager.hpp>
#include <Object.hpp>
#include <string.h>

ObjectManager& ObjectManager::instance(){
    static ObjectManager instance;
    return instance;
}

void ObjectManager::addObject(Object* object){
    Objects.push_back(object);
    for(std::string tag:object->tags){
        ObjectsByTagList[tag].push_back(object);
    }
}

void ObjectManager::removeObject(Object* object){
    for(size_t i=0;i<Objects.size();i++){
        if(Objects.at(i)==object) Objects.erase(Objects.begin()+i);
    }
    for(std::string tag:object->tags){
        std::vector<Object*> list=ObjectsByTagList[tag];
        for(size_t i=0;i<list.size();i++){
            if(list[i]==object)
                list.erase(list.begin()+i);
        }
    }
}

std::vector<Object*>& ObjectManager::getObjectsByType(){
    return Objects;
}

std::vector<Object*>& ObjectManager::getObjectsByTag(std::string tagName){
    return ObjectsByTagList[tagName];
}
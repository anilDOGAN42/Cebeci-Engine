#include <ObjectManager.hpp>
#include <Object.hpp>
#include <algorithm>
#include <vector>

static CebeciEngine::Core::App::Object::ObjectManager& objectManager=CebeciEngine::Core::App::Object::ObjectManager::instance();

namespace CebeciEngine::Core::App::Object {
Object::Object(){
    objectManager.addObject(this);
}

Object::~Object(){
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
}
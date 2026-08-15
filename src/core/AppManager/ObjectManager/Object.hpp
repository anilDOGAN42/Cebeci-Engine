#pragma once
#include <mutex>
#include <string>
#include <vector>

namespace CebeciEngine::Core::App::Object {
    
template<typename T>
class ObjectPointer;
class Object{
public:
    unsigned long int id;
    std::string name;

    Object();
    virtual ~Object();

    std::vector<std::string> tags;

    void addTag(std::string tagName);

    bool removeTag(std::string name);

    bool addChild(Object* object);
    bool removeChild(Object* object);

    Object* getChild(std::string name);
    Object* getChild(unsigned int id);

    template<typename T>
    T* getChildByType(){
        for(Object* o:Childs){
            if(T* casted=dynamic_cast<T*>(o))
                return casted;
        }
        return nullptr;
    }

    template<typename T>
    std::vector<T*> getChildsByType(){
        std::vector<T*> matchingObjects;
        for(Object* o:Childs){
            if(T* casted=dynamic_cast<T*>(o))
                matchingObjects.push_back(casted);
        }
        return matchingObjects;
    }

    Object* getParent();
    bool canBeAddedToNode();
        
    bool setParent(Object* parent);
        
    void unlock();
    void lock();

    bool isActive();
    void activate();
    void deactivate();

private:
    std::recursive_mutex mtx;

    Object* parent;
    std::vector<Object*> Childs;

    bool active;

protected:
    bool isSingleton=false;
    bool isNodeComponent=true;
};
}
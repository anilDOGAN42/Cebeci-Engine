#pragma once
#include "application.hpp"
#include <Object.hpp>
#include <mutex>
#include <vector>
#include <string>
#include <map>
#include <typeinfo>

namespace CebeciEngine::Core::App{class App;};//forward declaration
namespace CebeciEngine::Core::App::Object {
class ObjectManager{
public:
    static ObjectManager& instance();
    friend class CebeciEngine::Core::App::App;
    friend class CebeciEngine::Core::App::Object::Object;

    ObjectManager(const ObjectManager&) = delete;
    ObjectManager& operator=(const ObjectManager&) = delete;

    void addObject(Object* object);
    void removeObject(Object* object);

    template<typename T>
    T* getObject(unsigned long int id){
        ObjectsMutex.lock();
        for(Object* object:Objects){
            if(object->id==id) {
                ObjectsMutex.unlock();
                return dynamic_cast<T*>(object);
            }
            
        }
        ObjectsMutex.unlock();
        return nullptr;
    }

    template<typename T>
    T* getObject(std::string name){
        ObjectsMutex.lock();

        for(Object* object:Objects){
            if(object->name==name) {
                ObjectsMutex.unlock();
                return dynamic_cast<T*>(object);
            }
        }

        ObjectsMutex.unlock();
        return nullptr;
    }

    template<typename T>
    std::vector<Object*> getObjectsByType(){
        std::vector<Object*> objects;

        ObjectsMutex.lock();

        for(Object* obj:Objects)
            if(typeid(T).hash_code()==typeid(*obj).hash_code()) 
                objects.push_back(obj);
        
        ObjectsMutex.unlock();
        return objects;
    }

    std::vector<Object*>& getObjectsByTag(std::string tagName);

private:
    ObjectManager()=default;

    void deleteAllObjects();

    size_t avaibleID=0;

    std::mutex ObjectsMutex;
    std::vector<Object*> Objects;
    
    std::mutex ObjectsByTagMutex;
    std::map<std::string, std::vector<Object*>> ObjectsByTag;

};
}
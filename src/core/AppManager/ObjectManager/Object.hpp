#pragma once
#include <atomic>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

namespace CebeciEngine::Core::App::Object {
    
template<typename T>
class ObjectLock;
class Object{
public:
    unsigned long int id;
    std::string name;

    Object();
    virtual ~Object();

    std::vector<std::string> tags;

    void addTag(std::string tagName);

    bool removeTag(std::string name);

    bool addComponent(Object* object);
    bool removeComponent(Object* object);

    Object* getComponent(std::string name);
    Object* getComponent(unsigned int id);

    template<typename T>
    T* getComponentByType(){
        for(Object* o:Components){
            if(T* casted=dynamic_cast<T*>(o))
                return casted;
        }
        return nullptr;
    }

    template<typename T>
    std::vector<T*> getComponentsByType(){
        std::vector<T*> matchingObjects;
        for(Object* o:Components){
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

    Object* operator->();

private:
    std::recursive_mutex mtx;
    std::atomic<std::thread::id> ownerThread={ std::thread::id{} };
    unsigned int recursionCount{0};

    Object* parent;
    std::vector<Object*> Components;
protected:
    bool isSingleton=false;
    bool isNodeComponent=true;
};



template<typename T>
class ObjectPointer:public Object{
public:
    ObjectPointer(T* object){
        static_assert(std::is_base_of_v<Object, T>, "Template parameter T must be derived from Object!");
        this->object=object;
    }
        
private:
    class Lock{
        friend class ObjectPointer;
        T* object;
    public:
        Lock(T* object){
            this->object=object;
            object->lock();
        }
        ~Lock(){
            object->unlock();
        }
    };
    T* object;
public:
    Lock operator->(){
        return Lock(object);
    }
        
};
}
    #pragma once
    #include <string>
    #include <vector>

    namespace CebeciEngine::Core::App::Object {
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
        
        bool setParent(Object* parent);
        
    private:
        Object* parent;
        std::vector<Object*> Components;

    protected:
        bool isSingleton=false;
        bool isNodeComponent=true;
    };
    }
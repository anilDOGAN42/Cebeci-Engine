#include "scene.hpp"
#include "camera.hpp"
#include "Mesh.hpp"
#include "node.hpp"
#include <stdlib.h>
#include <vector>

namespace CebeciEngine::Core {
using namespace Render::Camera;

scene::scene(){
    this->isNodeComponent=false;
}

bool scene::setParent(Object* object){
    return false;
}
bool scene::addChild(Object* object){
    if(typeid(*object)!=typeid(node)) return false;

    Object::addChild(object);

    this->Nodes.push_back((node*)object);
    ((node*)object)->addedToScene=true;

    std::vector<node*>childs;

    Object* obj=object;

    do{
        childs=((node*)obj)->getChildsByType<node>();

        if(childs.size()==0){
            obj=obj->getParent();
            continue;
        }
        unsigned int i=0;
        for(;i<childs.size();i++){
            node* child=childs.at(i);
            if(child->addedToScene) continue;

            this->addNode(child);
            child->addedToScene=true;

            obj=child;
            break;
        }
        if(i==childs.size()) obj=obj->getParent(); 

    }while(obj!=this && obj!=nullptr);

    return true;
}

std::vector<node*>& scene::getNodes(){
    return Nodes;
}

void scene::drawScene(){
    for(int i = 0;i<Nodes.size();i++){
        Mesh* mesh=Nodes[i]->getChildByType<Mesh>();
        if(mesh) mesh->draw();
    }
}

void scene::addNode(node* Node){
    Nodes.push_back(Node);
}

void scene::removeNode(node* Node){
    for(size_t i=0;i<Nodes.size();i++){
        if(Nodes.at(i)==Node){
            Nodes.erase(Nodes.begin()+i);
        }
    }
}

void scene::setCamera(camera* camera){
    activeCamera=camera;
}

camera* scene::getActiveCamera(){
    return activeCamera;
}



}
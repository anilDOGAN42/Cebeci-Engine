#include "scene.hpp"
#include "camera.hpp"
#include "Mesh.hpp"
#include "node.hpp"
#include <stdlib.h>

namespace CebeciEngine::Core {
using namespace Render::Camera;

scene::scene(){
    this->isNodeComponent=false;
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
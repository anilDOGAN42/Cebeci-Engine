#include "scene.hpp"
#include "camera.hpp"
#include "Mesh.hpp"
#include <stdlib.h>

namespace CebeciEngine::Core {
using namespace Render::Camera;
scene::~scene(){
    
}

void scene::drawScene(){
    for(int i = 0;i<Nodes.size();i++){
        Mesh* mesh=Nodes[i]->getComponentByType<Mesh>();
        if(mesh) mesh->draw();
    }
}

void scene::addNode(node* Node){
    Nodes.push_back(Node);
}

void scene::setCamera(camera* camera){
    activeCamera=camera;
}

camera* scene::getActiveCamera(){
    return activeCamera;
}

std::vector<startTask*> scene::getStartTasks(){
    return startTasks;
}
std::vector<updateTask*> scene::getUpdateTasks(){
    return updateTasks;
}

void scene::addStartTask(startTask* task){
    this->startTasks.push_back(task);
}
void scene::addUpdateTask(updateTask* task){
    this->updateTasks.push_back(task);
}
}
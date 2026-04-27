#include "scene.hpp"
#include "camera.hpp"
#include "Mesh.hpp"
#include <stdlib.h>

scene::~scene(){
    
}

void scene::drawScene(){
    for(int i = 0;i<Nodes.size();i++)
        Nodes[i]->getMesh()->draw();
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
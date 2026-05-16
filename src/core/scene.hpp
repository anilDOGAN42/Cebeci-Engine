#pragma once
#include "application.hpp"
#include <Task.hpp>
#include <node.hpp>
#include <vector>
#include <camera.hpp>

using namespace CebeciEngine::Core::App::Task;

namespace CebeciEngine::Core {
class node;
class scene:public App::Object::Object{
public:
    void addNode(node* Node);
    void drawScene();
    
    void setCamera(Render::Camera::camera* camera);
    Render::Camera::camera* getActiveCamera();

    std::vector<startTask*> getStartTasks();
    std::vector<updateTask*> getUpdateTasks();

    void addStartTask(startTask* task);
    void addUpdateTask(updateTask* task);

    ~scene();

private:
    std::vector<node*> Nodes;
    Render::Camera::camera* activeCamera;

    std::vector<updateTask*> updateTasks;
    std::vector<startTask*> startTasks;
    
};
}


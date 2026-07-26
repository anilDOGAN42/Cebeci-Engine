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
    void removeNode(node* Node);

    void drawScene();
    
    void setCamera(Render::Camera::camera* camera);
    Render::Camera::camera* getActiveCamera();

    std::vector<Task*>& getTasks();
    void addTask(Task* task);

    void removeTask(Task* task);
    void removeTask(size_t taskID);

    scene();
    ~scene()=default;

private:
    std::vector<node*> Nodes;
    Render::Camera::camera* activeCamera;

    std::vector<Task*> Tasks;
    
};
}


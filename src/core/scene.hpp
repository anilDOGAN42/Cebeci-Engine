#pragma once
#include <Task.hpp>
#include <node.hpp>
#include <vector>
#include <camera.hpp>

class scene:public Object{
public:
    void addNode(node* Node);
    void drawScene();
    
    void setCamera(camera* camera);
    camera* getActiveCamera();

    std::vector<startTask*> getStartTasks();
    std::vector<updateTask*> getUpdateTasks();

    void addStartTask(startTask* task);
    void addUpdateTask(updateTask* task);

    ~scene();

private:
    std::vector<node*> Nodes;
    camera* activeCamera;

    std::vector<updateTask*> updateTasks;
    std::vector<startTask*> startTasks;
    
};
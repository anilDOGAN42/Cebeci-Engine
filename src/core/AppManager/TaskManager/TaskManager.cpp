#include "TaskManager.hpp"
#include "Task.hpp"
#include "scene.hpp"
#include <application.hpp>

namespace CebeciEngine::Core::App::Task{
TaskManager::TaskManager(){}

TaskManager& TaskManager::instance(){
    static TaskManager instance;
    return instance;
    
}

void TaskManager::getActiveScenesTasks(){
    scene *Scene= App::instance().getActiveScene();

    this->startTasks=Scene->getStartTasks();
    this->updateTasks=Scene->getUpdateTasks();

    for(startTask* task:this->startTasks)
        task->clearDeltaTime();

    for(updateTask* task:this->updateTasks)
        task->clearDeltaTime();

}


void TaskManager::addUpdateTask(updateTask* task){
    updateTasks.push_back(task);
}
void TaskManager::addStartTask(startTask* task){
    startTasks.push_back(task);
}

void TaskManager::runStartTasks(){
    for(unsigned int i=0;i<startTasks.size();i++)
        this->startTasks[i]->run();
}

void TaskManager::runUpdateTasks(){
    
    for(unsigned int i=0;i<updateTasks.size();i++)
        this->updateTasks[i]->run();
}
}
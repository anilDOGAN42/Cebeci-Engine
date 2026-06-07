#pragma once
#include "Task.hpp"
#include <vector>

namespace CebeciEngine::Core::App::Task{
class TaskManager{
public:
    static TaskManager& instance();

    TaskManager(const TaskManager&) = delete;
    TaskManager& operator=(const TaskManager&) = delete;

    void getActiveScenesTasks();

    void addUpdateTask(updateTask* task);
    void addStartTask(startTask* task);

    void runUpdateTasks();
    void runStartTasks();


private:
    TaskManager();

    std::vector<updateTask*> updateTasks;
    std::vector<startTask*> startTasks;

};
}
#pragma once
#include "Task.hpp"
#include <vector>

class TaskManager{
public:
    static TaskManager& instance();

    TaskManager(const TaskManager&) = delete;
    TaskManager& operator=(const TaskManager&) = delete;

    void getActiveScenesTasks();

    void runUpdateTasks();
    void runStartTasks();

private:
    TaskManager();

    std::vector<updateTask*> updateTasks;
    std::vector<startTask*> startTasks;

};
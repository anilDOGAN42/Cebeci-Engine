#include "Task.hpp"


Task::Task(void(*func)(double deltaTime),bool isActive){
    this->func=func;
    this->active=isActive;
}

void Task::clearDeltaTime(){
    this->lastTime=Clock::now();
}

void Task::activate(){
    this->clearDeltaTime();
    this->active=true;
}

void Task::deactivate(){
    this->active=false;
}

updateTask::updateTask(void(*func)(double deltaTime),bool isActive):Task(func,isActive){}
startTask::startTask(void(*func)(double deltaTime),bool isActive):Task(func,isActive){}

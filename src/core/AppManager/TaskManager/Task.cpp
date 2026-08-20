#include "Task.hpp"
#include <thread>

namespace CebeciEngine::Core::App::Task{

void Task::clearDeltaTime(){
    this->lastTime=Clock::now();
}

void Task::run(){
    if(!isActive()) return;
    if(!Init_Function_Ran) {Init();  Init_Function_Ran=true; }
    if(!Start_Function_Ran){Start(); Start_Function_Ran=true;}

    Clock::time_point now=Clock::now();

    double seconds = std::chrono::duration<double>(now-lastTime).count();

    Update(seconds);
    lastTime=now;

}

std::thread::id Task::getTaskThreadId(){
    return this->taskThread;
}
void Task::setTaskThreadId(std::thread::id id){
    this->taskThread=id;
}

}
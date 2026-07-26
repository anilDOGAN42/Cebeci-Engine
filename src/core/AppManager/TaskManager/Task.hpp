#pragma once
#include "Object.hpp"
#include <chrono>
#include <thread>


using Clock = std::chrono::steady_clock;

namespace CebeciEngine::Core::App::Task{
class Task:Object::Object{
public:
    
    virtual void activate();
    virtual void deactivate();

    void run();

    std::thread::id getTaskThreadId();
    void setTaskThreadId(std::thread::id id);

    virtual void clearDeltaTime();

protected:
    virtual void Update(double deltaTime){}
    virtual void Start(){}
    virtual void Init(){}
    
    Clock::time_point lastTime = Clock::now();

    bool active;
    bool Init_Function_Ran=false;
    bool Start_Function_Ran=false;

    std::thread::id taskThread{};
};
}
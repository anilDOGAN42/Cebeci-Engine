#pragma once
#include <chrono>


using Clock = std::chrono::steady_clock;

class Task{
public:
    Task(void(*func)(double deltaTime),bool isActive);

    virtual void activate();
    virtual void deactivate();

    virtual void clearDeltaTime();

    virtual void run()=0;
protected:
    void(*func)(double deltaTime);

    Clock::time_point lastTime = Clock::now();

    bool active;
};

class updateTask: public Task{
public:
    updateTask(void(*func)(double deltaTime),bool isActive);
    void run() override{
        if(active){
            Clock::time_point now = Clock::now();

            double deltaTime =std::chrono::duration<double>(now-lastTime).count();

            this->lastTime = now;
                
            func(deltaTime);
        }
    }
};

class startTask: public Task{
public:
    startTask(void(*func)(double deltaTime),bool isActive);
    void run() override{
        if(active){
            func(0);
        }
    }
};


class sceneInitTask: public Task{
public:
    sceneInitTask(void(*func)(double deltaTime),bool isActive);
    void run() override{
        if(active){
            func(0);
        }
    }
};
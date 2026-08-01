#include "TaskManager.hpp"
#include "Task.hpp"
#include "Thread.hpp"
#include <application.hpp>
#include <iostream>
#include <thread>

namespace CebeciEngine::Core::App::Task{

using Threading::Thread;

TaskManager& TaskManager::instance(){
    static TaskManager instance;
    return instance;
    
}

void TaskManager::initMainThread(){
    this->MainThreadId=std::this_thread::get_id();
}

void TaskManager::deleteAllThreads(){
    ThreadsMutex.lock();
    for(Thread* thread:this->Threads){
        delete thread;
    }
    ThreadsMutex.unlock();
}

Threading::Thread* TaskManager::createThread(std::string name){
    ThreadsMutex.lock();
    Thread* newThread=new Thread(name);

    this->Threads.push_back(newThread);

    ThreadsMutex.unlock();
    return newThread;
}

void TaskManager::deleteThread(std::string name){
    ThreadsMutex.lock();

    for(size_t i=0;i<Threads.size();i++){
        Thread* thread=Threads.at(i);
        if(thread->name==name){
            Threads.erase(Threads.begin()+i);
            delete thread;
            
            ThreadsMutex.unlock();
            return;
        }
    }
    ThreadsMutex.unlock();
}

void TaskManager::deleteThread(std::thread::id id){
    ThreadsMutex.lock();

    for(size_t i=0;i<Threads.size();i++){
        Thread* thread=Threads.at(i);
        if(thread->id==id){
            Threads.erase(Threads.begin()+i);
            delete thread;
            
            ThreadsMutex.unlock();
            return;
        }
    }
    ThreadsMutex.unlock();
}

Thread* TaskManager::getThread(std::thread::id id){
    ThreadsMutex.lock();
    for(Thread* thread:Threads){
        if(thread->id==id){
            ThreadsMutex.unlock();
            return thread;
        }
    }
    ThreadsMutex.unlock();
    return nullptr;

}
Thread* TaskManager::getThread(std::string name){
    ThreadsMutex.lock();
    for(Thread* thread:Threads){
        if(thread->name==name){
            ThreadsMutex.unlock();
            return thread;
        }
    }
    ThreadsMutex.unlock();
    return nullptr;
}

void TaskManager::addTaskToMainThread(Task* task){
    MainThreadTasksMutex.lock();
    task->setTaskThreadId(MainThreadId);

    this->MainThreadTasks.push_back(task);
    MainThreadTasksMutex.unlock();
}

void TaskManager::addTaskToThread(Task* task,std::thread::id threadId){
    ThreadsMutex.lock();

    Thread* thread=this->getThread(threadId);

    if(thread==nullptr){
        std::cerr<<"Thread is null!\n";
        return;
    }

    task->setTaskThreadId((std::thread::id)threadId);
    
    thread->addTaskToThread(task);

    ThreadsMutex.unlock();
}

void TaskManager::addTaskToThread(Task* task,std::string name){
    ThreadsMutex.lock();
    Thread* thread=getThread(name);

    if(thread==nullptr){
        std::cerr<<"Thread is null!\n";
        return;
    }

    task->setTaskThreadId((std::thread::id)thread->id);

    thread->addTaskToThread(task);
    ThreadsMutex.unlock();
}

}
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
    for(Thread* thread:this->Threads){
        delete thread;
    }
}

Threading::Thread* TaskManager::createThread(std::string name){
    Thread* newThread=new Thread(name);

    this->Threads.push_back(newThread);

    return newThread;
}

void TaskManager::deleteThread(std::string name){
    Thread* thread=getThread(name);

    if(!thread) return;

    for(size_t i=0;i<Threads.size();i++){
        if(Threads.at(i)==thread){
            Threads.erase(Threads.begin()+i);
        }
    }

    delete thread;
}

void TaskManager::deleteThread(std::thread::id id){
    Thread* thread=getThread(id);

    if(!thread) return;

    for(size_t i=0;i<Threads.size();i++){
        if(Threads.at(i)==thread){
            Threads.erase(Threads.begin()+i);
        }
    }

    delete thread;
}

Thread* TaskManager::getThread(std::thread::id id){
    for(Thread* thread:Threads){
        if(thread->id==id) return thread;
    }
    return nullptr;
}
Thread* TaskManager::getThread(std::string name){
    for(Thread* thread:Threads){
        if(thread->name==name) return thread;
    }
    return nullptr;
}

void TaskManager::addTaskToMainThread(Task* task){
    task->setTaskThreadId(MainThreadId);

    this->MainThreadTasks.push_back(task);

}

void TaskManager::addTaskToThread(Task* task,std::thread::id threadId){
    task->setTaskThreadId((std::thread::id)threadId);

    Thread* thread=this->getThread(threadId);

    thread->addTaskToThread(task);

}

void TaskManager::addTaskToThread(Task* task,std::string name){
    Thread* thread=getThread(name);

    if(thread==nullptr){
        std::cerr<<"Thread is null!\n";
        return;
    }

    task->setTaskThreadId((std::thread::id)thread->id);

    thread->addTaskToThread(task);

}

}
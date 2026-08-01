#pragma once
#include "Task.hpp"
#include "Thread.hpp"
#include "application.hpp"
#include <mutex>
#include <string>
#include <thread>
#include <vector>

namespace CebeciEngine::Core::App{
class App;
namespace Task{

class TaskManager{
public:
    static TaskManager& instance();

    TaskManager(const TaskManager&) = delete;
    TaskManager& operator=(const TaskManager&) = delete;

    Threading::Thread* createThread(std::string name);

    void deleteThread(std::string name);
    void deleteThread(std::thread::id id);

    Threading::Thread* getThread(std::thread::id id);
    Threading::Thread* getThread(std::string name);


    void addTaskToMainThread(Task* task);

    void addTaskToThread(Task* task,std::thread::id threadId);
    void addTaskToThread(Task* task,std::string threadName);

private:
    TaskManager()=default;

    friend class CebeciEngine::Core::App::App;

    void initMainThread();
    void deleteAllThreads();

    std::thread::id MainThreadId{};

    std::mutex ThreadsMutex;
    std::vector<Threading::Thread*> Threads;

    std::mutex MainThreadTasksMutex;
    std::vector<Task*> MainThreadTasks;
};
}
}
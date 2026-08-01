#pragma once
#include "Task.hpp"
#include <atomic>
#include <mutex>
#include <thread>
#include <vector>

namespace CebeciEngine::Core::App::Task{
class TaskManager;
namespace Threading{
class Thread{
public:
    void addTaskToThread(Task* task);
    void removeTaskFromThread(Task* task);

    std::thread::id getId();
private:
    friend class CebeciEngine::Core::App::Task::TaskManager;
    Thread(std::string name);
    ~Thread();

    std::thread thread;
    void thread_main();
    
    std::atomic<bool> is_running{false};
    std::mutex tasks_mutex;

    std::vector<Task*> tasks;

    std::thread::id id;
    std::string name;
};
}
}
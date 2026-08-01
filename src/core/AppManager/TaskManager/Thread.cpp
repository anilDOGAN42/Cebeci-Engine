    #include "Thread.hpp"
    #include <thread>

    namespace CebeciEngine::Core::App::Task::Threading {

        Thread::Thread(std::string name) {
        this->name = name;
        this->is_running = true;
        
        this->thread = std::thread(&Thread::thread_main, this);
        
        this->id = this->thread.get_id(); 
    }

        Thread::~Thread() {
            is_running = false;
            if (thread.joinable()) {
                thread.join();
            }
        }   

        void Thread::thread_main() {
            this->id = std::this_thread::get_id();

            while (is_running) {
                tasks_mutex.lock();
                for (Task* task : tasks) {
                    if (task) {
                        task->run();
                    }
                }
                tasks_mutex.unlock();
                std::this_thread::yield();
            }
        }

        void Thread::addTaskToThread(Task* task) {
            if (!task) return;
            tasks_mutex.lock();
            this->tasks.push_back(task);
            tasks_mutex.unlock();
        }

        void Thread::removeTaskFromThread(Task* task) {
            tasks_mutex.lock();
            for (auto it = tasks.begin(); it != tasks.end(); ++it) {
                if (*it == task) {
                    tasks.erase(it);
                    tasks_mutex.unlock();
                    break;
                }
            }
            tasks_mutex.unlock();
        }

        std::thread::id Thread::getId() {
            return this->thread.get_id();
        }
    }
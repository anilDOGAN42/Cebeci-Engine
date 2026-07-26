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
            cv.notify_all();
            if (thread.joinable()) {
                thread.join();
            }
        }   

        void Thread::thread_main() {
            this->id = std::this_thread::get_id();

            while (is_running) {
                std::vector<Task*> tasks_to_run;

                {
                    std::unique_lock<std::mutex> lock(tasks_mutex);
                    
                        cv.wait(lock, [this]() {
                        return !tasks.empty() || !is_running;
                    });
                    
                    if (!is_running) break;

                    tasks_to_run = tasks; 

                }

                for (Task* task : tasks_to_run) {
                    if (task) {
                        task->run();
                    }
                }

                std::this_thread::yield();
            }
        }

        void Thread::addTaskToThread(Task* task) {
            if (!task) return;

            {
                std::lock_guard<std::mutex> lock(tasks_mutex);
                this->tasks.push_back(task);
            }
            

            cv.notify_one(); 
        }

        void Thread::removeTaskFromThread(Task* task) {
            std::lock_guard<std::mutex> lock(tasks_mutex);
            for (auto it = tasks.begin(); it != tasks.end(); ++it) {
                if (*it == task) {
                    tasks.erase(it);
                    break;
                }
            }
        }

        std::thread::id Thread::getId() {
            return this->thread.get_id();
        }
    }
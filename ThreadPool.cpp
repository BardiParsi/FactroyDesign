#include "ThreadPool.h"
// Constructor to initialize the thread pool with a specified number of threads
ThreadPool::ThreadPool(size_t numThreads) : stop(false) {
    for (size_t i = 0; i < numThreads; ++i) {
        workers.emplace_back([this](std::stop_token stopToken) {
            while (!stopToken.stop_requested()) {
                std::function<void()> task;
                { // Wait for either a task to be available or a stop request
                    std::unique_lock<std::mutex> lock(queueMutex);
                    condition.wait(lock, [this, &stopToken] {
                        return stopToken.stop_requested() || !tasks.empty();
                        });
                    // If stop requested and no tasks, exit the loop
                    if (stopToken.stop_requested() && tasks.empty()) {
                        return;
                    }
                    // Retrieve the next task from the queue
                    task = std::move(tasks.front());
                    tasks.pop();
                } 
                task(); // Execute the task
            }
        }, stopSource.get_token()); // Pass the stop token to the worker thread
    }
}
// Destructor to clean up and join all worker threads
ThreadPool::~ThreadPool() {
    stopSource.request_stop(); // Request stop for all threads
    condition.notify_all();
    for (auto& worker : workers) {
        if (worker.joinable()) {
            worker.join();
        }
    }
}

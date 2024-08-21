#pragma once

#include <vector>
#include <thread>
#include <functional>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <future>
#include <stop_token>
#include <cassert>

// A class representing a thread pool for managing and executing tasks concurrently
class ThreadPool {
private:
    std::vector<std::jthread> workers;  // Vector of jthreads representing the worker threads in the pool
    std::queue<std::function<void()>> tasks; // Queue to hold tasks submitted to the thread pool
    std::mutex queueMutex; // Mutex to protect access to the task queue
    std::condition_variable condition; // Condition variable used for synchronizing task execution
    std::atomic<bool> stop; // Atomic flag indicating if the thread pool is stopping
    std::stop_source stopSource; // Source to signal stopping requests to the threads

public:
    // Constructor to initialize the thread pool with a specified number of threads
    explicit ThreadPool(size_t numThreads);
    ~ThreadPool(); // Destructor to clean up and join all worker threads

    // Template method to submit a task to the thread pool
    // Returns a future that will hold the result of the task when it completes
    template<class F, class... Args>
    auto enqueue(F&& f, Args&&... args) -> std::future<std::invoke_result_t<F, Args...>> {
        using returnType = std::invoke_result_t<F, Args...>; // Determine the return type of the task
        // Create a packaged_task that wraps the callable and its arguments
        auto task = std::make_shared<std::packaged_task<returnType()>>(
            std::bind(std::forward<F>(f), std::forward<Args>(args)...)
        );

        std::future<returnType> res = task->get_future();  // Get the future associated with the packaged_task
        {
            std::unique_lock<std::mutex> lock(queueMutex); // Lock the mutex to safely access the task queue
            // Throw an exception if attempting to enqueue a task while the pool is stopping
            if (stopSource.stop_requested()) {
                throw std::runtime_error("enqueue on stopped ThreadPool");
            }
            // Add the task to the queue
            tasks.emplace([task]() { (*task)(); });
        }
        condition.notify_one(); // Notify one of the waiting threads that a new task is available
        return res; // Return the future associated with the task
    }
};

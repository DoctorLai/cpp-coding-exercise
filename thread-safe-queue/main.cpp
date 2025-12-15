#include <iostream>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <memory>
#include <thread>

template <typename T> class ThreadSafeQueue
{
  public:
    ThreadSafeQueue() = default;
    ~ThreadSafeQueue() = default;

    void
    enqueue(T item)
    {
        std::lock_guard<std::mutex> lock(mutex_);
        queue_.push(std::move(item));
        cond_var_.notify_one();
    }

    T
    dequeue()
    {
        std::unique_lock<std::mutex> lock(mutex_);
        cond_var_.wait(lock, [this]() { return !queue_.empty(); });
        T item = queue_.front();
        queue_.pop();
        return item;
    }

    bool
    isEmpty() const
    {
        std::lock_guard<std::mutex> lock(mutex_);
        return queue_.empty();
    }

    size_t
    size() const
    {
        std::lock_guard<std::mutex> lock(mutex_);
        return queue_.size();
    }

  private:
    mutable std::mutex mutex_;
    std::condition_variable cond_var_;
    std::queue<T> queue_;
};

int
main()
{
    ThreadSafeQueue<int> tsQueue;

    // Enqueue some items
    tsQueue.enqueue(1);
    tsQueue.enqueue(2);
    tsQueue.enqueue(3);

    // Dequeue and print items
    while (!tsQueue.isEmpty()) {
        std::cout << tsQueue.dequeue() << std::endl;
    }

    // create two threads to demonstrate thread safety
    std::thread producer([&tsQueue]() {
        for (int i = 1; i < 10; ++i) {
            tsQueue.enqueue(i);
            std::cout << "Enqueued: " << i << std::endl;
        }
    });

    std::thread consumer([&tsQueue]() {
        for (int i = 1; i < 10; ++i) {
            int item = tsQueue.dequeue();
            std::cout << "Dequeued: " << item << std::endl;
        }
    });

    producer.join();
    consumer.join();

    return 0;
}
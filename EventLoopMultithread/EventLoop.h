#pragma once

#include <queue>
#include <future>
#include <memory>
#include <mutex>
#include <atomic>
#include "Task.h"


class EventLoop : public std::enable_shared_from_this<EventLoop>
{
private:
    std::mutex _mutex;
    std::atomic_bool _isRunning;
    std::priority_queue<Task, std::vector<Task>, std::greater<Task>> _tasks;

private:
    EventLoop();

public:
    ~EventLoop();
    void run();
    void stop();
    void schedule(const Task& task);
    void schedule(const std::function<std::future<void>(std::weak_ptr<EventLoop>)> func);

    static std::shared_ptr<EventLoop> make();
};


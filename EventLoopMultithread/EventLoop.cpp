#include "EventLoop.h"

EventLoop::EventLoop()
    : _isRunning(false)
{
}

EventLoop::~EventLoop()
{
}

void EventLoop::run()
{
    auto sleepTimePoint = std::chrono::steady_clock::now();

    _isRunning = true;
    while (_isRunning)
    {
        std::this_thread::sleep_until(sleepTimePoint);

        Task task;
        {
            std::lock_guard<std::mutex> lock(_mutex);

            if (_tasks.empty())
                continue;

            task = _tasks.top();
            if (task._timePoint > std::chrono::steady_clock::now())
            {
                sleepTimePoint = task._timePoint;
                continue;
            }
            _tasks.pop();
        }

        task._func(weak_from_this());
    }
}

void EventLoop::stop()
{
    _isRunning = false;
}

void EventLoop::schedule(const Task& task)
{
    std::lock_guard<std::mutex> lock(_mutex);
    _tasks.push(task);
}

void EventLoop::schedule(const std::function<std::future<void>(std::weak_ptr<EventLoop>)> func)
{
    std::lock_guard<std::mutex> lock(_mutex);
    _tasks.emplace(weak_from_this(), func);
}

std::shared_ptr<EventLoop> EventLoop::make()
{
    return std::shared_ptr<EventLoop>(new EventLoop());
}

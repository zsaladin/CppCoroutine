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
    _isRunning = true;
    while (_isRunning)
    {
        if (_tasks.empty())
            continue;

        Task task = _tasks.top();
        if (task._timePoint > std::chrono::steady_clock::now())
        {
            std::this_thread::sleep_until(task._timePoint);
            continue;
        }

        _tasks.pop();
        task._func(weak_from_this());
    }
}

void EventLoop::stop()
{
    _isRunning = false;
}

void EventLoop::schedule(const Task& task)
{
    _tasks.push(task);
}

void EventLoop::schedule(const std::function<std::future<void>(std::weak_ptr<EventLoop>)> func)
{
    _tasks.emplace(weak_from_this(), func);
}

std::shared_ptr<EventLoop> EventLoop::make()
{
    return std::shared_ptr<EventLoop>(new EventLoop());
}

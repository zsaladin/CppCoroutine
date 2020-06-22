#pragma once

#include <memory>
#include <future>
#include <chrono>
#include <experimental/coroutine>

using TimePoint = std::chrono::time_point<std::chrono::steady_clock>;

class EventLoop;
class Task
{
    friend EventLoop;

private:
    std::weak_ptr<EventLoop> _loop;
    std::function<std::future<void>(std::weak_ptr<EventLoop>)> _func;
    TimePoint _timePoint;


public:
    Task(std::weak_ptr<EventLoop>, std::function<std::future<void>(std::weak_ptr<EventLoop>)>);
    Task(std::weak_ptr<EventLoop>, std::function<std::future<void>(std::weak_ptr<EventLoop>)>, const TimePoint&);
    Task(const Task& other);
    Task(Task&& other) noexcept;
    Task& operator=(const Task& other);
    Task& operator=(Task&& other) noexcept;
    bool operator>(const Task& other) const;
};


#include "Task.h"
#include "EventLoop.h"

Task::Task(std::weak_ptr<EventLoop> loop, std::function<std::future<void>(std::weak_ptr<EventLoop>)> func)
    : Task(loop, func, std::chrono::steady_clock::now())
{
}

Task::Task(std::weak_ptr<EventLoop> loop, std::function<std::future<void>(std::weak_ptr<EventLoop>)> func, const TimePoint& timePoint)
    : _loop(loop), _func(func), _timePoint(timePoint)
{
}

Task::Task(const Task& other)
    : _loop(other._loop), _func(other._func), _timePoint(other._timePoint)
{
}

Task::Task(Task&& other) noexcept
    : _loop(std::move(other._loop)), _func(std::move(other._func)), _timePoint(std::move(other._timePoint))
{
}

Task& Task::operator=(const Task& other)
{
    _loop = other._loop;
    _func = other._func;
    _timePoint = other._timePoint;
    return *this;
}

Task& Task::operator=(Task&& other) noexcept
{
    _loop = std::move(other._loop);
    _func = std::move(other._func);
    _timePoint = std::move(other._timePoint);
    return *this;
}

bool Task::operator>(const Task& other) const
{
    return _timePoint > other._timePoint;
}


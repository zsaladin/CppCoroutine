#pragma once

#include <chrono>
#include <memory>
#include <experimental/coroutine>


using MilliSeconds = std::milli;
using Duration = std::chrono::duration<std::int64_t, MilliSeconds>;
using TimePoint = std::chrono::time_point<std::chrono::steady_clock>;

class EventLoop;
class Sleep
{
private:
    std::weak_ptr<EventLoop> _loop;
    TimePoint _timePoint;

public:
    Sleep(std::weak_ptr<EventLoop>, const Duration&);
    ~Sleep();

    bool await_ready() noexcept;
    void await_suspend(std::experimental::coroutine_handle<> coroutine) noexcept;
    void await_resume() noexcept;
};


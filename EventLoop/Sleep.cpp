#include "Sleep.h"
#include "EventLoop.h"

#include <iostream>

Sleep::Sleep(std::weak_ptr<EventLoop> loop, const Duration& duration)
    : _loop(loop), _timePoint(std::chrono::steady_clock::now() + duration)
{
}

Sleep::~Sleep() = default;

bool Sleep::await_ready() noexcept
{
    return _timePoint <= std::chrono::steady_clock::now();
}

void Sleep::await_suspend(std::experimental::coroutine_handle<> coroutine) noexcept
{
    auto func = [coroutine = std::move(coroutine)](std::weak_ptr<EventLoop>) -> std::future<void> {
        coroutine.resume();
        co_return;
    };

    auto loop = _loop.lock();
    if (loop)
    {
        loop->schedule(Task(_loop, func, _timePoint));
    }
}

void Sleep::await_resume() noexcept
{
}

#pragma once

#include <experimental/coroutine>

template <typename T>
class Awaitable
{
    virtual bool await_ready() noexcept = 0;
    virtual void await_suspend(std::experimental::coroutine_handle<> coroutine) noexcept = 0;
    virtual T await_resume() noexcept = 0;
};


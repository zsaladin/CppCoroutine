#pragma once

#include "Awaitable.h"

template<typename T>
class Job : public Awaitable<T>
{
public: 
    Job<T>(std::)
    virtual bool await_ready() noexcept override;
    virtual void await_suspend(std::experimental::coroutine_handle<> coroutine) noexcept overrid;
    virtual T await_resume() noexcept override;
};


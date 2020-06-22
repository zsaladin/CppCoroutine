#include <iostream>
#include <chrono>
#include "EventLoop.h"
#include "Task.h"
#include "Sleep.h"


using namespace std::literals::chrono_literals;

std::future<void> func0(std::weak_ptr<EventLoop> loop) 
{
    std::cout << "func0 - 1" << std::endl;
    co_await Sleep(loop, 1000ms);

    std::cout << "func0 - 2" << std::endl;
}


int longTimeJob()
{
    std::cout << "long time job 1" << std::endl;
    std::this_thread::sleep_for(50000ms);
    std::cout << "long time job 2" << std::endl;
    return 100;
}

std::future<void> func1(std::weak_ptr<EventLoop> loop)
{
    std::cout << "func1 - 1" << std::endl;
    int result = co_await std::async(longTimeJob);

    std::cout << "func1 - 2" << std::endl;
    loop.lock()->stop();
}



int main()
{
    auto loop = EventLoop::make();

    //loop->schedule(func0);
    loop->schedule(func1);
    loop->run();
}
#include <iostream>
#include <chrono>
#include "EventLoop.h"
#include "Task.h"
#include "Sleep.h"


using namespace std::literals::chrono_literals;

std::future<void> func0(std::weak_ptr<EventLoop> loop) 
{
    std::cout << "func0 - 1" << std::endl;  // 1
    co_await Sleep(loop, 1000ms);

    std::cout << "func0 - 2" << std::endl;  // 5
}

std::future<void> func1(std::weak_ptr<EventLoop> loop)
{
    std::cout << "func1 - 1" << std::endl;  // 2
    co_await Sleep(loop, 3000ms);

    std::cout << "func1 - 2" << std::endl;  // 8

}

std::future<void> funcNested(std::weak_ptr<EventLoop> loop)
{
    std::cout << "funcNested - 1" << std::endl;  // 4
    co_await Sleep(loop, 1500ms);
    std::cout << "funcNested - 2" << std::endl;  // 6
}

std::future<void> func2(std::weak_ptr<EventLoop> loop)
{
    std::cout << "func2 - 1" << std::endl;  // 3
    co_await funcNested(loop);
    std::cout << "func2 - 2" << std::endl;  // 7
}

int longTimeJob()
{
    // spinning event loop
    // need synchronization
    std::cout << "long time job 1" << std::endl;
    std::this_thread::sleep_for(5000ms); 
    std::cout << "long time job 2" << std::endl;
    return 100;
}

std::future<void> func3(std::weak_ptr<EventLoop> loop)
{
    std::cout << "func3 - 1, " << std::this_thread::get_id() << std::endl;
    int result = co_await std::async(longTimeJob);
    std::cout << "func3 - 2, " << std::this_thread::get_id() << ", " << result << std::endl;

    loop.lock()->stop(); // need synchronization
}

int main()
{
    auto loop = EventLoop::make();

    loop->schedule(func0);
    loop->schedule(func1);
    loop->schedule(func2);
    loop->schedule(func3);
    loop->run();
}
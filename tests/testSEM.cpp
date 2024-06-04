#include <chrono>
#include <cstdint>
#include <iostream>
#include <SimpleEventManager/SimpleEventManager.hpp>
#include "TestEventRaiser.hpp"
#include "TestEventConsumer.hpp"





int main(int, char*[])
{
    sem::SimpleEventManager eventManager;
    TestEventRaiser ter(eventManager, std::chrono::milliseconds(100));
    TestEventConsumer tec(eventManager);

    std::this_thread::sleep_for(std::chrono::seconds(3));

    std::cout << "Hello World!" << std::endl;
    return 0;
}

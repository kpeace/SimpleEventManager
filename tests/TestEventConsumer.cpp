#include "TestEventConsumer.hpp"
#include "MyEvent.hpp"
#include <cstdint>
#include <iostream>
#include <memory>

TestEventConsumer::TestEventConsumer(sem::SimpleEventManager &sem)
    : _consumption(sem.registerEventConsumer(std::hash<std::string>{}(MyEvent::getEventIdString())))
    , _running(true)
    , _consumerThread(std::thread([this]{doConsume();}))
{
}

TestEventConsumer::~TestEventConsumer()
{
    _running = false;
    _consumption->unregister();

    if(_consumerThread.joinable())
    {
        _consumerThread.join();
    }
}

void TestEventConsumer::doConsume()
{
    while (_running) {
        auto ret = _consumption->waitForEvents();
        if (ret.reason == sem::WaitReturnValue::WaitReturnReason::UNREGISTER) {
            return;
        }

        for (auto & event : *ret.events)
        {
            std::cout << "Got event type: " << event->getId() << ", data:" << event->getValue<uint64_t>("value", 0) << std::endl;
        }
    }
}

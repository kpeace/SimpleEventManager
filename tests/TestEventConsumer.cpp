#include "TestEventConsumer.hpp"
#include "MyEvent.hpp"
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
            auto myEvent = std::static_pointer_cast<MyEvent>(event);
            std::cout << "Got event type: " << event->getId() << ", data:" << myEvent->getValue("value", 0) << std::endl;
        }
    }
}

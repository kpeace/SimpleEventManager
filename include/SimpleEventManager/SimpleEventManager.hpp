#pragma once

#include "Event.hpp"
#include "EventConsumptionInterface.hpp"
#include "EventRaiserInterface.hpp"
#include "EventSourceManagerInterface.hpp"
#include <memory>

namespace sem {

class SimpleEventManagerImp;

class SimpleEventManager
{
public:
    EventRaiserInterfacePtr registerEventSource(Event::EventId, EventSourceManagerInterfacePtr);
    EventConsumptionInterfacePtr registerEventConsumer(Event::EventId);

    // Constructors / Destructors
    SimpleEventManager();
    SimpleEventManager(SimpleEventManager const &) = delete;
    SimpleEventManager(SimpleEventManager &&) = default;

    SimpleEventManager & operator=(SimpleEventManager const &) = delete;
    SimpleEventManager & operator=(SimpleEventManager &&) = default;

    ~SimpleEventManager();

private:
    //pimple to make compilation quicker
    std::shared_ptr<SimpleEventManagerImp> _semImp;
};

}

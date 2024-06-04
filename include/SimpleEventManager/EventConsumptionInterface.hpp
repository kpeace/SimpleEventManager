#pragma once

#include <memory>
#include <vector>
#include "Event.hpp"

namespace sem {

using EventContainerType = std::vector<std::shared_ptr<Event>>;

struct WaitReturnValue
{
    enum class WaitReturnReason
    {
        GOT_EVENT,
        UNREGISTER
    };

    WaitReturnReason reason;
    std::unique_ptr<EventContainerType> events;
};


// This class is used by consumers to consume events
class EventConsumptionInterface
{
public:

    using EventContainerType = std::vector<std::shared_ptr<Event>>;

    EventConsumptionInterface() = default;
    EventConsumptionInterface(EventConsumptionInterface const &) = delete;
    EventConsumptionInterface(EventConsumptionInterface &&) = default;

    virtual ~EventConsumptionInterface() = default;

    EventConsumptionInterface & operator=(EventConsumptionInterface const &) = delete;
    EventConsumptionInterface & operator=(EventConsumptionInterface &&) = default;

    // block thread and wait until there are events for consumption. Return events or reason for stopping
    virtual WaitReturnValue waitForEvents() = 0;

    // unregister from reciving events. will also cause the waitForEvents to return.
    virtual void unregister() = 0;
};

using EventConsumptionInterfacePtr = std::shared_ptr<EventConsumptionInterface>;

}

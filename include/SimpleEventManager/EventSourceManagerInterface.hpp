#pragma once

#include <memory>
namespace sem {

// This calss is used by the SEM to stop and start an event source.
// The idea is that an event source should be running only when there
// is a consumer to consume the events
class EventSourceManagerInterface
{
public:
    virtual void startEventSource() = 0;
    virtual void stopEventSource() = 0;

    // constructors and destructors
    EventSourceManagerInterface() = default;
    EventSourceManagerInterface(EventSourceManagerInterface const &) = default;
    EventSourceManagerInterface(EventSourceManagerInterface &&) = default;

    virtual ~EventSourceManagerInterface() = default;

    EventSourceManagerInterface & operator=(EventSourceManagerInterface const &) = default;
    EventSourceManagerInterface & operator=(EventSourceManagerInterface &&) = default;
};

using EventSourceManagerInterfacePtr = std::unique_ptr<EventSourceManagerInterface>;

}

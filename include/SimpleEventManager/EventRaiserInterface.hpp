#pragma once

#include <memory>
#include "Event.hpp"

namespace sem {

class EventRaiserInterface
{
public:
    virtual void raiseEvent(std::shared_ptr<Event>) = 0;
    virtual void unregister() = 0;

    // constructor / destrucotr / copy + move operators
    EventRaiserInterface() = default;
    EventRaiserInterface(EventRaiserInterface const &) = default;
    EventRaiserInterface(EventRaiserInterface &&) = default;

    virtual ~EventRaiserInterface() = default;

    EventRaiserInterface & operator=(EventRaiserInterface const &) = default;
    EventRaiserInterface & operator=(EventRaiserInterface &&) = default;
};

using EventRaiserInterfacePtr = std::unique_ptr<EventRaiserInterface>;

}

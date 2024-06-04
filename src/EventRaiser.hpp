#pragma once

#include <SimpleEventManager/Event.hpp>
#include <SimpleEventManager/EventRaiserInterface.hpp>
#include <memory>

namespace sem {

class SimpleEventManagerImp;

class EventRaiser : public EventRaiserInterface
{
public:
    EventRaiser() = delete;
    explicit EventRaiser(Event::EventId, unsigned int, std::weak_ptr<SimpleEventManagerImp>) ;

    void raiseEvent(std::shared_ptr<Event> event) final;
    void unregister() final;

private:
    Event::EventId _eventId;
    unsigned int _sourceId;
    std::weak_ptr<SimpleEventManagerImp> _eventManger;
};

}

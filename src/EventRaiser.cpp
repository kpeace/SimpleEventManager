#include "EventRaiser.hpp"
#include "SimpleEventManagerImp.hpp"

namespace sem {
EventRaiser::EventRaiser(Event::EventId id, unsigned int sourceId, std::weak_ptr<SimpleEventManagerImp> eventManager)
    : _eventId(id)
    , _sourceId(sourceId)
    , _eventManger(std::move(eventManager))
{}

void EventRaiser::raiseEvent(std::shared_ptr<Event> event)
{
    // TODO add here a check that the event is of the correct ID
    // maybe the ID should be part of the type? is it possible?
    if (auto sharedManager = _eventManger.lock(); sharedManager != nullptr)
    {
        sharedManager->raiseEvent(event);
    }
}

void EventRaiser::unregister()
{
    if (auto sharedManager = _eventManger.lock(); sharedManager != nullptr)
    {
        sharedManager->unregisterEventSource(_eventId, _sourceId);
    }

    _eventManger.reset();
}

}

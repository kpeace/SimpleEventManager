#include "SimpleEventManagerImp.hpp"
#include <algorithm>
#include <memory>
#include <mutex>
#include <vector>
#include "EventRaiser.hpp"
#include "EventConsumerHandler.hpp"

namespace sem {
SimpleEventManagerImp::~SimpleEventManagerImp()
{
    _running = false;
    _hasEvents.notify_all();
    if (_eventForwarder.joinable())
    {
        _eventForwarder.join();
    }
}

SimpleEventManagerImp::SimpleEventManagerImp()
    : _running(true)
    , _eventForwarder([this]() {forwardEvents();})
    , _eventQueue(std::make_unique<std::vector<std::shared_ptr<Event>>>())
{
}

std::shared_ptr<SimpleEventManagerImp> SimpleEventManagerImp::create()
{
    // make_shared can't call a non public constructor.
    // as a work around we do this ugly thing
    struct EnableMakeSharedWithSimpleEventManagerImp : public SimpleEventManagerImp
    {
        EnableMakeSharedWithSimpleEventManagerImp() = default;
    };
    return std::make_shared<EnableMakeSharedWithSimpleEventManagerImp>();
}

std::weak_ptr<SimpleEventManagerImp> SimpleEventManagerImp::getWeakPtr()
{
    return weak_from_this();
}

EventRaiserInterfacePtr SimpleEventManagerImp::registerEventSource(Event::EventId eventId,
    EventSourceManagerInterfacePtr eventSourceMgr)
{
    // we have an internal id for each event source registration
    static unsigned int internalId = 0;

    // creating the id for this specific event source registration
    ++internalId;

    // first lets add the event source maanger to map for later reffernce
    {
        std::lock_guard<std::mutex> lock(_eventSourceManagersLock);
        _eventSourceManagers[eventId][internalId] = std::move(eventSourceMgr);
    }

    // now we check if this event source has a consumer. if it has, start the source
    {
        std::lock_guard<std::mutex> lock(_eventConsumersLock);
        if (_eventConsumers.find(eventId) != _eventConsumers.end() &&
            !_eventConsumers[eventId].empty())
        {
            eventSourceMgr->startEventSource();
        }
    }

    return std::make_unique<EventRaiser>(eventId, internalId, getWeakPtr());
}

void SimpleEventManagerImp::unregisterEventSource(Event::EventId eventId, unsigned int sourceId)
{
    std::lock_guard<std::mutex> lock(_eventSourceManagersLock);
    _eventSourceManagers[eventId].erase(sourceId);
}

void SimpleEventManagerImp::raiseEvent(std::shared_ptr<Event> event)
{
    {
        std::lock_guard<std::mutex> lock(_eventQueueLock);
        _eventQueue->push_back(event);
    }

    _hasEvents.notify_all();
}

EventConsumptionInterfacePtr SimpleEventManagerImp::registerEventConsumer(Event::EventId eventId)
{
    // we have an internal id for each event consumer registration
    static unsigned int internalId = 0;

    // creating the id for this specific event consumer registration
    ++internalId;

    auto consumerHandler = std::make_shared<EventConsumerHandler>(eventId, internalId, getWeakPtr());

    {
        std::lock_guard<std::mutex> lock(_eventConsumersLock);
        _eventConsumers[eventId][internalId] = consumerHandler;
    }

    {
        std::lock_guard<std::mutex> lock(_eventSourceManagersLock);
        if (_eventSourceManagers.find(eventId) !=  _eventSourceManagers.end() &&
            !_eventSourceManagers[eventId].empty())
        {
            for (auto & [id, eventSourceMgr] : _eventSourceManagers[eventId])
            {
                eventSourceMgr->startEventSource();
            }
        }

    }

    return consumerHandler;
}

void SimpleEventManagerImp::unregisterEventConsumer(Event::EventId eventId, unsigned int consumerId)
{
    std::lock_guard<std::mutex> lock(_eventConsumersLock);
    _eventConsumers[eventId].erase(consumerId);
}


void SimpleEventManagerImp::forwardEvents()
{
    while (_running)
    {
        std::unique_lock<std::mutex> eventQueueLock(_eventQueueLock);
        _hasEvents.wait(eventQueueLock, [this] { return !_running || !_eventQueue->empty() ;});
        if (!_running)
        {
            return;
        }

        // by swapping queues we can release the lock quickly even if there are a lot of events in the queue
        auto queue = std::make_unique<EventContainer>();

        // small performance optimization. That way there is no need to allocate space when a new event is pushed
        queue->reserve(_eventQueue->size() * 2);

        queue.swap(_eventQueue);
        eventQueueLock.unlock();

        std::lock_guard<std::mutex> lock(_eventConsumersLock);
        for (auto & event : *queue)
        {
            for (auto & [consumerId, consumer] : _eventConsumers[event->getId()])
            {
                consumer->raiseEvent(event);
            }
        }
    }
}

}

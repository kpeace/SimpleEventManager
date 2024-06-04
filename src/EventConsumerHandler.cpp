#include "EventConsumerHandler.hpp"
#include "SimpleEventManagerImp.hpp"
#include <memory>
#include <mutex>

namespace sem {

EventConsumerHandler::EventConsumerHandler(
    Event::EventId eventId,
    unsigned int consumerId,
    std::weak_ptr<SimpleEventManagerImp> eventManger)
    : _eventId(eventId)
    , _consumerId(consumerId)
    , _eventManger(std::move(eventManger))
    , _eventQueue(std::make_unique<EventContainerType>())
{
}

EventConsumerHandler::~EventConsumerHandler() = default;

WaitReturnValue EventConsumerHandler::waitForEvents()
{
    std::unique_lock<std::mutex> lock(_eventQueueLock);
    _hasEvents.wait(lock, [this] { return _interrupt || !_eventQueue->empty() ;});

    if (_interrupt)
    {
        return {WaitReturnValue::WaitReturnReason::UNREGISTER, std::unique_ptr<EventContainerType>()};
    }

    auto eventsQueue = std::make_unique<EventContainerType>();
    _eventQueue.swap(eventsQueue);
    lock.unlock();

    return {WaitReturnValue::WaitReturnReason::GOT_EVENT, std::move(eventsQueue)};
}

void EventConsumerHandler::unregister()
{
    _interrupt = true;
    _hasEvents.notify_all();
    if (auto sharedManager = _eventManger.lock(); sharedManager != nullptr)
    {
        sharedManager->unregisterEventConsumer(_eventId, _consumerId);
    }

    _eventManger.reset();
}

void EventConsumerHandler::raiseEvent(std::shared_ptr<Event> event)
{
    {
        std::lock_guard<std::mutex> lock(_eventQueueLock);
        _eventQueue->push_back(event);
    }

    _hasEvents.notify_all();
}

}

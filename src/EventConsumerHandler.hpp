#pragma once

#include <atomic>
#include <condition_variable>
#include <memory>
#include <mutex>
#include <SimpleEventManager/EventConsumptionInterface.hpp>

namespace sem {

class SimpleEventManagerImp;

class EventConsumerHandler final : public EventConsumptionInterface
{
public:
    EventConsumerHandler() = delete;
    EventConsumerHandler(EventConsumerHandler const &) = delete;
    EventConsumerHandler(EventConsumerHandler &&) = delete;

    EventConsumerHandler & operator=(EventConsumerHandler const &) = delete;
    EventConsumerHandler & operator=(EventConsumerHandler &&) = delete;

    explicit EventConsumerHandler(Event::EventId, unsigned int, std::weak_ptr<SimpleEventManagerImp>);
    virtual ~EventConsumerHandler() final;

    WaitReturnValue waitForEvents() final;
    void unregister() final;

    void raiseEvent(std::shared_ptr<Event>);

private:
    std::atomic_bool _interrupt = false;
    Event::EventId _eventId;
    unsigned int _consumerId;
    std::weak_ptr<SimpleEventManagerImp> _eventManger;
    std::mutex _eventQueueLock;
    std::unique_ptr<EventContainerType> _eventQueue;
    std::condition_variable _hasEvents;
};

using EventConsumerHandlerPtr = std::shared_ptr<EventConsumerHandler>;

}

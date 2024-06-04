#pragma once

#include <atomic>
#include <condition_variable>
#include <memory>
#include <unordered_map>
#include <mutex>
#include <thread>
#include <SimpleEventManager/Event.hpp>
#include <SimpleEventManager/EventRaiserInterface.hpp>
#include <SimpleEventManager/EventSourceManagerInterface.hpp>
#include "EventConsumerHandler.hpp"

namespace sem {

class SimpleEventManagerImp : public std::enable_shared_from_this<SimpleEventManagerImp>
{
public:
    ~SimpleEventManagerImp();
    static std::shared_ptr<SimpleEventManagerImp> create();

    EventRaiserInterfacePtr registerEventSource(Event::EventId, EventSourceManagerInterfacePtr);
    EventConsumptionInterfacePtr registerEventConsumer(Event::EventId);

private:
    using EventContainer = std::vector<std::shared_ptr<Event>>;

    // EventRaiser at the end calls functions in SEM to raise an event
    // lets give them a friend status since EventRaiser is anyway hidden behind an interface
    friend class EventRaiser;
    // EventConsumerHandler needs to call the unregister. We can make the unregister public
    // or make EventConsumerHandler a friend class. Guess which one I chose...
    friend class EventConsumerHandler;

    SimpleEventManagerImp();
    std::weak_ptr<SimpleEventManagerImp> getWeakPtr();

    void unregisterEventSource(Event::EventId, unsigned int);
    void raiseEvent(std::shared_ptr<Event> event);
    void forwardEvents();
    void unregisterEventConsumer(Event::EventId, unsigned int);

    std::mutex _eventSourceManagersLock;
    // each event id can have a list of sources that rais that event
    std::unordered_map<Event::EventId, std::unordered_map<unsigned int, EventSourceManagerInterfacePtr>> _eventSourceManagers;

    std::mutex _eventConsumersLock;
     // each consumer listnes to a specific event, there can be many consumers listneing to the same event
    std::unordered_map<Event::EventId, std::unordered_map<unsigned int, EventConsumerHandlerPtr>> _eventConsumers;

    // in theory we want to give the SEM priority over event pushing. This can be done with
    // https://stackoverflow.com/questions/11666610/how-to-give-priority-to-privileged-thread-in-mutex-locking
    // this will be left for future improvments
    std::mutex _eventQueueLock;
    // initially events are placed on queue. We store it as unique_ptr to reduce locking time
    std::unique_ptr<EventContainer> _eventQueue;

    std::atomic_bool _running;
    std::thread _eventForwarder;
    std::condition_variable _hasEvents;
};

}

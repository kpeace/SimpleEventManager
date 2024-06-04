#include <SimpleEventManager/SimpleEventManager.hpp>
#include <utility>
#include "SimpleEventManagerImp.hpp"

namespace sem {
    SimpleEventManager::SimpleEventManager()
     : _semImp(SimpleEventManagerImp::create())
    {}

    SimpleEventManager::~SimpleEventManager() = default;

    EventRaiserInterfacePtr SimpleEventManager::registerEventSource(Event::EventId id,
        EventSourceManagerInterfacePtr esm)
    {
        return _semImp->registerEventSource(id, std::move(esm));
    }

    EventConsumptionInterfacePtr SimpleEventManager::registerEventConsumer(Event::EventId id)
    {
        return _semImp->registerEventConsumer(id);
    }

}

#include "MyEvent.hpp"
#include "SimpleEventManager/Event.hpp"
#include <any>
#include <cstdint>
#include <memory>

const std::string MyEvent::_eventIdString = "Event0";


std::any MyEvent::doGetValue(std::string const & key, std::any const &defaultValue)
{
    if (_data.find(key) != _data.end()) {
        return _data.at(key);
    }

    return defaultValue;
}

void MyEvent::doSetValue(std::string const & key, std::any const &value)
{
    _data[key] = std::any_cast<uint64_t>(value);
}

MyEvent::MyEvent(uint64_t data)
    : sem::Event(std::hash<std::string>{}(_eventIdString))
{
    setValue("value", data);
}

std::string const & MyEvent::getEventIdString()
{
    return _eventIdString;
}

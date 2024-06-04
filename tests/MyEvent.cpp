#include "MyEvent.hpp"
#include "SimpleEventManager/Event.hpp"
#include <cstdint>
#include <memory>

const std::string MyEvent::_eventIdString = "Event0";


uint64_t MyEvent::getValue(std::string key, uint64_t const &defaultValue)
{
    if (_data.find(key) != _data.end()) {
        return _data.at(key);
    }

    return defaultValue;
}

void MyEvent::setValue(std::string key, uint64_t const &value)
{
    _data[key] = value;
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

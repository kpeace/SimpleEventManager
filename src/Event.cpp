#include <SimpleEventManager/Event.hpp>

namespace sem {

Event::Event(Event const &) = default;

Event::Event(Event &&) noexcept = default;

Event::~Event() = default;

Event & Event::operator=(Event const &) = default;

Event & Event::operator=(Event &&) noexcept = default;

Event::EventId Event::getId() const
{
    return _id;
}

}

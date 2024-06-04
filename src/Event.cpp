#include <SimpleEventManager/Event.hpp>

namespace sem {

Event::EventId const Event::getId() const
{
    return _id;
}

}

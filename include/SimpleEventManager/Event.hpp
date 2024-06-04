#pragma once

#include <cstdint>

namespace sem {

class Event
{
public:
    using EventId = uint64_t;

    explicit Event(EventId id)
    : _id(id)
    {
    }

    [[nodiscard]] EventId const getId() const;

private:
    EventId _id;
};

} // end of namespace sem

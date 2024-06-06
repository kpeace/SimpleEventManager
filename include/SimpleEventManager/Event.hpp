#pragma once

#include <cstdint>
#include <string>
#include <any>

namespace sem {

class Event
{
public:
    using EventId = uint64_t;

    Event() = delete;

    explicit Event(EventId id)
    : _id(id)
    {
    }

    Event(Event const &);
    Event(Event &&) noexcept ;

    virtual ~Event();

    Event & operator=(Event const &);
    Event & operator=(Event &&) noexcept;

    [[nodiscard]] EventId getId() const;

    // getting and setting data
    template <typename T>
    T getValue(std::string const & key, T const & defaultValue)
    {
        return std::any_cast<T>(doGetValue(key, defaultValue));
    }

    template <typename T>
    void setValue(std::string const & key, T const & value)
    {
        doSetValue(key, std::any(value));
    }

protected:
    virtual std::any doGetValue(std::string const & key, std::any const & defaultValue) = 0;
    virtual void doSetValue(std::string const & key, std::any const & value) = 0;

private:
    EventId _id;
};

} // end of namespace sem

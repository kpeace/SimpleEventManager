#include <string>
#include <memory>

namespace sem {

class EventDataInterface
{
public:
    template <typename T>
    T getValue(std::string, T const &);

    template <typename T>
    void setValue(std::string, T const &);
};

class EventBase
{
public:
    template <typename T>
    T getValue(std::string key, T const & defaultValue)
    {
        return _data->getValue(key, defaultValue);
    }

    template <typename T>
    void setValue(std::string key, T const & value)
    {
        _data->setValue(key, value);
    }

private:
    std::unique_ptr<EventDataInterface> _data;
};

} // end of namespace sem
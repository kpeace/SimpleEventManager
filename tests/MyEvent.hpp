#include <SimpleEventManager/Event.hpp>
#include <cstdint>
#include <unordered_map>
#include <string>

using MyDataContainer = std::unordered_map<std::string, uint64_t>;

class MyEvent : public sem::Event
{
public:
    explicit MyEvent(uint64_t);
    static std::string const & getEventIdString();

    uint64_t getValue(std::string, uint64_t const &);

    void setValue(std::string, uint64_t const &);
private:
    static const std::string _eventIdString;
    MyDataContainer _data;
};

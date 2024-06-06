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

protected:
    std::any doGetValue(std::string const & key, std::any const &defaultValue) final;

    void doSetValue(std::string const &key, std::any const &value) final;
private:
    static const std::string _eventIdString;
    MyDataContainer _data;
};

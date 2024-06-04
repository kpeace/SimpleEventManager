#include <SimpleEventManager/EventConsumptionInterface.hpp>
#include <SimpleEventManager/SimpleEventManager.hpp>
#include <atomic>
#include <thread>

class TestEventConsumer
{
public:
    explicit TestEventConsumer(sem::SimpleEventManager &);
    ~TestEventConsumer();
private:
    void doConsume();

    sem::EventConsumptionInterfacePtr _consumption;
    std::atomic_bool _running;
    std::thread _consumerThread;
};

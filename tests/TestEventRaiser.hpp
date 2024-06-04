#include "MyEvent.hpp"
#include <atomic>
#include <chrono>
#include <memory>
#include <SimpleEventManager/SimpleEventManager.hpp>
#include <thread>


namespace sem {

class EventRaiserInterface;

}


class TestEventRaiser
{
public:
    TestEventRaiser(sem::SimpleEventManager &, std::chrono::milliseconds);
    ~TestEventRaiser();
    void start();
    void stop();
private:
    void doRaiseEvent();

    std::chrono::milliseconds _interval;
    std::unique_ptr<sem::EventRaiserInterface> _eventRaiser;
    std::atomic_bool _running;
    std::thread _raiserThread;
};

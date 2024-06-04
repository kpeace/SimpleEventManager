#include "TestEventRaiser.hpp"
#include <SimpleEventManager/EventRaiserInterface.hpp>
#include <SimpleEventManager/EventSourceManagerInterface.hpp>
#include <cstdint>
#include <memory>
#include <thread>

class TestEventRaiserManager : public sem::EventSourceManagerInterface
{
public:
    explicit TestEventRaiserManager(TestEventRaiser *testEventRaiser)
     : _testEventRaiser(testEventRaiser)
     {}

    void startEventSource() final
    {
        _testEventRaiser->start();
    }
    void stopEventSource() final
    {
        _testEventRaiser->stop();
    }
private:
    TestEventRaiser *_testEventRaiser;
};

TestEventRaiser::TestEventRaiser(sem::SimpleEventManager & evMgr, std::chrono::milliseconds interval)
    : _eventRaiser(evMgr.registerEventSource(std::hash<std::string>{}(MyEvent::getEventIdString()),
        std::make_unique<TestEventRaiserManager>(this)))
    , _interval(interval)
    , _running(false)
    {}

TestEventRaiser::~TestEventRaiser()
{
    _running = false;
    _eventRaiser->unregister();
    if (_raiserThread.joinable())
    {
        _raiserThread.join();
    }
}

void TestEventRaiser::start()
{
    _running = true;
    _raiserThread = std::thread([this]{doRaiseEvent();});
}

void TestEventRaiser::stop()
{
    _running = false;
}

void TestEventRaiser::doRaiseEvent()
{
    static uint64_t counter = 0;
    while (_running) {
        _eventRaiser->raiseEvent(std::make_shared<MyEvent>(++counter));
        std::this_thread::sleep_for(_interval);
    }
}

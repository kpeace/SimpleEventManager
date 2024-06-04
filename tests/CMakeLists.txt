
add_executable(testSEM
    MyEvent.cpp
    TestEventRaiser.cpp
    TestEventConsumer.cpp
    testSEM.cpp
)

target_compile_features(testSEM PRIVATE cxx_std_17)

target_link_libraries(testSEM
    PRIVATE SimpleEventManager
)

add_test(NAME testSEMtest COMMAND testSEM)

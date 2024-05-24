
add_executable(testSEMX
    testSEM.cpp
)

target_compile_features(testSEMX PRIVATE cxx_std_17)

# target_link_libraries()

add_test(NAME testSEMtest COMMAND testSEMX)
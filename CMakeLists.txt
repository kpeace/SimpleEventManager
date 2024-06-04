cmake_minimum_required(VERSION 3.27)
project(
    "SimpleEventManager"
    VERSION 0.1
    DESCRIPTION "A Simple, Generic, Event Manager"
    LANGUAGES CXX
    )

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(src)

# Testing only available if this is the main app
# Emergency override MODERN_CMAKE_BUILD_TESTING provided as well
#if((CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME OR MODERN_CMAKE_BUILD_TESTING)
#   AND BUILD_TESTING)
  add_subdirectory(tests)
#endif()

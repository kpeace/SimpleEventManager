file(GLOB HEADER_LIST CONFIGURE_DEPENDS "${SimpleEventManager_SOURCE_DIR}/include/SimpleEventManager/*.hpp")

add_library(SimpleEventManager
    Event.cpp
    EventRaiser.cpp
    EventConsumerHandler.cpp
    SimpleEventManagerImp.cpp
    SimpleEventManager.cpp
    ${HEADER_LIST}
)

# We need this directory, and users of our library will need it too
target_include_directories(SimpleEventManager PUBLIC ../include)

# All users of this library will need at least C++17
target_compile_features(SimpleEventManager PUBLIC cxx_std_17)

# IDEs should put the headers in a nice place
source_group(
  TREE "${PROJECT_SOURCE_DIR}/include"
  PREFIX "Header Files"
  FILES ${HEADER_LIST}
)

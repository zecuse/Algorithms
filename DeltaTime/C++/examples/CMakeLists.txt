add_executable(BasicTicker main.cpp)
target_link_libraries(BasicTicker PRIVATE DeltaTime Concurrent)
target_include_directories(BasicTicker PUBLIC ${PROJECT_SOURCE_DIR})

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET BasicTicker PROPERTY CXX_STANDARD 20)
endif() 

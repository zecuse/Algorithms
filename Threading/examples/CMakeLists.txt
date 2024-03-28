add_executable(ThreadingDemo main.cpp)

target_link_libraries(ThreadingDemo PRIVATE Concurrent)
target_include_directories(ThreadingDemo PUBLIC ${PROJECT_SOURCE_DIR})

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ThreadingDemo PROPERTY CXX_STANDARD 20)
endif() 

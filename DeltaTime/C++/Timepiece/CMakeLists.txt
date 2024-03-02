add_library(Timepiece STATIC TimeSpan.hpp Stopwatch.hpp Stopwatch.cpp)
target_link_libraries(Timepiece PUBLIC cxx_setup)
target_include_directories(Timepiece PUBLIC ${PROJECT_SOURCE_DIR})

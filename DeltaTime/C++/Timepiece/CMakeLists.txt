add_library(Timepiece STATIC Stopwatch.cpp Stopwatch.hpp)
target_link_libraries(Timepiece PUBLIC cxx_setup)
target_include_directories(Timepiece PUBLIC ${PROJECT_SOURCE_DIR})

add_library(DeltaTime STATIC Ticker.cpp Ticker.hpp)
target_link_libraries(DeltaTime PRIVATE Timepiece)
target_include_directories(DeltaTime PUBLIC ${PROJECT_SOURCE_DIR})

add_library(DeltaTime STATIC
			Updatable.hpp Ticker.hpp
			Updatable.cpp Ticker.cpp)
target_link_libraries(DeltaTime PRIVATE Timepiece)
target_include_directories(DeltaTime PUBLIC ${PROJECT_SOURCE_DIR})

add_library(TickerDemo STATIC
			TickerDemo1.hpp TickerDemo2.hpp
			TickerDemo1.cpp TickerDemo2.cpp)
target_link_libraries(TickerDemo PUBLIC cxx_setup)
target_include_directories(TickerDemo PUBLIC ${PROJECT_SOURCE_DIR})

add_executable(BasicTicker main.cpp)

find_package(re2 REQUIRED) 

target_link_libraries(BasicTicker PRIVATE TickerDemo DeltaTime Concurrent Utilities re2::re2)
target_include_directories(BasicTicker PUBLIC ${PROJECT_SOURCE_DIR})

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET BasicTicker PROPERTY CXX_STANDARD 20)
endif() 

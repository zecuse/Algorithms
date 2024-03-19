add_library(Utilities STATIC stringUtils.hpp stringUtils.cpp)
target_link_libraries(Utilities PUBLIC cxx_setup)
target_include_directories(Utilities PUBLIC ${PROJECT_SOURCE_DIR})
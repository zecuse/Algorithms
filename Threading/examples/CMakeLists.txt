add_executable(SimpleCondVar SimpleCondVar.cpp)
target_include_directories(SimpleCondVar PUBLIC ${PROJECT_SOURCE_DIR})

add_executable(SimpleSemaphore SimpleSemaphore.cpp)
target_include_directories(SimpleSemaphore PUBLIC ${PROJECT_SOURCE_DIR})

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET SimpleCondVar PROPERTY CXX_STANDARD 20)
  set_property(TARGET SimpleSemaphore PROPERTY CXX_STANDARD 20)
endif() 

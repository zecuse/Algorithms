project(Threading)

add_subdirectory(Concurrent)
add_subdirectory(examples)

if(ENABLE_BUILD_TESTING)
	set(TESTS "")
	#target_sources(${PROJECT_NAME} PRIVATE ${TESTS})
endif()
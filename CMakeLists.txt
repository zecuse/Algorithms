cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(is_msvc $<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>)
  set(debug $<CONFIG:Debug,RelWithDebInfo>)
  set(format $<IF:${is_msvc},$<${debug}:EditAndContinue>,$<${debug}:ProgramDatabase>>)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT ${format})
endif()

project (Algorithms)

add_library(cxx_setup INTERFACE)
if (${is_msvc})
	target_compile_options(cxx_setup INTERFACE -W4)
elseif (CMAKE_COMPILER_IS_GNUCXX)
	target_compile_options(cxx_setup INTERFACE -Wall)
	target_compile_options(cxx_setup INTERFACE -Wextra -Wpedantic)
endif()
target_compile_features(cxx_setup INTERFACE cxx_std_20)

if (ENABLE_BUILD_TESTING)
	list(APPEND CMAKE_PREFIX_PATH "C:/Program Files (x86)/googletest-distribution")
	enable_testing()
	find_package(GTest REQUIRED)
endif() 

if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/Threading)
	add_subdirectory (Threading)
endif()

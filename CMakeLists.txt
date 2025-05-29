cmake_minimum_required( VERSION 4.0)
# magick from here: https://github.com/Kitware/CMake/blob/v4.0.2/Help/dev/experimental.rst
set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "a9e1cf81-9932-4810-974b-6eccaf14e457")
project( ModelReader LANGUAGES CXX)

	# compiler settings
include( cmake/cpp_config.cmake)

	# deps
include(FetchContent)
include( cmake/libs/g3log.cmake)
include( cmake/libs/gtest.cmake)
include( cmake/libs/benchmark.cmake)
FetchContent_MakeAvailable( g3log gtest benchmark)

	#  srcs
include_directories( "${PROJECT_SOURCE_DIR}/src")
add_executable(main "src/main.cpp")
target_link_libraries(main PRIVATE stdc++exp)

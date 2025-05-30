cmake_minimum_required( VERSION 4.0)
# magick from here: https://github.com/Kitware/CMake/blob/v4.0.2/Help/dev/experimental.rst
set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "a9e1cf81-9932-4810-974b-6eccaf14e457")
project( ModelConverter LANGUAGES CXX)

	# compiler settings
include( cmake/cpp_config.cmake)

	# deps
include(FetchContent)
include( cmake/libs/g3log.cmake)
include( cmake/libs/tinyobjloader.cmake)
FetchContent_MakeAvailable( g3log tinyobjloader)

	#  srcs
include_directories( "${PROJECT_SOURCE_DIR}/src" "${g3sinks_SOURCE_DIR}/sink_snippets/src")
add_executable(convert_model "src/convert_model.cpp")
target_sources(convert_model PRIVATE
	FILE_SET modules TYPE CXX_MODULES FILES
		# model
	"src/model/format.cppm" "src/model/convert.cppm"
			# formats
	"src/model/formats/obj.cppm" "src/model/formats/stl.cppm"
)

target_link_libraries(convert_model PRIVATE stdc++exp g3log tinyobjloader) # note the stdc++exp!

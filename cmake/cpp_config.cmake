list( APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")
include( add_compile_options_cxx)
message( STATUS "cpp config..")

	#  Basic c++ settings
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_MODULE_STD ON)

	#  proper module support requires gcc15..
if (CMAKE_COMPILER_IS_GNUCXX)
	if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 15)
		message( WARANING "minimum gcc version 15 required")
	endif()
	add_compile_options_cxx( -Wall -Wextra -fdiagnostics-color=always)
endif()

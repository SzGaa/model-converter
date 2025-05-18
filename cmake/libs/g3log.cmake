FetchContent_Declare(
	g3log
	GIT_REPOSITORY	https://github.com/KjellKod/g3log
	GIT_TAG			2.4
	GIT_SHALLOW TRUE
	GIT_PROGRESS TRUE
)
option(ADD_G3LOG_UNIT_TEST "" OFF)
option(ADD_FATAL_EXAMPLE "" OFF)
option(G3_SHARED_LIB "" OFF)
option(USE_DYNAMIC_LOGGING_LEVELS "" ON)

FetchContent_Declare(
	benchmark
	GIT_REPOSITORY https://github.com/google/benchmark
	GIT_TAG		   v1.9.3
	GIT_SHALLOW TRUE
	GIT_PROGRESS TRUE
)

option(BENCHMARK_ENABLE_TESTING "Enable testing of the benchmark library." OFF)

# populates compile options flags for c/c++ language
# nicer solution, than manually populating CXX_FLAGS etc..
function( add_compile_options_cxx)
	foreach( opt ${ARGV})
		message( STATUS "  c++ option: ${opt}")
		add_compile_options($<$<COMPILE_LANGUAGE:C,CXX>:${opt}>)
	endforeach()
endfunction()

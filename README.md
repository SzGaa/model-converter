# Model Converter Experimantal Project

Experimental project using modern tools and c++ features.
- c++23
- gcc-15 with import std
- cmake 4.0


##  Usage

Build the container via docker or podman.
Enter to the project's root folder.

```
docker build -f container/env_ubuntu_gcc -t szgaa/build .
```

The container contains the dependencies to build and run the project.

```
docker run --rm -it -v .:/app szgaa/build bash
```

Example build of the project using cmake & ninja.

```
cmake -Bbuild -GNinja . -DCMAKE_POLICY_VERSION_MINIMUM=3.5
cmake --build build
./build/convert_model ./data/teapot.obj
```

Use https://3dviewer.net/ to inspect the original and the generated files.


##  Conclusion

Modules have clear benefits over the traditional c++ include system and would be practical to be
used in the future, but..

In its current state it is not yet recommended for bigger projects as it still faces some
serious limitations!

pro:
- cleaner, denser, safer structure
- module interface and implementation can be placed into the same file
- potentially faster compilations


**Limitations** I faced even for such a small project:
- TU entities can't be part of the module interface
	- https://en.cppreference.com/w/cpp/language/tu_local.html
	- tried to use armadillo for vector representation and optimized math, but can't worked out
	- Model is part of the interface, no easy quick workaround
		- in bigger projects you clearly want such basic types to be part of your module interface
- limited std import support
	- gcc-15 still not implemented all std imports I tried to use
- can't mix imported and header included std libraries
	- it technically means you can't use import std until your code uses non module friendly 3rd party
		- LLM based code generation can help to resolve such issues much quicker than one might expect
- limited module support
	- 'module: private;' not yet implemented
	- can't place interface and implementation in single file
		- I wanted to get a feel of this, so implemented this way
		- bloats the BMI

All major compilers have basic module support by now.
If you are aware of the limitations I would happily suggest to use it for smaller even production projects.

**Modern c++ needs modules, but it is not yet there**

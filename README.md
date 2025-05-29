# Obj Reader Test Project for Shapr3d

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
./build/main
```

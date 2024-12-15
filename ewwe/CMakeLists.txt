cmake_minimum_required(VERSION 3.30)
project(ewwe)

set(CMAKE_CXX_STANDARD 26)

add_executable(ewwe cmake-build-debug/centralmanager.cpp
        cmake-build-debug/World.cpp
        cmake-build-debug/World.h
        cmake-build-debug/entitymanager.cpp
        cmake-build-debug/entitymanager.h
        cmake-build-debug/Entity.cpp
        cmake-build-debug/Entity.h
        cmake-build-debug/Datastructs.cpp
        cmake-build-debug/Datastructs.h
        cmake-build-debug/PhysicsManager.cpp
        cmake-build-debug/PhysicsManager.h
        cmake-build-debug/Chunk.cpp
        cmake-build-debug/Chunk.h
        cmake-build-debug/Octree.cpp
        cmake-build-debug/Octree.h)

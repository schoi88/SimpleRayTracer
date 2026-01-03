cmake_minimum_required(VERSION 3.28.3)

project(RayTracer LANGUAGES CXX)

set(SOURCE_FILES
    ./src/main.cpp
    ./src/Camera.cpp
    ./src/HittableList.cpp
    ./src/Sphere.cpp
)

add_executable(RayTrace ${SOURCE_FILES})
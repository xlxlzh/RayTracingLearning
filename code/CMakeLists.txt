set(SRC_LIST src/HitableList.cpp src/Sphere.cpp src/Vector3.cpp main.cpp)
include_directories(include include/stb)
add_subdirectory(src)
add_executable(RayTracing ${SRC_LIST})
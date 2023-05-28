cmake_minimum_required(VERSION 3.0)


set (CMAKE_CXX_STANDARD 11)
# Executable & linking
add_executable(${PROJECT_NAME} main.cpp snake.cpp)
if (NOT TARGET raylib)
  find_package(raylib 2.5.0 REQUIRED)
endif()
target_link_libraries(${PROJECT_NAME} raylib)
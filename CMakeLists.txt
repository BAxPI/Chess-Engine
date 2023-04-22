cmake_minimum_required(VERSION 3.0.0)
project(Chess-Engine VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(Chess-Engine main.cpp board.cpp attacks.cpp xorshift_random.cpp)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
set(CMAKE_CXX_STANDARD 17)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

cmake_minimum_required(VERSION 3.0.0)
project(Chess-Engine VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(Chess-Engine main.cpp board.cpp leapers_attack.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

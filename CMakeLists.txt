# The minimum version of CMake that is required.
cmake_minimum_required(VERSION 3.0.0)

# The name & the version of the project
project(Chess-Engine VERSION 0.1.0)

# Including the CTest frame work, it allows to add custom tests (Which I don't have yet!)
include(CTest)
enable_testing()

# Adds an executable target name that consist the following .cpp files.
add_executable(Chess-Engine main.cpp board.cpp attacks.cpp xorshift_random.cpp Bitboards.cpp)

# Checks if the compiler is GCC or Clang then adds compilation flags for errors & warnings.
if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    add_compile_options(-Wall -Wextra -pedantic -Werror -Wno-unused-parameter -Wno-unused-variable)
endif()

# Sets the standard to be c++17
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

# Debugging options
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS_DEBUG "-g")

# Add custom build target for Valgrind checking.
find_program(VALGRIND "valgrind")
if(VALGRIND)
    add_custom_target(valgrind-check
        COMMAND ${VALGRIND} --leak-check=full --show-leak-kinds=all $<TARGET_FILE:Chess-Engine>
        DEPENDS Chess-Engine
    )
endif()


# Specifying the CPACK project name (Not in use atm.)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
# Specifying the CPACK Project version (Not in use atm.)
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
# Used to package the project for distribution (Non in use atm.)
include(CPack)

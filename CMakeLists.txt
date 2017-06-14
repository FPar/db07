cmake_minimum_required(VERSION 3.2)

project(db07)

set(CMAKE_CXX_STANDARD 11)

if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic")
endif()

add_subdirectory(src)
add_subdirectory(tests)

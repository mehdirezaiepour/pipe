#
# Created by Piade on 7/12/19.
#


cmake_minimum_required(VERSION 3.12)
project(named_pipe)

set(PROJECT_DIR   ${CMAKE_CURRENT_SOURCE_DIR} )
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_DIR}/bin)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE "Release")


set(CMAKE_CXX_FLAGS_DEBUG    "-pthread   -O1 -g -Wall -Wextra -Werror")
set(CMAKE_CXX_FLAGS_RELEASE  "-pthread   -O3    -Wall -Wextra        ")

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING
            "Choose the type of build, options are: Debug Release."
            FORCE)
endif(NOT CMAKE_BUILD_TYPE)

find_package (Threads)

include_directories(${PROJECT_DIR}/include)

add_subdirectory(${PROJECT_DIR}/src)

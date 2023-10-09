cmake_minimum_required(VERSION 3.21)

#-----------------------------------------------------------------------------------------

project(caches)

#-----------------------------------------------------------------------------------------

set(TESTING_ENABLED ON CACHE BOOL [FORCE])

#-----------------------------------------------------------------------------------------

set(CMAKE_BUILD_TYPE "Debug")

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_definitions(MY_DEBUG)
    message("Debug_version")
endif ()

#-----------------------------------------------------------------------------------------

add_subdirectory(./cache/)

if (TESTING_ENABLED)
    add_subdirectory(./tests/)
endif()

unset(TESTING_ENABLED CACHE)


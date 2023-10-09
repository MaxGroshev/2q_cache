cmake_minimum_required(VERSION 3.21)

#-----------------------------------------------------------------------------------------

project(cache)

#-----------------------------------------------------------------------------------------

#Root dir src
set(SOURCE
    ./user_interface.cpp)

#Figures
set(2Q_SRC
    ./2q_cache/main.cpp)

set(PERF_LRU
    ./perf_cache/main.cpp)

#Debug
set(DEBUG_UTILS
    ../debug_utils/error_control/error_control.cpp)

#-----------------------------------------------------------------------------------------

add_executable(2q_cache ${SOURCE} ${2Q_SRC} ${DEBUG_UTILS})
add_executable(perf_lru ${SOURCE} ${PERF_LRU} ${DEBUG_UTILS})

target_include_directories(2q_cache PRIVATE
                            ./perf_cache/
                            ./2q_cache/
                            ../debug_utils/
                            ../debug_utils/error_control/
                            ../debug_utils/logs/
                            ../debug_utils/time_control/
                            ./)

target_include_directories(perf_lru PRIVATE
                            ./perf_cache/
                            ./2q_cache/
                            ../debug_utils/
                            ../debug_utils/error_control/
                            ../debug_utils/logs/
                            ../debug_utils/time_control/
                            ./)






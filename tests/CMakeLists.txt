cmake_minimum_required (VERSION 3.21)

#-----------------------------------------------------------------------------------------

project (tests)

#-----------------------------------------------------------------------------------------

#Unit_tests
set (TESTS
    ./main.cpp
    ../cache/user_interface.cpp)

#Debug
set (DEBUG_UTILS
    ../debug_utils/error_control/error_control.cpp)

#-----------------------------------------------------------------------------------------

include_directories(e2e_tests PRIVATE ../cache/2q_cache/
                                      ../cache/perf_cache/
                                      ../cache/)

add_executable            (e2e_tests ${TESTS} ${DEBUG_UTILS})
target_include_directories(e2e_tests PRIVATE ../debug_utils
                                             ../debug_utils/error_control/
                                             ../debug_utils/logs/
                                             ../debug_utils/time_control/)


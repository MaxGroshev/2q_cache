#ifndef TESTING_HPP
#define TESTING_HPP

//-----------------------------------------------------------------------------------------

#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <list>
#include <iterator>
#include <unordered_map>

#include "../cache/user_interface.hpp"
#include "../cache/perf_cache/perf_lru_cache.hpp"
#include "../cache/2q_cache/2q_cache.hpp"
#include "../debug_utils/debug_utils.hpp"
#include "../debug_utils/console_colors.hpp"

const int count_of_perf_lru_tests = 7;
const int count_of_2_q_tests      = 5;

//-----------------------------------------------------------------------------------------

int test_perf_lru   ();
int test_two_q      ();
int get_correct_res (std::istream & in_strm);
int show_test_res   (int num_of_test, int hits, int correct_res, double test_time);

#endif

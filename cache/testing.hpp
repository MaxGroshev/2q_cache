#ifndef TESTING_HPP
#define TESTING_HPP

//-----------------------------------------------------------------------------------------

#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <list>
#include <queue>
#include <iterator>
#include <unordered_map>

#include "./perf_lru_cache.hpp"
#include "./2q_cache.hpp"
#include "../debug_utils/error_control.h"

//-----------------------------------------------------------------------------------------

inline int int_get_page (int key) {return key; };
int cache_test ();
int skip_wrong_input ();
int get_init_data (size_t* cache_size, size_t* count_of_elem, std::istream & in_strm = std::cin);
int test_user_data (const size_t count_of_elem, cache::perf_lru_t<int>& lru, int* data);
int get_test_data ();

#endif

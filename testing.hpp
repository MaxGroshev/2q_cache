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

#include "./cache.hpp"
#include "./2q_cache.hpp"
#include "./debug_utils/error_control.h"

//-----------------------------------------------------------------------------------------

inline int int_get_page (int key) {return key; };
int cache_test ();
int skip_wrong_input ();
int get_init_data (size_t* cache_size, size_t* count_of_elem, std::istream & is = std::cin);
int get_test_data (int* hits, const size_t count_of_elem, cache::two_q_cache_t<int>& lru,
                                                          std::istream & is = std::cin);
int ger_test_data ();

#endif

#ifndef USER_INTERFACE_HPP
#define USER_INTERFACE_HPP

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

int get_init_data (size_t* cache_size, size_t* count_of_elem, std::istream & in_strm = std::cin);
int skip_wrong_input ();


#endif
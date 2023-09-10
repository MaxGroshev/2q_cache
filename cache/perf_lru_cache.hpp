#ifndef PERF_LRU_CACHE_HPP
#define PERF_LRU_CACHE_HPP

//-----------------------------------------------------------------------------------------

#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <list>
#include <iterator>
#include <unordered_map>

#include "./lru_cache.hpp"
#include "../debug_utils/error_control.h"

//-----------------------------------------------------------------------------------------

namespace cache {

template <typename T, typename KeyT = int>
class perf_lru_t : public cache_t <T, KeyT> {
    using list_iter  = typename std::list<std::pair<KeyT, T>>::iterator;
    using hash_iter  = typename std::unordered_map<KeyT, list_iter>::iterator;
    using lru_object = cache_t <T, KeyT>;
    private:
        std::unordered_map<T, std::list<size_t>> data_hash;
    public:
        //Constructor & distructor
        explicit perf_lru_t (size_t size_ = 0);
        virtual ~perf_lru_t ();
        //Others methods
        template <typename F>
        bool check_update (KeyT key, F get_page);
        int  update_data_hash (KeyT key);
        int  pop_not_soon_access  (KeyT key);
        auto find_not_soon_access (KeyT key) -> list_iter;
        T*   get_user_data  (const size_t count_of_elem, std::istream & in_strm);
        int  dump_data_hash ();
        //Test method
        int  test_data (const size_t count_of_elem, T* data);
};
#include "./perf_lru_cache.tpp"
}

//-----------------------------------------------------------------------------------------

#endif

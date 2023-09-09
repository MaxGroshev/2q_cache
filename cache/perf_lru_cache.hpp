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
        //std::list<std::pair<KeyT, T>> cache;
        std::unordered_map<KeyT, list_iter> data_hash;
    public:
        //Constructor & distructor
        explicit perf_lru_t (size_t size_ = 0);
        virtual ~perf_lru_t ();
        //Inline methods
        //--
        //Others methods
        template <typename F>
        bool check_update  (KeyT key, F get_page);
};
#include "./perf_lru_cache.tpp"
}

//-----------------------------------------------------------------------------------------

#endif

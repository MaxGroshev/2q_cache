#ifndef TWO_Q_CACHE_HPP
#define TWO_Q_CACHE_HPP

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
#include "./debug_utils/error_control.h"

//-----------------------------------------------------------------------------------------

namespace cache {

template <typename T, typename KeyT = int>
class two_q_cache_t {
    public:
        size_t hot_size;
        size_t a1_in_size;
        size_t a1_out_size;
        cache_t<T, KeyT> lru_hot {hot_size};
        cache_t<T, KeyT> a1_in   {a1_in_size};
        //std::queue<std::pair<KeyT, T>> a1_out;
    public:
        //Constructor & distructor
        explicit two_q_cache_t (size_t size_);
        virtual ~two_q_cache_t ();
        //Inline methods
        //inline bool is_full () const { return (lru_hot.size () == hot_size); };
        //Others methods
        template <typename F>
        bool check_update (KeyT key, F get_page);
};
#include "./2q_cache.tpp"
}

//-----------------------------------------------------------------------------------------

#endif

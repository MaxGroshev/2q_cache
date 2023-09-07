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
class two_q_cache_t { //TODO: legacy from cache_t
    using list_iterat = typename std::list<std::pair<KeyT, T>>::iterator;
    public:
        size_t hot_size;
        size_t a1_in_size;
        size_t a1_out_size;
        cache_t<T, KeyT> lru_hot {hot_size};
        cache_t<T, KeyT> a1_in   {a1_in_size};
        cache_t<T, KeyT> a1_out  {a1_out_size};
    public:
        //Constructor & distructor
        explicit two_q_cache_t (size_t size_);
        virtual ~two_q_cache_t ();
        //Inline methods
        //Others methods
        template <typename F>
        bool check_update    (KeyT key, F get_page);
        template <typename F>
        int  add_to_a1_in    (KeyT key, F get_page);
        int  get_from_a1_out (KeyT key, list_iterat elem);
        int  move_to_head_in_hot_lru (list_iterat elem);
        int  move_from_a1_in_to_out ();
};
#include "./2q_cache.tpp"
}

//-----------------------------------------------------------------------------------------

#endif

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

#include "./lru_cache.hpp"
#include "./debug_utils/error_control.h"

//-----------------------------------------------------------------------------------------

namespace cache {

template <typename T, typename KeyT = int>
class two_q_cache_t {
    using list_iter = typename std::list<std::pair<KeyT, T>>::iterator;
    const size_t least_size_of_cache = 4;
    private:
        size_t a1_in_size;
        size_t hot_lru_size;
        size_t a1_out_size;

        cache_t<T, KeyT> lru_hot{hot_lru_size};
        cache_t<T, KeyT> a1_in  {a1_in_size};
        cache_t<T, KeyT> a1_out {a1_out_size};

        int dump (std::ofstream & os = std::cout);
    public:
        //Constructor & distructor
        explicit two_q_cache_t (size_t size_);
        virtual ~two_q_cache_t ();
        //Others methods
        template <typename F>
        bool check_update    (KeyT key, F get_page);
        template <typename F>
        int  add_to_a1_in    (KeyT key, F get_page);
        int  get_from_a1_out (KeyT key, list_iter elem);
        int  move_to_head_in_hot_lru (list_iter elem);
        int  move_from_a1_in_to_out  ();
        int  dump_cache (const char* name_of_log_file = "./logs_output/cache_dump.txt");
};
#include "./2q_cache.tpp"
}

//-----------------------------------------------------------------------------------------

#endif

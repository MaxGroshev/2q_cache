#ifndef CACHE_HPP
#define CACHE_HPP

//-----------------------------------------------------------------------------------------

#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <list>
#include <queue>
#include <iterator>
#include <unordered_map>

#include "./debug_utils/error_control.h"

//-----------------------------------------------------------------------------------------

namespace cache {

template <typename T, typename KeyT = int>
class cache_t {
    using list_iterat = typename std::list<std::pair<KeyT, T>>::iterator;
    public:
        size_t size;
        std::list<std::pair<KeyT, T>> cache;
        std::unordered_map<KeyT, list_iterat> hash;
        //std::queue<std::pair<KeyT, T>> a1_in;
        //std::queue<std::pair<KeyT, T>> a1_out;
    public:
        //Constructor & distructor
        explicit cache_t (size_t size_ = 0);
        virtual ~cache_t ();
        //Inline methods
        inline bool   is_full () const { return (cache.size () == size); };
        inline size_t size_of () const { return size; };
        //Others methods
        template <typename F>
        bool check_update (KeyT key, F get_page);
};
#include "./cache.tpp"
}

//-----------------------------------------------------------------------------------------

#endif

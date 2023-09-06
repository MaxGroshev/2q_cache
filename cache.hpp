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
    protected:
        size_t size;
        std::list<std::pair<KeyT, T>> cache;
        std::unordered_map<KeyT, list_iterat> hash;
        //std::queue<std::pair<KeyT, T>> a1_in;
        //std::queue<std::pair<KeyT, T>> a1_out;
    public:
        //Constructor & distructor
        explicit cache_t (size_t size_);
        virtual ~cache_t ();
        //Inline methods
        inline bool is_full () const { return (cache.size () == size); };
        //Others methods
        template <typename F>
        bool check_update (KeyT key, F get_page);
};
#include "./cache.tpp"
}

//-----------------------------------------------------------------------------------------

inline int int_get_page (int key) {return key; };
int cache_test ();
int skip_wrong_input ();
int get_init_data (size_t* cache_size, size_t* count_of_elem, std::istream & is = std::cin);
int get_test_data (int* hits, const size_t count_of_elem, cache::cache_t<int>& lru,
                                                          std::istream & is = std::cin);
int ger_test_data ();

#endif

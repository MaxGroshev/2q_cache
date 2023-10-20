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

#include "ASSERT.hpp"
#include "user_interface.hpp"
#include "lru_cache.hpp"

//-----------------------------------------------------------------------------------------

namespace cache {

template <typename T, typename KeyT = int>
class perf_lru_t {
    using list_iter = typename std::list<std::pair<KeyT, T>>::iterator;
    using hash_iter = typename std::unordered_map<KeyT, list_iter>::iterator;
    private:
        std::unordered_map<T, std::list<size_t>> data_occur_hash;
        cache_t<T, KeyT> lru_cache;
    public:
        //Constructor & distructor
        explicit perf_lru_t (size_t size_) : lru_cache (size_) {};

        //Others methods
        bool check_update (const KeyT key, int(*get_page)(int));
        int  update_data_occur_hash (const KeyT key) ;
        list_iter      find_farthest();
        void           pop_farthest ();
        std::vector<T> get_user_data (const size_t count_of_elem,
                                      std::istream & in_strm = std::cin);
        int dump_data_occur_hash () const;

        bool data_will_occur_again (const KeyT key) const {
            return !(data_occur_hash.find(key)->second.size () == 1);
        };
        int test_data (std::vector<T> data);
};
}
#include "./perf_lru_cache.tpp"

//-----------------------------------------------------------------------------------------

#endif

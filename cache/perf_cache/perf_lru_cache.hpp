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

#include "../user_interface.hpp"
#include "../lru_cache.hpp"
#include "../../debug_utils/error_control.h"

//-----------------------------------------------------------------------------------------

namespace cache {

enum type_of_pop_t {
    POPED_NOTHING    = -2,
    POPED_RECEIVED   = -1,
    POPED_FROM_CACHE = 0,
};

template <typename T, typename KeyT = int>
class perf_lru_t : public cache_t <T, KeyT> {
    using list_iter  = typename std::list<std::pair<KeyT, T>>::iterator;
    using hash_iter  = typename std::unordered_map<KeyT, list_iter>::iterator;
    using lru_object = cache_t <T, KeyT>;

    private:
        std::unordered_map<T, std::list<size_t>> data_occur_hash;
    public:
        //Constructor & distructor
        explicit perf_lru_t (size_t size_ = 0);
        virtual ~perf_lru_t ();

        //Others methods
        bool check_update (KeyT key, int(*get_page)(int));
        int  update_data_occur_hash (KeyT key);
        int  pop_farthest  (KeyT key);
        auto find_farthest (KeyT key) -> list_iter;
        std::vector<T> get_user_data (const size_t count_of_elem,
                                      std::istream & in_strm = std::cin);
        int  dump_data_occur_hash ();

        bool data_will_occur_again (KeyT key) const {
            return !(data_occur_hash.find(key)->second.size () == 1);
        };

        //Check that next meeting of received elem is later than next meeting of
        //cached elem
        int recieved_found_later_then_cached (list_iter latest_access_page, KeyT key) {
            ASSERT(latest_access_page != cache.end());
            return (data_occur_hash[latest_access_page->first].front () <=
                                *(std::next(data_occur_hash.find(key)->second.begin())));
        };
        //Testing method
        int  test_data (const size_t count_of_elem, std::vector<T> data);
};
}
#include "./perf_lru_cache.tpp"

//-----------------------------------------------------------------------------------------

#endif

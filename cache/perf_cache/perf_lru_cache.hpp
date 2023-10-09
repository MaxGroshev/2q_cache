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

enum class type_of_pop_t {
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

        //Others methods
        bool check_update (const KeyT key, int(*get_page)(int));
        int  update_data_occur_hash  (const KeyT key) ;
        type_of_pop_t  pop_farthest  (const KeyT key);
        auto find_farthest (const KeyT key) -> list_iter;
        std::vector<T> get_user_data (const size_t count_of_elem,
                                      std::istream & in_strm = std::cin);
        int  dump_data_occur_hash () const;

        bool data_will_occur_again (const KeyT key) const {
            return !(data_occur_hash.find(key)->second.size () == 1);
        };
        int test_data (std::vector<T> data);

        int recieved_found_later_then_cached (const KeyT key_of_cached,
                                              const KeyT key_of_received) {
            using namespace std;

            list<size_t> list_with_occurs_received =
                                            data_occur_hash.find(key_of_received)->second;
            size_t occur_to_received = *(next(list_with_occurs_received.begin()));
            size_t occur_to_cached   = data_occur_hash[key_of_cached].front();

            return (occur_to_cached <= occur_to_received);
        };
};
}
#include "./perf_lru_cache.tpp"

//-----------------------------------------------------------------------------------------

#endif

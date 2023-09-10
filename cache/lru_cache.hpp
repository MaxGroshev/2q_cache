#ifndef LRU_CACHE_HPP
#define LRU_CACHE_HPP

//-----------------------------------------------------------------------------------------

#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <list>
#include <iterator>
#include <unordered_map>

#include "../debug_utils/error_control.h"

//-----------------------------------------------------------------------------------------

namespace cache {

template <typename T, typename KeyT = int>
class cache_t {
    using list_iter = typename std::list<std::pair<KeyT, T>>::iterator;
    using hash_iter = typename std::unordered_map<KeyT, list_iter>::iterator;
    public:
        size_t size;
        std::list<std::pair<KeyT, T>> cache;
        std::unordered_map<KeyT, list_iter> hash;
    public:
        //Constructor & distructor
        explicit cache_t (size_t size_ = 0);
        virtual ~cache_t ();
        //Inline methods
        inline bool   is_full   () const { return (cache.size () == size);};
        inline size_t size_of   () const { return size;};
        inline bool   is_cached (hash_iter hit) const { return (hit != hash.end ());};
        //Others methods
        T* get_user_data (const size_t count_of_elem,
                          std::istream & in_strm = std::cin) const;
        template <typename F>
        bool check_update (KeyT key, F get_page);
        int  dump_to_file (const char* name_of_log_file =
                           "./logs_output/perf_lru_dump.txt");
        int  dump_to_strm (std::ostream & os = std::cout);

};
#include "./lru_cache.tpp"
}

//-----------------------------------------------------------------------------------------

#endif

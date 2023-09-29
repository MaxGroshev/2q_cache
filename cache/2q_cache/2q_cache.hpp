#ifndef TWO_Q_CACHE_HPP
#define TWO_Q_CACHE_HPP

//-----------------------------------------------------------------------------------------

#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <list>
#include <iterator>
#include <unordered_map>

#include "../lru_cache.hpp"
#include "../user_interface.hpp"

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

        int dump_to_strm (std::ofstream & os = std::cout);
    public:
        //Constructor & distructor
        explicit two_q_cache_t (size_t size_);
        virtual ~two_q_cache_t ();

        //Others methods
        bool check_update (KeyT key, int(*get_page)(int));
        int  add_to_a1_in (KeyT key, int(*get_page)(int));
        int  move_from_a1_out_to_hot_lru (KeyT key, list_iter elem);
        int  move_to_front_of_hot_lru (list_iter elem);
        int  move_from_a1_in_to_out   ();
        int  dump_to_file (const char* name_of_log_file);
        std::vector<T> get_user_data (const size_t count_of_elem,
                                      std::istream & in_strm = std::cin);

        //Data test method
        int  test_data (std::vector<T> data);
};
}
#include "./2q_cache.tpp"

//-----------------------------------------------------------------------------------------

#endif

#ifndef LRU_CACHE_TPP
#define LRU_CACHE_TPP

namespace cache {

//-----------------------------------------------------------------------------------------

template <typename T, typename KeyT>
cache_t<T, KeyT>::cache_t (size_t size_) {
    ASSERT (size_ >= 0);
    size = size_;
    LOG_DEBUG ("Constructed cache with init size: ", size, '\n');
}

template <typename T, typename KeyT>
cache_t<T, KeyT>::~cache_t () {
    LOG_DEBUG ("Destructed cache with size: ", size, '\n');
}

//-----------------------------------------------------------------------------------------

template <typename T, typename KeyT>
template <typename F>
bool cache_t<T, KeyT>::check_update (KeyT key, F get_page) {
    auto hit = hash.find (key);
    if (hit == hash.end ()) {
        if (is_full ()) {
            hash.erase (cache.back().first);
            cache.pop_back ();
        }
        cache.emplace_front (key, get_page (key));
        hash.emplace        (key, cache.begin ());
        return false;
    }

    auto elem = hit->second;
    if (elem != cache.begin ()) {
        cache.splice (cache.begin (), cache, elem);
    }
    return true;
}

template <typename T, typename KeyT>
T* cache_t<T, KeyT>::get_user_data (const size_t count_of_elem,
                                    std::istream & in_strm) const {
    LOG_DEBUG ("Getting of data for cache\n");

    T* data = (T*) malloc (count_of_elem * sizeof (T));
    ASSERT (!is_nullptr (data));

    for (size_t i = 0; i < count_of_elem; i++) {
        in_strm >> data[i];
        if (!in_strm.good ()) {
            std::cout << "\nWrong input of values\n";
            print_error_message (CUR_POS_IN_PROG);
            exit (-1);
        }
    }
    return data;
}

//-----------------------------------------------------------------------------------------

template <typename T, typename KeyT>
int cache_t<T, KeyT>::dump_to_file (const char* name_of_log_file) {
    using std::endl;

    std::ofstream dump_file;
    dump_file.open (name_of_log_file);
    ASSERT (dump_file.is_open ());

    dump_to_strm (dump_file);
    dump_file.close ();
    return 0;
}

template <typename T, typename KeyT>
int cache_t<T, KeyT>::dump_to_strm (std::ostream & os) {
    ASSERT (os.good ());

    auto cur_node = cache.begin ();
    for (size_t i = 0; cur_node != cache.end (); i++) {
        os << "[" << i << "] key: " << cur_node->first << " , val: "
        << cur_node->second << std::endl;
        cur_node = std::next (cur_node);
    }
    return 0;
}
}
#endif

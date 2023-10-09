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
bool cache_t<T, KeyT>::check_update (KeyT key, int(*get_page)(int)) {
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
std::vector<T> cache_t<T, KeyT>::get_user_data (const size_t count_of_elem,
                                    std::istream & in_strm) const {
    LOG_DEBUG ("Getting of data for cache\n");

    std::vector<T> data;
    T val = 0;
    for (size_t i = 0; i < count_of_elem; i++) {
        in_strm >> val;
        data.push_back (val);
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
int cache_t<T, KeyT>::dump_to_strm (std::ostream & os) const{
    ASSERT (os.good ());

    for (auto const& [key, value] : cache) {
        std::cout << "[" << key << "] : " << value << '\n';
    }
    return 0;
}
}

#endif

#ifndef PERF_LRU_CACHE_TPP
#define PERF_LRU_CACHE_TPP

//-----------------------------------------------------------------------------------------

template <typename T, typename KeyT>
perf_lru_t<T, KeyT>::perf_lru_t (size_t size_) : cache_t<T, KeyT> (size_) {

}

template <typename T, typename KeyT>
perf_lru_t<T, KeyT>::~perf_lru_t () {

}

//-----------------------------------------------------------------------------------------

template <typename T, typename KeyT>
template <typename F>
bool perf_lru_t<T, KeyT>::check_update (KeyT key, F get_page) {
    auto hit = lru_object::hash.find (key);
    if (hit == lru_object::hash.end ()) {
        if (lru_object::is_full ()) {
            lru_object::hash.erase (lru_object::cache.back().first);
            lru_object::cache.pop_back ();
        }
        lru_object::cache.emplace_front (key, get_page (key));
        lru_object::hash.emplace        (key, lru_object::cache.begin ());

        return false;
    }
    auto elem = hit->second;
    if (elem != lru_object::cache.begin ()) {
        lru_object::cache.splice (lru_object::cache.begin (), lru_object::cache, elem);
    }
    return true;
}

template <typename T, typename KeyT>
T* cache_t<T, KeyT>::get_user_data (const size_t count_of_elem,
                                    std::istream & in_strm) const {
    LOG_DEBUG ("Getting of data for cache\n");

    T* data = (T*) malloc (count_of_elem * sizeof (T*));
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

#endif

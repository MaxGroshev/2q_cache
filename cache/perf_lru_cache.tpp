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
            pop_not_soon_access (key);
        }
        lru_object::cache.emplace_front (key, get_page (key));
        lru_object::hash.emplace        (key, lru_object::cache.begin ());
        update_data_hash (key);
        return false;
    }
    auto elem = hit->second;
    if (elem != lru_object::cache.begin ()) {
        lru_object::cache.splice (lru_object::cache.begin (), lru_object::cache, elem);
        update_data_hash (key);
    }
    return true;
}

//-----------------------------------------------------------------------------------------

template <typename T, typename KeyT>
int perf_lru_t<T, KeyT>::pop_not_soon_access (KeyT key) {
    auto not_soon_access_page = find_not_soon_access (key);
    if (not_soon_access_page->second == key) return 0;
    lru_object::hash.erase (not_soon_access_page->first);
    lru_object::cache.erase (not_soon_access_page);
    LOG_DEBUG ("Removed from perf_lru: ", not_soon_access_page->second, '\n');
    return 0;
}

template <typename T, typename KeyT>
auto perf_lru_t<T, KeyT>::find_not_soon_access (KeyT key) -> list_iter {
    auto cur_node = lru_object::cache.begin ();
    auto not_soon_access_page = cur_node;
    auto hashed_page = data_hash.find (cur_node->first);
    while (cur_node != lru_object::cache.end ()) {
        if ((hashed_page != data_hash.end ()) &&
            (data_hash[key].begin() == data_hash[key].end ())) {
            if (hashed_page->second.front () > data_hash[not_soon_access_page->first].front ()) {
                not_soon_access_page = cur_node;
            }
        }
        cur_node    = std::next (cur_node);
        hashed_page = data_hash.find (cur_node->first);
    }
    return not_soon_access_page;
}

template <typename T, typename KeyT>
int perf_lru_t<T, KeyT>::update_data_hash (KeyT key) {
    data_hash[key].pop_front ();
    if ((data_hash[key].begin() == data_hash[key].end ())) {
        data_hash.erase (key);
    }
    return 0;
}

//-----------------------------------------------------------------------------------------

template <typename T, typename KeyT>
T* perf_lru_t<T, KeyT>::get_user_data (const size_t count_of_elem,
                                       std::istream & in_strm) {
    LOG_DEBUG ("Getting of data for cache\n");

    T* data = (T*) malloc (count_of_elem * sizeof (T*));
    ASSERT (!is_nullptr (data));
    for (size_t i = 0; i < count_of_elem; i++) {
        in_strm >> data[i];
        if (!in_strm.good ()) {
            std::cout << "\nWrong input of values\n";
            print_error_message (CUR_POS_IN_PROG);
            exit (-1);
        };
        data_hash[data[i]].push_back (i);
    }
    dump_data_hash ();
    return data;
}

template <typename T, typename KeyT>
int perf_lru_t<T, KeyT>::dump_data_hash () {
    for (auto map_itr = data_hash.begin (); map_itr != data_hash.end (); map_itr++) {
        std::cout << "Key [" << map_itr->first << ']' << ": ";
        for(auto l_itr = map_itr->second.begin (); l_itr != map_itr->second.end (); l_itr++) {
            std::cout<< *l_itr <<", ";
        }
        std::cout << std::endl;
    }
    return 0;
}

#endif

#ifndef PERF_LRU_CACHE_TPP
#define PERF_LRU_CACHE_TPP

namespace cache {

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
        if (!data_will_occur_again (key)) {
            update_data_occur_hash (key);
            return false;
        }

        else if (lru_object::is_full ()) {
            int pop_type = pop_farthest (key);
            if (pop_type == POPED_RECEIVED) {
                update_data_occur_hash (key);
                return false;
            }
        }
        lru_object::cache.emplace_front (key, get_page (key));
        lru_object::hash.emplace        (key, lru_object::cache.begin ());
        update_data_occur_hash (key);
        return false;
    }

    auto elem = hit->second;
    if (elem != lru_object::cache.begin ()) {
        lru_object::cache.splice (lru_object::cache.begin (), lru_object::cache, elem);
    }
    update_data_occur_hash (key);
    return true;
}

//-----------------------------------------------------------------------------------------

template <typename T, typename KeyT>
int perf_lru_t<T, KeyT>::pop_farthest (KeyT key) {
    auto latest_access_page = find_farthest (key);
    if (recieved_found_later_then_cached (latest_access_page, key)) {
        return POPED_RECEIVED;
    }

    lru_object::hash.erase  (latest_access_page->first);
    lru_object::cache.erase (latest_access_page);

    LOG_DEBUG ("Removed from perf_lru: ", latest_access_page->second, '\n');
    return POPED_FROM_CACHE;
}

template <typename T, typename KeyT>
auto perf_lru_t<T, KeyT>::find_farthest (KeyT key) -> list_iter {
    auto cur_node = lru_object::cache.begin ();
    auto latest_access_page = cur_node;
    auto hashed_page = data_occur_hash.find (cur_node->first);

    while (cur_node != lru_object::cache.end ()) {
        if ((hashed_page == data_occur_hash.end ()) ||
            (data_occur_hash[key].begin() == data_occur_hash[key].end ())) {
            return cur_node;
        }
        else if (hashed_page->second.front () >
                                        data_occur_hash[latest_access_page->first].front ()) {
            latest_access_page = cur_node;
        }
        cur_node    = std::next (cur_node);
        hashed_page = data_occur_hash.find (cur_node->first);
    }
    return latest_access_page;
}

template <typename T, typename KeyT>
int perf_lru_t<T, KeyT>::update_data_occur_hash (KeyT key) {
    data_occur_hash[key].pop_front ();
    if (data_occur_hash[key].begin() == data_occur_hash[key].end ()) {
        data_occur_hash.erase (key);
    }
    return 0;
}

//-----------------------------------------------------------------------------------------

template <typename T, typename KeyT>
T* perf_lru_t<T, KeyT>::get_user_data (const size_t count_of_elem,
                                       std::istream & in_strm) {
    LOG_DEBUG ("Get data for cache\n");

    T* data = (T*) malloc (count_of_elem * sizeof (T*));
    ASSERT (!is_nullptr (data));

    for (size_t i = 0; i < count_of_elem; i++) {
        in_strm >> data[i];
        if (!in_strm.good ()) {
            std::cout << "\nWrong input of values\n";
            print_error_message (CUR_POS_IN_PROG);
            exit (-1);
        };
        data_occur_hash[data[i]].push_back (i);
    }
    //dump_data_occur_hash ();
    return data;
}

template <typename T, typename KeyT>
int perf_lru_t<T, KeyT>::dump_data_occur_hash () {
    for (auto map_itr = data_occur_hash.begin (); map_itr != data_occur_hash.end (); map_itr++) {
        std::cout << "Key [" << map_itr->first << ']' << ": ";
        for(auto l_itr = map_itr->second.begin (); l_itr != map_itr->second.end (); l_itr++) {
            std::cout<< *l_itr <<", ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    return 0;
}

//Testing_of_data==========================================================================

template <typename T, typename KeyT>
int perf_lru_t<T, KeyT>::test_data (const size_t count_of_elem, T* data) {
    LOG_DEBUG ("Testing of perf_lru cache\n");

    ASSERT (!is_nullptr (data));

    int hits = 0;
    for (size_t i = 0; i < count_of_elem; i++) {
        if (perf_lru_t::check_update (data[i], int_get_page)) hits++;
    }
    return hits;
}
}
#endif

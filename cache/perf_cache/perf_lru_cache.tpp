#ifndef PERF_LRU_CACHE_TPP
#define PERF_LRU_CACHE_TPP

namespace cache {

//-----------------------------------------------------------------------------------------

template <typename T, typename KeyT>
perf_lru_t<T, KeyT>::perf_lru_t (size_t size_) : cache_t<T, KeyT> (size_) {
}

//-----------------------------------------------------------------------------------------

template <typename T, typename KeyT>
bool perf_lru_t<T, KeyT>::check_update (KeyT key, int(*get_page)(int)) {
    auto hit = lru_object::hash.find (key);

    if (hit == lru_object::hash.end ()) {
        if (!data_will_occur_again (key)) {
            update_data_occur_hash (key);
            return false;
        }

        else if (lru_object::is_full ()) {
            type_of_pop_t pop_type = pop_farthest (key);
            if (pop_type == type_of_pop_t::POPED_RECEIVED) {
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
type_of_pop_t perf_lru_t<T, KeyT>::pop_farthest (KeyT key) {
    list_iter latest_access_page = find_farthest (key);
    ASSERT(latest_access_page != cache.end())

    if (recieved_found_later_then_cached (latest_access_page, key)) {
        return type_of_pop_t::POPED_RECEIVED;
    }

    lru_object::hash.erase  (latest_access_page->first);
    lru_object::cache.erase (latest_access_page);

    LOG_DEBUG ("Removed from perf_lru: ", latest_access_page->second, '\n');
    return type_of_pop_t::POPED_FROM_CACHE;
}

template <typename T, typename KeyT>
auto perf_lru_t<T, KeyT>::find_farthest (KeyT key) -> list_iter {
    auto node = lru_object::cache.begin ();
    auto latest_access_page = node;
    auto hashed_page = data_occur_hash.find (node->first);

    for (;node != lru_object::cache.end (); node = std::next (node)) {
        hashed_page = data_occur_hash.find (node->first);

        if ((hashed_page == data_occur_hash.end ()) || data_occur_hash[key].empty()) {
            return node;
        }
        else if (hashed_page->second.front () >
                                        data_occur_hash[latest_access_page->first].front ()) {
            latest_access_page = node;
        }
    }
    return latest_access_page;
}

template <typename T, typename KeyT>
int perf_lru_t<T, KeyT>::update_data_occur_hash (KeyT key) {
    data_occur_hash[key].pop_front ();
    if (data_occur_hash[key].empty()) {
        data_occur_hash.erase (key);
    }
    return 0;
}

//-----------------------------------------------------------------------------------------

template <typename T, typename KeyT>
std::vector<T> perf_lru_t<T, KeyT>::get_user_data (const size_t count_of_elem,
                                                   std::istream & in_strm) {
    LOG_DEBUG ("Get data for cache\n");

    std::vector<T> data;
    T val;
    for (size_t i = 0; i < count_of_elem; i++) {
        in_strm >> val;
        data.push_back(val);
        if (!in_strm.good ()) {
            std::cout << "\nWrong input of values\n";
            print_error_message (CUR_POS_IN_PROG);
            exit (-1);
        };
        data_occur_hash[data[i]].push_back (i);
    }
   // dump_data_occur_hash ();
    return data;
}

template <typename T, typename KeyT>
int perf_lru_t<T, KeyT>::dump_data_occur_hash () {
    std::cout << "Dump of occur data\n";

    for (auto const& key : data_occur_hash) {
        std::cout << "[" << key.first << "] : ";
        for(auto const& occurs : key.second) {
            std::cout<< occurs <<", ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    return 0;
}

//Testing_of_data==========================================================================

template <typename T, typename KeyT>
int perf_lru_t<T, KeyT>::test_data (std::vector<T> data) {
    LOG_DEBUG ("Testing of perf_lru cache\n");

    int hits = 0;
    for (T& page : data) {
        if (perf_lru_t::check_update (page, int_get_page)) hits++;
    }
    return hits;
}
}
#endif

#ifndef TWO_Q_CACHE_TPP
#define TWO_Q_CACHE_TPP

//-----------------------------------------------------------------------------------------

template <typename T, typename KeyT>
two_q_cache_t<T, KeyT>::two_q_cache_t (size_t size_) : a1_in_size (size_),
                                                       hot_size   (size_) {
    hot_size = size_;
}

template <typename T, typename KeyT>
two_q_cache_t<T, KeyT>::~two_q_cache_t () {

}

//-----------------------------------------------------------------------------------------

template <typename T, typename KeyT>
template <typename F>
bool two_q_cache_t<T, KeyT>::check_update (KeyT key, F get_page) {
    std::cout << "Here update\n";
    auto res = lru_hot.hash.find (key);
    if (res == lru_hot.hash.end ()) {
        res = a1_in.hash.find (key);
        if (res != a1_in.hash.end ()) {
            auto elem = res->second;
            std::cout << "Key is: " << key << std::endl;
            lru_hot.cache.splice (lru_hot.cache.begin (), a1_in.cache, elem);
            std::cout << lru_hot.cache.front ().first << std::endl;
            a1_in.hash.erase     (lru_hot.cache.front().first);
            lru_hot.hash.emplace (key, lru_hot.cache.begin ());
            std::cout << lru_hot.cache.front ().first << std::endl;
            return false;
        }
        if (a1_in.is_full ()) {
            a1_in.hash.erase (a1_in.cache.back().first);
            a1_in.cache.pop_back ();
        }
        a1_in.cache.emplace_front (key, get_page (key));
        a1_in.hash.emplace        (key, a1_in.cache.begin ());

        return false;
    }
    std::cout << "Get hit\n";
    auto elem = res->second;
    if (elem != lru_hot.cache.begin ()) {
        lru_hot.cache.splice (lru_hot.cache.begin (), lru_hot.cache, elem);
    }

    return true;
}

#endif

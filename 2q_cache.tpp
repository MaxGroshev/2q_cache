#ifndef TWO_Q_CACHE_TPP
#define TWO_Q_CACHE_TPP

//-----------------------------------------------------------------------------------------

template <typename T, typename KeyT>
two_q_cache_t<T, KeyT>::two_q_cache_t (size_t size_) : a1_in_size (size_),
                                                       hot_size   (size_),
                                                       a1_out_size(size_) {
}

template <typename T, typename KeyT>
two_q_cache_t<T, KeyT>::~two_q_cache_t () {

}

//-----------------------------------------------------------------------------------------

template <typename T, typename KeyT>
template <typename F>
bool two_q_cache_t<T, KeyT>::check_update (KeyT key, F get_page) {
    std::cout << "Here to check\n";
    auto res = lru_hot.hash.find (key);
    if (res == lru_hot.hash.end ()) {
        res = a1_in.hash.find (key);
        if (res == a1_in.hash.end ()) {
            res = a1_out.hash.find (key);
            std::cout << "Before cond\n";
            if (res != a1_out.hash.end ()) {
                std::cout << "In a1_out\n";
                auto elem = res->second;
                if (lru_hot.is_full ()) {
                    lru_hot.hash.erase (lru_hot.cache.back().first);
                    lru_hot.cache.pop_back ();
                }
                lru_hot.cache.splice (lru_hot.cache.begin (), a1_out.cache, elem); //end of rewriting
                a1_out.hash.erase    (lru_hot.cache.front().first);
                lru_hot.hash.emplace (key, lru_hot.cache.begin ());
                return false;
            }
            if (a1_in.is_full ()) { //adding to a1_in
                if (a1_out.is_full ()) {
                    a1_out.hash.erase (a1_out.cache.back().first);
                    a1_out.cache.pop_back ();
                }
                std::cout << "Pop from a1_in to a1_out\n";
                auto elem = a1_in.cache.back ();
                a1_in.cache.pop_back();
                a1_out.cache.push_front (elem);
                std::cout << elem.first << std::endl;
                a1_in.hash.erase    (a1_out.cache.front().first);
                a1_out.hash.emplace (elem.second, a1_out.cache.begin ());
            }
            std::cout << "Inserting in a1_in\n";
            a1_in.cache.emplace_front (key, get_page (key));
            a1_in.hash.emplace        (key, a1_in.cache.begin ());
            return false;
        }
        std::cout << "Here I get hit\n";
        return true;
    }
    auto elem = res->second;
    if (elem != lru_hot.cache.begin ()) {
        lru_hot.cache.splice (lru_hot.cache.begin (), lru_hot.cache, elem);
    }

    return true;
}

#endif

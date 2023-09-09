#ifndef LRU_CACHE_TPP
#define LRU_CACHE_TPP

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
        cache.splice (cache.begin (), cache, elem /*std::next (elem)*/);
    }
    return true;
}

template <typename T, typename KeyT>
int cache_t<T, KeyT>::dump (std::ofstream & os) {
    ASSERT (os.good ());
    auto cur_node = cache.begin ();
    for (size_t i = 0; cur_node != cache.end (); i++) {
        os << "[" << i << "] key: " << cur_node->first << " , val: "
        << cur_node->second << std::endl;
        cur_node = std::next (cur_node);
    }
    return 0;
}

#endif
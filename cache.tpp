#ifndef CACHE_TPP
#define CACHE_TPP

//-----------------------------------------------------------------------------------------

template <typename T, typename KeyT>
cache_t<T, KeyT>::cache_t (size_t size_) {
    size = size_;
    std::cerr << "Constructed cache with init size: " << size_ << std::endl;
}

template <typename T, typename KeyT>
cache_t<T, KeyT>::~cache_t () {
    std::cerr << "Destructed cache with init size: " << size << std::endl;
}

//-----------------------------------------------------------------------------------------

template <typename T, typename KeyT>
template <typename F>
bool cache_t<T, KeyT>::check_update (KeyT key, F get_page) {
    auto res = hash.find (key);
    if (res == hash.end ()) {
        if (is_full ()) {
            hash.erase (cache.back().first);
            cache.pop_back ();
        }
        cache.emplace_front (key, get_page (key));
        hash.emplace        (key, cache.begin ());

        return false;
    }
    auto elem = res->second;
    if (elem != cache.begin ()) {
        cache.splice (cache.begin (), cache, elem /*std::next (elem)*/);
    }

    return true;
}

#endif

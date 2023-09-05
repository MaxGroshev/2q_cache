#ifndef CACHE_TPP
#define CACHE_TPP

//-----------------------------------------------------------------------------------------

template <typename T, typename KeyT>
two_q_cache_t<T, KeyT>::two_q_cache_t (size_t size_) {
    size = size_;
}

template <typename T, typename KeyT>
two_q_cache_t<T, KeyT>::~two_q_cache_t () {

}

//-----------------------------------------------------------------------------------------

template <typename T, typename KeyT>
template <typename F>
bool two_q_cache_t<T, KeyT>::check_update (KeyT key, F get_page) {
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

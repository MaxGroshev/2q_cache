#ifndef TWO_Q_CACHE_TPP
#define TWO_Q_CACHE_TPP

namespace cache {

//-----------------------------------------------------------------------------------------

template <typename T, typename KeyT>
two_q_cache_t<T, KeyT>::two_q_cache_t (size_t size_) : a1_in_size (size_ / 4),
hot_lru_size (size_ / 4), a1_out_size (size_- a1_in_size - hot_lru_size) {
    if (size_ < least_size_of_cache) { //how to call constr of cache after check os size?
        std::cout << "Impossible to use my cache with size less then: " ;
        std::cout << least_size_of_cache << std::endl;
        exit (-1);
    }
}

template <typename T, typename KeyT>
two_q_cache_t<T, KeyT>::~two_q_cache_t () {

}

//-----------------------------------------------------------------------------------------

template <typename T, typename KeyT>
template <typename F>
bool two_q_cache_t<T, KeyT>::check_update (KeyT key, F get_page) {
    auto hit = lru_hot.hash.find (key);
    if (!lru_hot.is_cached (hit)) {
        hit = a1_in.hash.find (key);
        if (!a1_in.is_cached (hit)) {
            hit = a1_out.hash.find (key);
            if (a1_out.is_cached (hit)) {
                move_from_a1_out_to_hot_lru  (key, hit->second);
                return true;
            }
            add_to_a1_in (key, get_page);
            return false;
        }
        return true;
    }
    move_to_front_of_hot_lru (hit->second);
    return true;
}

//-----------------------------------------------------------------------------------------

template <typename T, typename KeyT>
T* two_q_cache_t<T, KeyT>::get_user_data (const size_t count_of_elem,
                                          std::istream & in_strm) {
    LOG_DEBUG ("Getting of data for cache\n");

    T* data = (T*) malloc (count_of_elem * sizeof (T));
    ASSERT (!is_nullptr (data));

    for (size_t i = 0; i < count_of_elem; i++) {
        in_strm >> data[i];
        if (!in_strm.good ()) {
            std::cout << "\nWrong input of values\n";
            print_error_message (CUR_POS_IN_PROG);
            exit (-1);
        };
    }
    return data;
}

//-----------------------------------------------------------------------------------------

template <typename T, typename KeyT>
int two_q_cache_t<T, KeyT>::move_from_a1_out_to_hot_lru  (KeyT key, list_iter elem) {
    LOG_DEBUG ("In a1_out\n");

    if (lru_hot.is_full ()) {
        lru_hot.hash.erase (lru_hot.cache.back().first);
        lru_hot.cache.pop_back ();
    }
    lru_hot.cache.splice (lru_hot.cache.begin (), a1_out.cache, elem);
    a1_out.hash.erase    (lru_hot.cache.front().first);
    lru_hot.hash.emplace (key, lru_hot.cache.begin ());
    return 0;
}

template <typename T, typename KeyT>
template <typename F>
int two_q_cache_t<T, KeyT>::add_to_a1_in (KeyT key, F get_page) {
    LOG_DEBUG ("Inserting in a1_in\n");

    if (a1_in.is_full ()) {
        move_from_a1_in_to_out ();
    }

    a1_in.cache.emplace_front (key, get_page (key));
    a1_in.hash.emplace        (key, a1_in.cache.begin ());

    return 0;
}

template <typename T, typename KeyT>
int two_q_cache_t<T, KeyT>::move_from_a1_in_to_out () {
    LOG_DEBUG ("Pop from a1_in to a1_out\n");

    if (a1_out.is_full ()) {
        a1_out.hash.erase (a1_out.cache.back().first);
        a1_out.cache.pop_back ();
    }

    auto elem = a1_in.cache.back ();
    a1_in.cache.pop_back ();
    a1_out.cache.push_front (elem);
    a1_in.hash.erase    (a1_out.cache.front().first);
    a1_out.hash.emplace (elem.second, a1_out.cache.begin ());

    return 0;
}

template <typename T, typename KeyT>
int two_q_cache_t<T, KeyT>::move_to_front_of_hot_lru (list_iter elem) {
    if (elem != lru_hot.cache.begin ()) {
        lru_hot.cache.splice (lru_hot.cache.begin (), lru_hot.cache, elem);
    }
    return 0;
}

//-----------------------------------------------------------------------------------------

template <typename T, typename KeyT>
int two_q_cache_t<T, KeyT>::dump_to_file (const char* name_of_log_file) {
    using std::endl;

    std::ofstream dump_file;
    dump_file.open (name_of_log_file);
    ASSERT (dump_file.is_open ());

    dump_to_strm (dump_file);
    dump_file.close ();
    return 0;
}

template <typename T, typename KeyT>
int two_q_cache_t<T, KeyT>::dump_to_strm (std::ofstream & os) {
    os << "lru_hot:\n";
    lru_hot.dump_to_strm (os);
    os << "a1_in:\n";
    a1_in.dump_to_strm (os);
    os << "a1_out:\n";
    a1_out.dump_to_strm (os);
    return 0;
}

template <typename T, typename KeyT>
int two_q_cache_t<T, KeyT>::test_data (const size_t count_of_elem, T* data) {
    LOG_DEBUG ("Testing of 2q cache\n");

    ASSERT (!is_nullptr (data));

    int hits = 0;
    for (size_t i = 0; i < count_of_elem; i++) {
        if (check_update (data[i], int_get_page)) hits++;
    }
    return hits;
}
}
#endif

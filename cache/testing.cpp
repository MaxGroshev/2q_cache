#include "./testing.hpp"

//-----------------------------------------------------------------------------------------

int cache_test () {
    size_t cache_size = 0;
    size_t count_of_elem = 0;

    std::ifstream input_file;
    input_file.open ("./tests/test1.txt");
	ASSERT (input_file.is_open ());

    get_init_data (&cache_size, &count_of_elem, input_file);
    cache::cache_t<int> lru {cache_size};
    int* data = lru.get_user_data (count_of_elem); //bad: only int*
    int hits = 0;
    //lru.dump_cache ();
    input_file.close ();

    LOG_DEBUG ("Num of hits: "); std::cout << hits << std::endl;
    free (data);
    return hits;
}

//-----------------------------------------------------------------------------------------

int get_init_data (size_t* cache_size, size_t* count_of_elem, std::istream & in_strm) {
    bool correct_input = false;
    while (!correct_input) {
        in_strm >> *cache_size >> *count_of_elem;
        if (!in_strm.good ()) {
            skip_wrong_input ();
            std::cout << "\nWrong input of init values\n";
            continue;
        }
        correct_input = true;
    }
    LOG_DEBUG (*cache_size, ' ', *count_of_elem, '\n');
    return 0;
}

// int get_test_data (int* hits, const size_t count_of_elem, cache::cache_t<int>& lru,
//                                                           std::istream & in_strm) {
//     int val  = 0;
//     for (size_t i = 0; i < count_of_elem; i++) {
//         in_strm >> val;
//         if (!in_strm.good ()) {
//             std::cout << "\nWrong input of values\n";
//             print_error_message (CUR_POS_IN_PROG);
//             return -1;
//         }
//         if (lru.cache_t::check_update (val, int_get_page)) (*hits)++;
//     }
//     return *hits; //pointer and ret_value at the same time
// }

int skip_wrong_input () {
    std::cin.clear ();
    while (std::cin.get () != '\n') {
        continue;
    }
    return 0;
}

#include "./testing.hpp"

//-----------------------------------------------------------------------------------------

int cache_test () {
    size_t cache_size = 0;
    size_t count_of_elem = 0;

    std::ifstream input_file;
    input_file.open ("./tests/test1.txt");
	ASSERT (input_file.is_open ());

    get_init_data (&cache_size, &count_of_elem, input_file);
    cache::two_q_cache_t<int> lru {cache_size};
    int hits = 0;
    get_test_data (&hits, count_of_elem, lru, input_file);
    std::cout << "Num of hits: " << hits << std::endl;

    input_file.close ();

    return hits;
}

//-----------------------------------------------------------------------------------------

int get_init_data (size_t* cache_size, size_t* count_of_elem, std::istream & is) {
    bool correct_input = false;
    while (!correct_input) {
        is >> *cache_size >> *count_of_elem;
        if (!is.good ()) {
            skip_wrong_input ();
            std::cout << "\nWrong input of init values\n";
            continue;
        }
        if (*cache_size < 5) {
            std::cout << "Impossible to use my cache with size less then 5\n";
            continue;
        }
        correct_input = true;
    }
    std::cout << *cache_size << ' ' << *count_of_elem << std::endl;
    return 0;
}

int get_test_data (int* hits, const size_t count_of_elem, cache::two_q_cache_t<int>& lru,
                                                          std::istream & is) {
    int val  = 0;
    for (size_t i = 0; i < count_of_elem; i++) {
        is >> val;
        if (!is.good ()) {
            std::cout << "\nWrong input of values\n";
            print_error_message (CUR_POS_IN_PROG);
            return -1;
        }
        if (lru.check_update (val, int_get_page)) (*hits)++;
    }
    return *hits; //pointer and ret_value at the same time
}

int skip_wrong_input () {
    std::cin.clear ();
    while (std::cin.get () != '\n') {
        continue;
    }
    return 0;
}

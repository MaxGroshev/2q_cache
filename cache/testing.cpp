#include "./testing.hpp"

//-----------------------------------------------------------------------------------------

int cache_test () {
    size_t cache_size = 0;
    size_t count_of_elem = 0;

    std::ifstream input_file;
    input_file.open ("./tests/test1.txt");
	ASSERT (input_file.is_open ());

    get_init_data (&cache_size, &count_of_elem, input_file);
    cache::perf_lru_t<int> lru {cache_size};
    auto user_data = lru.get_user_data (count_of_elem, input_file); //bad: only int*
    int hits = test_user_data (count_of_elem, lru, user_data);
    lru.dump_to_file ();
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

int test_user_data (const size_t count_of_elem, cache::perf_lru_t<int>& lru, T* data) {
    ASSERT (!is_nullptr (data));
    int hits = 0;
    for (size_t i = 0; i < count_of_elem; i++) {
        if (lru.perf_lru_t::check_update (data[i], int_get_page)) hits++;
    }
    return hits;
}

int skip_wrong_input () {
    std::cin.clear ();
    while (std::cin.get () != '\n') {
        continue;
    }
    return 0;
}

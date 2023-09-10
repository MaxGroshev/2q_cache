#include "./testing.hpp"

//-----------------------------------------------------------------------------------------

int cache_test () {
    size_t cache_size    = 0;
    size_t count_of_elem = 0;

    std::ifstream input_file;
    input_file.open ("./tests/test_data/test1.txt");
	ASSERT (input_file.is_open ());
    int hits = 0;

    while (!input_file.eof ()) {
        {
            get_init_data (&cache_size, &count_of_elem, input_file);
            cache::perf_lru_t<int> lru {cache_size};
            auto user_data = lru.get_user_data (count_of_elem, input_file);
            hits = lru.test_data (count_of_elem, user_data);
            if (is_correct_res (hits, input_file)) {
                show_test_data ()
            }
            free (user_data);
            LOG_DEBUG ("Num of hits: "); std::cout << hits << std::endl;
        }
    }

    input_file.close ();
    LOG_DEBUG ("Num of hits: "); std::cout << hits << std::endl;
    return 0;
}

//-----------------------------------------------------------------------------------------



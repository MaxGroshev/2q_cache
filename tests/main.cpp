#include "./testing.hpp"

//-----------------------------------------------------------------------------------------

int main () {
    test_perf_lru ();
    test_two_q    ();
    return 0;
}

int test_perf_lru () {
    std::ifstream input_file;
    input_file.open ("./tests/test_data/test_perf_lru.txt");
	ASSERT (input_file.is_open ());

    int    hits          = 0;
    size_t cache_size    = 0;
    size_t count_of_elem = 0;

    //std::cout << time () / 10000;
    std::cerr << "-----------------PERF_LRU_TESTS--------------------\n";
    for (int num_of_test = 1; num_of_test <= count_of_perf_lru_tests; num_of_test++) {
        {
            get_init_data (&cache_size, &count_of_elem, input_file);
            cache::perf_lru_t<int> lru {cache_size};

            auto user_data   = lru.get_user_data (count_of_elem, input_file);
            int  correct_res = get_correct_res (input_file);
            hits = lru.test_data (user_data);

            show_test_res (num_of_test, hits, correct_res);
        }
    }
    input_file.close ();
    return 0;
}

int test_two_q () { //repeating of the previos code, but impossible to change in this realisation
    std::ifstream input_file;
    input_file.open ("./tests/test_data/two_q_tests.txt");
	ASSERT (input_file.is_open ());

    int    hits = 0;
    size_t cache_size    = 0;
    size_t count_of_elem = 0;
    std::cerr << "--------------------2_Q_TESTS----------------------\n";
    for (int num_of_test = 1; num_of_test <= count_of_2_q_tests; num_of_test++) {
        {
            get_init_data (&cache_size, &count_of_elem, input_file);
            cache::two_q_cache_t<int> lru {cache_size};

            auto user_data   = lru.get_user_data (count_of_elem, input_file);
            int  correct_res = get_correct_res (input_file);
            hits = lru.test_data (user_data);

            show_test_res (num_of_test, hits, correct_res);
        }
    }
    input_file.close ();
    return 0;
}

//-----------------------------------------------------------------------------------------

int get_correct_res (std::istream & in_strm) {
    int correct_res = 0;
    in_strm >> correct_res;
    return correct_res;
}

int show_test_res (int num_of_test, int hits, int correct_res) {
    if (hits == correct_res) {
        fprintf (stderr, "|%s Test %d IS PASSED:%s", GREEN_C, num_of_test, RESET_C);
        fprintf (stderr, "%s [hits: %d; correct res: %d]%s\n", BLUE_C, hits, correct_res, RESET_C);
    }
    else {
        fprintf (stderr, "|%s Test %d IS FAILED:%s", RED_C, num_of_test, RESET_C);
        fprintf (stderr, "%s [hits: %d; correct res: %d]%s\n", BLUE_C, hits, correct_res, RESET_C);
    }
    return 0;
}

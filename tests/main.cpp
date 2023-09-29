#include "./testing.hpp"

//-----------------------------------------------------------------------------------------

int main () {
    test_perf_lru ();
    test_two_q    ();
    return 0;
}

int test_perf_lru () {

    using namespace time_control;

    std::ifstream input_file;
    input_file.open ("./tests/test_data/test_perf_lru.txt");
	ASSERT (input_file.is_open ());

    int    hits          = 0;
    size_t cache_size    = 0;
    size_t count_of_elem = 0;

    chrono_time_type start_time;
    chrono_time_type end_time;

    std::cout << "-----------------PERF_LRU_TESTS--------------------\n";
    for (int num_of_test = 1; num_of_test <= count_of_perf_lru_tests; num_of_test++) {
        start_time = chrono_cur_time ();

        get_init_data (&cache_size, &count_of_elem, input_file);
        cache::perf_lru_t<int> lru {cache_size};
        auto user_data   = lru.get_user_data (count_of_elem, input_file);
        int  correct_res = get_correct_res (input_file);
        hits = lru.test_data (user_data);

        end_time = chrono_cur_time ();
        show_test_res (num_of_test, hits, correct_res, (end_time - start_time) / 0.001ms);
    }

    input_file.close ();
    return 0;
}

int test_two_q () { //repeating of the previos code, but impossible to change in this realisation

    using namespace time_control;

    std::ifstream input_file;
    input_file.open ("./tests/test_data/two_q_tests.txt");
	ASSERT (input_file.is_open ());

    int    hits = 0;
    size_t cache_size    = 0;
    size_t count_of_elem = 0;

    chrono_time_type start_time;
    chrono_time_type end_time;

    std::cout << "--------------------2_Q_TESTS----------------------\n";
    for (int num_of_test = 1; num_of_test <= count_of_2_q_tests; num_of_test++) {
        start_time = chrono_cur_time ();

        get_init_data (&cache_size, &count_of_elem, input_file);
        cache::two_q_cache_t<int> lru {cache_size};
        auto user_data   = lru.get_user_data (count_of_elem, input_file);
        int  correct_res = get_correct_res (input_file);
        hits = lru.test_data (user_data);

        end_time = chrono_cur_time ();
        show_test_res (num_of_test, hits, correct_res, (end_time - start_time) / 0.001ms);
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

int show_test_res (int num_of_test, int hits, int correct_res, double test_time) {

    using namespace time_control;

    if (hits == correct_res) {
        printf ("|%s Test %d IS PASSED:%s", GREEN_C, num_of_test, RESET_C);
        printf ("%s [hits: %d; correct res: %d]%s\n", BLUE_C, hits, correct_res, RESET_C);
    }
    else {
        printf ("|%s Test %d IS FAILED:%s", RED_C, num_of_test, RESET_C);
        printf ("%s [hits: %d; correct res: %d]%s\n", BLUE_C, hits, correct_res, RESET_C);
    }
    printf ("|Time of running: %lg microseconds\n", test_time);

    return 0;
}

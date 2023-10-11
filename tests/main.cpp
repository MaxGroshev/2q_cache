#include "./testing.hpp"

//-----------------------------------------------------------------------------------------

int main () {
    //test_perf_lru ();
    //test_two_q    ();
    comp_perf_and_2q ();
    return 0;
}

int test_perf_lru () {

    using namespace time_control;

    std::ifstream input_file;
    input_file.open ("../tests/test_data/perf_lru_tests.txt");
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
    input_file.open ("../tests/test_data/two_q_tests.txt");
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

int comp_perf_and_2q () {

    using namespace time_control;

    std::ifstream input_file;
    input_file.open ("../tests/test_data/comp_tests.txt");
	ASSERT (input_file.is_open ());

    int    perf_lru_hits = 0;
    int    two_q_hits    = 0;
    size_t cache_size    = 0;
    size_t count_of_elem = 0;
    int    perf_lru_correct_res = 0;
    int    two_q_correct_res    = 0;

    std::chrono::high_resolution_clock::time_point start_time;
    std::chrono::high_resolution_clock::time_point end_time;

    std::cout << "-----------------COMPARISON_TESTS--------------------\n";
    for (int num_of_test = 1; num_of_test <= count_of_comp_test; num_of_test++) {
        get_init_data (&cache_size, &count_of_elem, input_file);

        cache::perf_lru_t<int> perf_lru {cache_size};
        cache::two_q_cache_t<int> lru_2q {cache_size};
        auto user_data = perf_lru.get_user_data (count_of_elem, input_file);

        start_time = chrono_high_res_time ();
        perf_lru_correct_res = get_correct_res (input_file);
        perf_lru_hits = perf_lru.test_data (user_data);
        end_time = chrono_high_res_time ();
        double perf_lru_time = (end_time - start_time) / 0.001ms;

        start_time = chrono_high_res_time ();
        two_q_correct_res = get_correct_res (input_file);
        two_q_hits = lru_2q.test_data (user_data);
        end_time = chrono_high_res_time ();
        double two_q_time = (end_time - start_time) / 0.001ms;

        show_comp_res (num_of_test, perf_lru_hits, two_q_hits,
                       perf_lru_correct_res, two_q_correct_res,
                       perf_lru_time, two_q_time, cache_size,
                       count_of_elem);
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

int show_comp_res   (int num_of_test, int perf_lru_hits, int two_q_hits,
                     int perf_lru_correct_res, int two_q_correct_res,
                     double perf_lru_time, double two_q_time, size_t cache_size,
                     size_t count_of_elem) {

    using namespace time_control;
    std::cout << "|----------------------------------------------------\n";
    if (perf_lru_hits == perf_lru_correct_res && two_q_hits == two_q_correct_res) {
        std::cout << "|" << GREEN_C << "Test num_of_test IS PASSED: " << RESET_C << "\n";
    }
    else {
        std::cout << "|" << RED_C << "Test " << num_of_test  << "IS FAILED:" << RESET_C << "\n";
    }
    std::cout << "|Perf lru running tine:" << perf_lru_time << " microseconds\n";
    std::cout << "|2q running time:      " << two_q_time << "microseconds\n";
    std::cout << "|Cache size   :" << cache_size << "\n";
    std::cout << "|Count_of_elem:" << count_of_elem << "\n";

    return 0;
}

int show_test_res (int num_of_test, int hits, int correct_res, double test_time) {

    using namespace time_control;

    if (hits == correct_res) {
        std::cout << "|" << GREEN_C << "Test " <<  num_of_test << " IS PASSED: " << RESET_C << "\n";
        std::cout << BLUE_C << "hits: " << hits << " correct res: " << RESET_C<<  "\n";
    }
    else {
        std::cout << "|" << RED_C << "Test " << num_of_test  << "IS FAILED:" << RESET_C << "\n";
        std::cout << BLUE_C << "hits: " << hits << " correct res: " << RESET_C<<  "\n";
    }
    std::cout << "|Time of running: " << test_time << "microseconds\n";

    return 0;
}

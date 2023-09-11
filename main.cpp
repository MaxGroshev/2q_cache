#include "./prog_for_testing_system.hpp"

int main (int argc, char* argv[]) {

    if (!strcmp (argv[1], "-tc") && argc == 2) {
        cache_test ();
    }
    else if (!strcmp (argv[1], "-2q") && argc == 2) {
        run_two_q_cache ();
    }
    else if (!strcmp (argv[1], "-pc") && argc == 2) {
        run_perf_cache ();
    }
    else {
        //cache_test ();
        run_two_q_cache ();
        //run_perf_cache ();
    }

    return 0;
}

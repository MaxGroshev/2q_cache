#include "./prog_for_testing_system.hpp"

int main (int argc, char* argv[]) {

    if (argc == 2 && !strcmp (argv[1], "-tc")) {
        cache_test ();
        return 0;
    }
    //run_two_q_cache ();
    run_perf_cache ();

    return 0;
}

#include "user_interface.hpp"

//-----------------------------------------------------------------------------------------

int get_init_data (size_t* cache_size, size_t* count_of_elem, std::istream & in_strm) {
    ASSERT (!in_strm.eof ());

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

int skip_wrong_input () {
    std::cin.clear ();
    while (std::cin.get () != '\n') {
        continue;
    }
    return 0;
}

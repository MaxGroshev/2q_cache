#include "./perf_lru_cache.hpp"

int main () {
    size_t cache_size    = 0;
    size_t count_of_elem = 0;

    get_init_data (&cache_size, &count_of_elem);
    cache::perf_lru_t<int> lru {cache_size};

    auto user_data = lru.get_user_data (count_of_elem);
    if (is_nullptr (user_data)) return -1;
    int hits       = lru.test_data     (count_of_elem, user_data);
    std::cout << hits << std::endl;
    free (user_data);

    return 0;
}

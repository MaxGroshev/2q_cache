#pragma once

#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <chrono>
#include <iomanip>

//-----------------------------------------------------------------------------------------

namespace time_control {

using namespace std::literals;
using chrono_time_type = std::chrono::time_point<std::chrono::steady_clock>;

inline auto chrono_cur_time () {
    return std::chrono::steady_clock::now ();
};

inline auto chrono_high_res_time () {
    return std::chrono::high_resolution_clock::now();
}

inline auto chrono_time_in_time_t () {
    const auto now = std::chrono::system_clock::now();

    std::time_t t_now  = std::chrono::system_clock::to_time_t(now);
    return std::put_time(std::localtime(&t_now), "%F %T.\n");
};

inline void chrono_show_time () {
    const auto now   = std::chrono::system_clock::now();
    const auto today = std::chrono::floor<std::chrono::days>(now);
    const auto hms   = std::chrono::hh_mm_ss{now - today};
    std::cout << "hms: "  << hms << '\n';
}

inline void chrono_show_date () {
    const auto now = std::chrono::system_clock::now();
    const auto ymd = std::chrono::year_month_day(
        std::chrono::floor<std::chrono::days>(now));
    std::cout << "ymd: "  << ymd << '\n';
}




}

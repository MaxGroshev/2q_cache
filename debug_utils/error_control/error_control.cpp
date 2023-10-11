#include "error_control.hpp"

//-----------------------------------------------------------------------------------------

int is_nullptr (const void* ptr) {
    if (ptr == nullptr) {
        return 1;
    }
    else return 0;
}

int print_error_message (const char* file_, const char* func_, int line_) {
    const char* error_mes = "\033[91mERROR Message\033[0m";
    std::cerr << "-------------------------" << error_mes <<"----------------------\n";
    std::cerr << "| filename:     " << BLUE_C   << file_ << RESET_C << std::endl;
    std::cerr << "| name_of_func: " << GREEN_C  << func_ << RESET_C << std::endl;
    std::cerr << "| num_of_line:  " << YELLOW_C << line_ << RESET_C << std::endl;
    std::cerr << "------------------------------------------------------------\n\n";

    return 0;
}

//-----------------------------------------------------------------------------------------

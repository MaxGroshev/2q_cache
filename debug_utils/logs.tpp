#ifndef LOGS_TPP
#define LOGS_TPP

//-----------------------------------------------------------------------------------------

template <class... Args>
int write_logs (Args... log_text) {
    (std::cerr << ... << log_text);
    return 0;
}

#endif

#ifndef ERROR_CONTR_H
#define ERROR_CONTR_H

//#define DEBUG

#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <format>
#include <chrono>
#include "ASSERT.h"
#include "./logs_define.h"

//-----------------------------------------------------------------------------------------

#define RED_C    "\033[91m"
#define GREEN_C  "\033[32m"
#define BLUE_C   "\033[36m"
#define YELLOW_C "\033[33m"
#define RESET_C  "\033[0m"

//-----------------------------------------------------------------------------------------

#define CUR_POS_IN_PROG __FILE__, __PRETTY_FUNCTION__, __LINE__

//-----------------------------------------------------------------------------------------

int   is_nullptr (const void* ptr);
char* timestamp  ();
int   print_error_message (const char* file_, const char* func_, int line_);
template <class... Args>
int   write_logs (Args... log_text);

#include "./logs.tpp"

#endif

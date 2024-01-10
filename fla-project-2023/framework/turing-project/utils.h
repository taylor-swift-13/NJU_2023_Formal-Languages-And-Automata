#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <string>
#include <fstream>
#include <cassert>
#include <algorithm>
#include <vector>
#include <unordered_set>
#include <list>
#include <iomanip> 
#include <assert.h>
#include <regex>
#include <filesystem>

using namespace std;

extern bool verbose; // 声明全局变量verbose
constexpr const char* help_tip ="usage: turing [-v|--verbose] [-h|--help] <tm> <input>";
constexpr const char* syntax_error_tip="syntax error";
constexpr const char* unaccepted_tip="(UNACCEPTED)" ;
constexpr const char* unaccepted_tip_verbose="UNACCEPTED" ;
constexpr const char* accepted_tip="(ACCEPTED)" ;
constexpr const char* accepted_tip_verbose="ACCEPTED" ;


constexpr const char* END="==================== END ====================";
constexpr const char* ERR="==================== ERR ====================";
constexpr const char* RUN="==================== RUN ====================";



enum ErrorCode {
    PRINT_HELP =0,
    ARG_ERROR = 1,
    FILE_READING_ERROR=2,
    CONSTRUCT_TURING_ERROR = 3,
    CONSTRUCT_DELTA_ERROR =4,
    INPUT_ERROR =5
};


#endif 


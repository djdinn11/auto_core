#pragma once
#include <windows.h>
#include <clock.h>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <thread>

namespace fs = std::filesystem;
namespace this_thread = std::this_thread;
using std::thread;
using std::wstring;
using std::cout;
using std::cerr;
using std::cin;
using std::format_error;
using std::invalid_argument;
using std::vformat;
using std::make_format_args;
using std::forward;
using std::format;
using std::endl;
using std::ofstream;
using std::ios;
using std::ifstream;

void logg(const string& message);
void loggnl(const string& message);
void log_init();
void log_end();

using logger_func = void(*)(const string&);

template<typename... Args>
void logger_template(const char* format_string, logger_func logger, Args&&... args) {
    try {
        if (format_string == nullptr) {
            throw invalid_argument("Format string is null");
        }
        auto formatted_string = vformat(format_string, make_format_args(forward<Args>(args)...));
        logger(formatted_string);
    }
    catch (const format_error& e) {
        string error = format("Format error: {}", e.what());
        logg(error);
    }
    catch (const invalid_argument& e) {
        string error = format("Invalid argument: {}", e.what());
        logg(error);
    }
}
template<typename... Args>
void logg(const char* format_string, Args&&... args) {
    logger_template(format_string, logg, forward<Args>(args)...);
}
template<typename... Args>
void loggnl(const char* format_string, Args&&... args) {
    logger_template(format_string, loggnl, forward<Args>(args)...);
}
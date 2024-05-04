#pragma once
#include <base.h>
#include <clock.h>

void logg(const string& message);
void loggnl(const string& message);
void update_main_log_file();

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

extern ofstream main_log_stream;
extern string main_log_name;
extern string logger_datestamp;
extern string log_directory;
extern bool send_logg_to_cout;
extern string session_start;
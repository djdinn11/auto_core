#pragma once
#include <logger.h>
#include <print.h>

void log_init();
void server_logg_and_logg(const string& msg);
void server_logg_and_print(const string& msg);

template<typename... Args>
void server_logg_and_logg(const char* format_string, Args&&... args) {
    string formatted_message = vformat(format_string, make_format_args(forward<Args>(args)...));
    server_logg_and_logg(formatted_message);
}
template<typename... Args>
void server_logg_and_print(const char* format_string, Args&&... args) {
    string formatted_message = vformat(format_string, make_format_args(forward<Args>(args)...));
    server_logg_and_print(formatted_message);
}
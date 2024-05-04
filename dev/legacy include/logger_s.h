#pragma once
#include <visual.h>

void log_server_end(const string& msg);
template<typename... Args>
void log_server_end(const char* format_string, Args&&... args) {
    string formatted_message = vformat(format_string, make_format_args(forward<Args>(args)...));
    log_server_end(formatted_message);
}
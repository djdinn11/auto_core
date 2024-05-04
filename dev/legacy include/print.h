#pragma once
#include <base.h>
#include <logger.h>

void print(const string& s);
void printnl(const string& s);
void print_to_screen(const string& msg);

using print_func = void(*)(const string&);

template<typename... Args>
void print_template(const char* format_string, print_func println, Args&&... args) {
    try {
        if (format_string == nullptr) {
            throw invalid_argument("Format string is null");
        }
        auto formatted_string = vformat(format_string, make_format_args(forward<Args>(args)...));
        println(formatted_string);
    }
    catch (const format_error& e) {
        string error = format("Format error: {}", e.what());
        print(error);
    }
    catch (const invalid_argument& e) {
        string error = format("Invalid argument: {}", e.what());
        print(error);
    }
}
template<typename... Args>
void print(const char* format_string, Args&&... args) {
    print_template(format_string, print, forward<Args>(args)...);
}
template<typename... Args>
void printnl(const char* format_string, Args&&... args) {
    print_template(format_string, printnl, forward<Args>(args)...);
}
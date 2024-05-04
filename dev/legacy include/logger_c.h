/*!
\file logger_c.h
\brief Offers specialized logging capabilities focused on individual components like music player activity.

This class extension to the generic logger module allows for focused logging, beneficial for debugging and monitoring specific aspects of Auto Core's operation.
*/
#pragma once
#include <logger.h>
#include <print.h>

class Logger {
public:
    Logger(const string& log_name);
    ~Logger();
    string name;
    string directory;
    string session_started;
    void logg(const string& message);
    void loggnl(const string& message);
    void logg_and_print(const string& message);
    void logg_and_logg(const string& message);
    void loggnl_and_printnl(const string& message);
    void loggnl_and_loggnl(const string& message);
    template<typename... Args>
    void logg(const char* format_string, Args&&... args) {
        string formatted_message = vformat(format_string, make_format_args(forward<Args>(args)...));
        logg(formatted_message);
    };
    template<typename... Args>
    void loggnl(const char* format_string, Args&&... args) {
        string formatted_message = vformat(format_string, make_format_args(forward<Args>(args)...));
        loggnl(formatted_message);
    };
    template<typename... Args>
    void logg_and_print(const char* format_string, Args&&... args) {
        string formatted_message = vformat(format_string, make_format_args(forward<Args>(args)...));
        logg(formatted_message);
        print(formatted_message);
    };
    template<typename... Args>
    void loggnl_and_printnl(const char* format_string, Args&&... args) {
        string formatted_message = vformat(format_string, make_format_args(forward<Args>(args)...));
        loggnl(formatted_message);
        println(formatted_message);
    };
    template<typename... Args>
    void logg_and_logg(const char* format_string, Args&&... args) {
        string formatted_message = vformat(format_string, make_format_args(forward<Args>(args)...));
        logg(formatted_message);
        ::logg(formatted_message);
    };
    template<typename... Args>
    void loggnl_and_loggnl(const char* format_string, Args&&... args) {
        string formatted_message = vformat(format_string, make_format_args(forward<Args>(args)...));
        loggnl(formatted_message);
        ::loggnl(formatted_message);
    };
    void update_log_file();
private:
    ofstream log_stream;
    void open_log_file();
    void close_log_file();
};
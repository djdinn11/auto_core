#include <logger_c.h>

Logger::Logger(const string& log_name) {
    name = log_name;
    directory = log_directory + name + "\\";
    open_log_file();
}
Logger::~Logger() {
    close_log_file();
}
void Logger::logg(const string& message) {
    if (log_stream.is_open()) {
        log_stream << message << endl;
    }
}
void Logger::loggnl(const string& message) {
    if (log_stream.is_open()) {
        log_stream << message;
    }
}
void Logger::logg_and_logg(const string& message) {
    if (log_stream.is_open()) {
        log_stream << message << endl;
    }
    ::logg(message);
}
void Logger::loggnl_and_loggnl(const string& message) {
    if (log_stream.is_open()) {
        log_stream << message;
    }
    ::loggnl(message);
}
void Logger::logg_and_print(const string& message) {
    if (log_stream.is_open()) {
        log_stream << message << endl;
    }
    print(message);
}
void Logger::loggnl_and_printnl(const string& message) {
    if (log_stream.is_open()) {
        log_stream << message;
    }
    printnl(message);
}
void Logger::update_log_file() {
    string session_status = "";
    if (log_stream.is_open()) {
        session_status = "---\n";
        log_stream << session_status;
        log_stream.close();
    }
    session_status += session_started;
    string datestamp = get_datestamp();
    string filename = name + "_" + datestamp + ".log";
    string logger_path = directory + filename;
    log_stream.open(logger_path, ios::app);
    log_stream << session_status << endl;
}
void Logger::open_log_file() {
    fs::create_directories(directory);
    session_started = "Session started at " + get_datetime_stamp_for_logger();
    update_log_file();
}
void Logger::close_log_file() {
    if (log_stream.is_open()) {
        string session_ended = "Session ended at " + get_datetime_stamp_for_logger();
        log_stream << session_ended << "\n***\n";
        log_stream.close();
    }
}
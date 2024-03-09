#include <logger.h>
#include <locale>
#include <wake.h>
#include <logger_c.h>

ofstream log_stream;
string logger_name;
string logger_datestamp;
string session_start;
string log_directory = R"(.\log\)";
bool send_cerr_to_cout = false;

void logg(const string& message) {
    cerr << message << endl;
    if (send_cerr_to_cout) {
        cout << message << endl;
    }
}
void loggnl(const string& message) {
    cerr << message;
    if (send_cerr_to_cout) {
        cout << message;
    }
}
void update_log_file() {
    if (log_stream.is_open()) {
        log_stream.close();
    }
    logger_datestamp = get_datestamp();
    logger_name = "log_" + logger_datestamp + ".txt";
    string logger_path = log_directory + logger_name;
    log_stream.open(logger_path, ios::app);
    cerr.rdbuf(log_stream.rdbuf());
}
void log_thread() {
    int log_thread_sleep_time = 60;
    fs::create_directories(log_directory);
    string current_datestamp = get_datestamp();
    while (true) {
        int seconds_to_sleep = log_thread_sleep_time - get_current_seconds();
        log_last_wake();
        logg("log thread sleeping for {} seconds at {}", seconds_to_sleep, get_timestamp_with_seconds());
        this_thread::sleep_for(chrono::seconds(seconds_to_sleep));
        current_datestamp = get_datestamp();
        if (current_datestamp != logger_datestamp) {
            logg("---");
            update_log_file();
            update_log_files();
            logg("---");
            logg(session_start);
        }
    }
}
void log_init() {
    session_start = "Session started " + get_datetime_stamp_for_logger();
    update_log_file();
    logg(session_start);
    thread t(log_thread);
    t.detach();
}
void log_end() {
    logg("Session ended {}", get_datetime_stamp_for_logger());
    logg("***");
}

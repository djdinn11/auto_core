#include <logger_t.h>
#include <sp.h>
#include <itunes.h>

void update_log_components() {
    update_sp_logger();
    update_iTunes_logger();
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
            update_main_log_file();
            update_log_components();
            logg("---");
            logg(session_start);
        }
    }
}
void log_init() {
    session_start = "Session started " + get_datetime_stamp_for_logger();
    update_main_log_file();
    logg(session_start);
    thread t(log_thread);
    t.detach();
}
void log_end() {
    logg("Session ended {}", get_datetime_stamp_for_logger());
    logg("***");
}
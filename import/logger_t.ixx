/*!
\file logger_t.ixx
\brief This module creates a logger thread.
*/
export module logger_t;
import visual;
import sp;
import itunes;
import logger_c;
import logger_w;
import logger_x;
import <Windows.h>;

Logger logger_logger("logger");

export void log_thread() {
    int log_thread_sleep_time = 60;
    string current_datestamp = get_datestamp();
    logger_logger.logg_and_logg("logger thread started");
    while (true) {
        int seconds_to_sleep = log_thread_sleep_time - get_current_seconds();
        log_last_wake();
        logger_logger.logg("log thread sleeping for {} seconds at {}", seconds_to_sleep, get_timestamp_with_seconds());
        this_thread::sleep_for(chrono::seconds(seconds_to_sleep));
        current_datestamp = get_datestamp();
        if (current_datestamp != logger_datestamp) {
            logg("---");
            update_main_log_file();
            logger_logger.update_log_file();
            update_log_components();
            logg("---");
            logg(session_start);
        }
    }
}
module logger;
import logger_t;

void log_init() {
    session_start = "Session started " + get_datetime_stamp_for_logger();
    fs::create_directories(log_directory);
    update_main_log_file();
    logg(session_start);
    thread t(log_thread);
    t.detach();
}

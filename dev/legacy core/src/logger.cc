#include <logger.h>

ofstream main_log_stream;
string main_log_name;
string logger_datestamp;
string log_directory = R"(.\log\)";
bool send_logg_to_cout = false;
string session_start;

void logg(const string& message) {
    if (main_log_stream.is_open()) {
        main_log_stream << message << endl;
    }
    if (send_logg_to_cout) {
        cout << message << endl;
    }
}
void loggnl(const string& message) {
    if (main_log_stream.is_open()) {
        main_log_stream << message;
    }
    if (send_logg_to_cout) {
        cout << message;
    }
}
void update_main_log_file() {
    if (main_log_stream.is_open()) {
        main_log_stream.close();
    }
    logger_datestamp = get_datestamp();
    main_log_name = "log_" + logger_datestamp + ".log";
    string logger_path = log_directory + main_log_name;
    main_log_stream.open(logger_path, ios::app);
}
#include <logger_s.h>

ofstream server_log_stream;
string server_log_name = "server.log";
string server_log_directory = R"(.\log\server\)";
string server_log_path = server_log_directory + server_log_name;

void server_logg_and_logg(const string& msg) {
    logg(msg);
    server_log_stream.open(server_log_path, ios::app);
    server_log_stream << msg << " at " << get_datetime_stamp_with_seconds() << endl;
    server_log_stream.close();
}
void server_logg_and_print(const string& msg) {
    server_log_stream.open(server_log_path, ios::app);
    server_log_stream << msg << endl;
    server_log_stream.close();
    print(msg);
}
void log_init() {
    fs::create_directories(server_log_directory);
    update_main_log_file();
}
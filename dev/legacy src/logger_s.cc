#include <logger_s.h>

void log_server_end(const string& msg) {
    ofstream server_log_stream;
    string server_log_name = "server.log";
    string server_log_directory = R"(.\log\server\)";
    string server_log_path = server_log_directory + server_log_name;
    server_log_stream.open(server_log_path, ios::app);
    server_log_stream << msg << " at " << get_datetime_stamp_with_seconds() << endl;
    server_log_stream.close();
    logg(msg);
}
/*!
\file logger_s.ixx
\brief This is a specialized logger for monitoring the server.
\hardlink
*/
export module logger_s;
import base;
import clock;
import logger;
import print;

ofstream server_log_stream;
string server_log_name = "server.log";
export string server_log_directory = R"(.\log\server\)";
export string server_log_path = server_log_directory + server_log_name;
export string port_number_str;

export {
    void log_server_end(const string& msg);
    void server_log_init();
    template<typename... Args> void log_server_end(const char* format_string, Args&&... args);
    void server_logg_and_logg(const string& msg);
    void server_logg_and_print(const string& msg);
    template<typename... Args> void server_logg_and_logg(const char* format_string, Args&&... args);
    template<typename... Args> void server_logg_and_print(const char* format_string, Args&&... args);
}

void set_port_number() {
    ifstream server_file(R"(.\config\server.ini)");
    string line;
    getline(server_file, line);
    auto open_bracket = line.find('[');
    auto close_bracket = line.find(']');
    port_number_str = line.substr(open_bracket + 1, close_bracket - open_bracket - 1);
}

void server_log_init() {
    fs::create_directories(server_log_directory);
    update_main_log_file();
    send_logg_to_cout = get_send_to_cout();
    set_port_number();
}
template<typename... Args>
void log_server_end(const char* format_string, Args&&... args) {
    string formatted_message = vformat(format_string, make_format_args(forward<Args>(args)...));
    log_server_end(formatted_message);
}

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

template<typename... Args>
void server_logg_and_logg(const char* format_string, Args&&... args) {
    string formatted_message = vformat(format_string, make_format_args(forward<Args>(args)...));
    server_logg_and_logg(formatted_message);
}
template<typename... Args>
void server_logg_and_print(const char* format_string, Args&&... args) {
    string formatted_message = vformat(format_string, make_format_args(forward<Args>(args)...));
    server_logg_and_print(formatted_message);
}
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
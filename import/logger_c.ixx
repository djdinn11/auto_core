/*!
\file logger_c.ixx
\brief Offers specialized logging capabilities focused on individual components like music player activity.
\hardlink
*/
export module logger_c;
import visual;
import <Windows.h>;

export class Logger {
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
    ofstream log_stream;
    void open_log_file();
    void close_log_file();
};
Logger::Logger(const string& log_name) {
    name = log_name;
    directory = log_directory + name + "\\";
    send_logg_to_cout = get_send_to_cout();
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
        log_stream.flush();
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
        log_stream.flush();
        log_stream.close();
    }
}
/*!
\file logger.ixx
\brief Defines a custom logger featuring logg() and loggnl().
\hardlink
*/
export module logger;
import base;
import clock;
import <Windows.h>;

export string session_start;
export ofstream main_log_stream;
export string main_log_name;
export string logger_datestamp;
export string log_directory = R"(.\log\)";
export bool send_logg_to_cout;

export void log_init();

export {
    void log_end();
    bool get_send_to_cout();
    void logg(const string& message);
    void loggnl(const string& message);
    void update_main_log_file();
    void close_main_log_file();
    template<typename... Args> void logg(const char* format_string, Args&&... args);
    template<typename... Args> void loggnl(const char* format_string, Args&&... args);
}

using logger_func = void(*)(const string&);

template<typename... Args>
void logger_template(const char* format_string, logger_func logger, Args&&... args) {
    try {
        if (format_string == nullptr) {
            throw invalid_argument("Format string is null");
        }
        auto formatted_string = vformat(format_string, make_format_args(forward<Args>(args)...));
        logger(formatted_string);
    }
    catch (const format_error& e) {
        string error = format("Format error: {}", e.what());
        logg(error);
    }
    catch (const invalid_argument& e) {
        string error = format("Invalid argument: {}", e.what());
        logg(error);
    }
}
template<typename... Args>
void logg(const char* format_string, Args&&... args) {
    logger_template(format_string, logg, forward<Args>(args)...);
}
template<typename... Args>
void loggnl(const char* format_string, Args&&... args) {
    logger_template(format_string, loggnl, forward<Args>(args)...);
}

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
    close_main_log_file();
    logger_datestamp = get_datestamp();
    main_log_name = "log_" + logger_datestamp + ".log";
    string logger_path = log_directory + main_log_name;
    main_log_stream.open(logger_path, ios::app);
}
void close_main_log_file() {
    if (main_log_stream.is_open()) {
        main_log_stream.flush();
        main_log_stream.close();
    }
}
bool get_send_to_cout() {
    ifstream logger_file(R"(.\config\logger.ini)");
    string line;
    getline(logger_file, line);
    auto open_bracket = line.find('[');
    auto close_bracket = line.find(']');
    string value = line.substr(open_bracket + 1, close_bracket - open_bracket - 1);
    return (value == "true");
}
void log_end() {
    logg("Session ended {}", get_datetime_stamp_for_logger());
    logg("***");
    close_main_log_file();
}
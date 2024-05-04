#include <logger_w.h>

void log_last_wake() {
    string wake_directory = R"(.\log\wake\)";
    fs::create_directories(wake_directory);
    static string previous_last_wake_file = wake_directory + "previous_wake.log";
    static string current_last_wake_file = wake_directory + "current_wake.log";
    static string last_wake_log_file = wake_directory + "wake_log.log";
    ofstream current_last_wake_clear(current_last_wake_file);
    if (current_last_wake_clear.is_open()) {
        current_last_wake_clear << "";
        current_last_wake_clear.close();
    }
    static string retrieve_last_wake_command = format("powercfg /lastwake >> {}", current_last_wake_file);
    system(retrieve_last_wake_command.c_str());
    ifstream previous_last_wake_stream(previous_last_wake_file);
    string line;
    oss previous_last_wake_oss;
    while (getline(previous_last_wake_stream, line)) {
        previous_last_wake_oss << line << '\n';
    }
    previous_last_wake_stream.close();
    ifstream current_last_wake_stream(current_last_wake_file);
    oss current_last_wake_oss;
    while (getline(current_last_wake_stream, line)) {
        current_last_wake_oss << line << '\n';
    }
    current_last_wake_stream.close();
    string current_last_wake_str = current_last_wake_oss.str();
    string current_last_wake_output;
    if (current_last_wake_str != previous_last_wake_oss.str()) {
        current_last_wake_output = get_datetime_stamp_with_seconds() + '\n' + current_last_wake_str;
        ofstream last_wake_log_stream(last_wake_log_file, ios::app);
        if (last_wake_log_stream.is_open()) {
            last_wake_log_stream << current_last_wake_output;
            last_wake_log_stream.close();
        }
        ofstream previous_last_wake_update(previous_last_wake_file);
        if (previous_last_wake_update.is_open()) {
            previous_last_wake_update << current_last_wake_str;
            previous_last_wake_update.close();
        }
        loggnl("wake state change detected at {}", current_last_wake_output);
    }
}
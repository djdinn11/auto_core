#include <config.h>

Config config;

Config::Config() {
    current_directory = LR"(C:\DJ\My Folder\Auto Core)";
    SetCurrentDirectory(current_directory.c_str());
    wstring program_title = L"Auto Core";
    SetConsoleTitle(program_title.c_str());
    ifstream config_file(R"(.\config\config.ini)");
    string line;
    getline(config_file, line);
    size_t open_bracket = line.find("[");
    size_t close_bracket = line.find("]");
    string value = line.substr(open_bracket + 1, close_bracket - open_bracket - 1);
    end_of_day = stoi(value);
    getline(config_file, line);
    open_bracket = line.find("[");
    close_bracket = line.find("]");
    value = line.substr(open_bracket + 1, close_bracket - open_bracket - 1);
    if (value == "false") {
        runtime_enabled = false;
    }
    else if (value == "true") {
        runtime_enabled = true;
    }
    getline(config_file, line);
    open_bracket = line.find("[");
    close_bracket = line.find("]");
    value = line.substr(open_bracket + 1, close_bracket - open_bracket - 1);
    if (value == "false") {
        send_logg_to_cout = false;
    }
    else if (value == "true") {
        send_logg_to_cout = true;
    }
    config_file.close();
}
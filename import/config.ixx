/*!
 * \file config.ixx
 * \brief Provides a module to handle program configuration.
 */
export module config;
import base;
import <Windows.h>;

export class Config {
public:
    Config(); 
    wstring current_directory;
    wstring program_title;
    bool runtime_enabled;
    bool start_local_server;
};

Config::Config()
    : current_directory(LR"(C:\DJ\My Folder\Auto Core)"),
    program_title(L"Auto Core"),
    runtime_enabled(false),
    start_local_server(false)
{
    SetCurrentDirectory(current_directory.c_str());
    SetConsoleTitle(program_title.c_str());
    ifstream config_file(R"(.\config\config.ini)");
    if (!config_file) {
        return; 
    }
    string line;
    while (getline(config_file, line)) {
        auto first_space = line.find(' ');
        auto open_bracket = line.find('[');
        auto close_bracket = line.find(']');
        if (open_bracket != string::npos && close_bracket != string::npos) {
            string key = line.substr(0, first_space);
            string value = line.substr(open_bracket + 1, close_bracket - open_bracket - 1);
            if (key == "runtime_enabled") {
                runtime_enabled = (value == "true");
            }
            else if (key == "start_local_server") {
                start_local_server = (value == "true");
            }
        }
    }
}

export Config config;
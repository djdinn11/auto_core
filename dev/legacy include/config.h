#pragma once
#include <visual.h>

class Config {
public:
    Config();
    wstring current_directory;
    wstring program_title;
    int end_of_day;
    bool runtime_enabled;
    bool send_logg_to_cout;
};

extern Config config;

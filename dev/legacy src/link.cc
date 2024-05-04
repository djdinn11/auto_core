#include <link.h>
#include <clipboard.h>
#include <main.h>
#include <config.h>

bool dash_selected = false;

string format_dash_prompt(const string& str) {
    vector<string> names;
    ss s(str);
    string name;
    char dash = '-';
    while (getline(s, name, dash)) {
        names.push_back(name);
    }
    oss formatted_names;
    for (size_t i = 0; i < names.size(); i++) {
        formatted_names << names[i];
        if ((i + 1) == 35) {
            formatted_names << ", ";
        }
        else if (((i + 1) % 5 == 0) && (i + 1 != names.size())) {
            formatted_names << "\n";
        }
        else if (i + 1 != names.size()) {
            formatted_names << ", ";
        }
    }
    loggnl("format_dash_prompt: ");
    auto formatted_names_str = formatted_names.str();
    print(formatted_names_str);
    return formatted_names_str;
}
string get_gpt_model(const string& str) {
    size_t first_space = str.find(' ');
    size_t end_comma = str.find(',');
    return str.substr(first_space + 1, end_comma - first_space - 1);
}
string get_gpt_message() {
    logg("get_gpt_message()");
    const string gpt_path_prompts = R"(.\link\gpt_prompts.rc)";
    ifstream file(gpt_path_prompts);
    if (!file.is_open()) {
        print("error reading file");
        return "";
    }
    vector<string> gpt_prompts;
    vector<string> gpt_models;
    string prompt;
    string model;
    while (getline(file, prompt)) {
        if (prompt.find("GPT") != string::npos) {
            model = get_gpt_model(prompt);
            gpt_models.push_back(model);
            gpt_prompts.push_back(prompt);
        }
        else if (prompt.find("*") != string::npos && prompt[0] == '*') {
            gpt_models.push_back("*");
            prompt = prompt.substr(1);
            gpt_prompts.push_back(prompt);
        }
        else if (prompt.find("-") != string::npos) {
            gpt_models.push_back("-");
            prompt = format_dash_prompt(prompt);
            gpt_prompts.push_back(prompt);
        }
        else {
            gpt_models.push_back(prompt);
            gpt_prompts.push_back(prompt);
        }
    }
    file.close();
    oss gpt_model_choice_prompt;
    gpt_model_choice_prompt << "Enter the number:\n";
    for (size_t i = 0; i < gpt_prompts.size(); ++i) {
        model = gpt_models[i];
        gpt_model_choice_prompt << format("{} for {}\n", i + 1, model);
    }
    gpt_model_choice_prompt << "> ";
    printnl(gpt_model_choice_prompt.str());
    string selection_str;
    int selection;
    while (true) {
        getline(cin, selection_str);
        logg("{}", selection_str);
        try {
            if (selection_str.empty()) {
                return gpt_prompts[gpt_prompts.size() - 1];
            }
            selection = stoi(selection_str);
            if (selection == 0 || selection > gpt_prompts.size()) {
                printnl("Incorrect input\nEnter again: ");
            }
            else if (selection == 5) {
                dash_selected = true;
                return gpt_prompts[selection - 1];
            }
            else {
                return gpt_prompts[selection - 1];
            }
        }
        catch (const invalid_argument&) {
            printnl("Incorrect input\nEnter again: ");
        }
    }
    logg("end of get_gpt_message()");
}
void threaded_print_gpt_message() {
    dash_selected = false;
    HWND current_window_handle = GetForegroundWindow();
    set_focus_auto_core();
    string gpt_message = get_gpt_message();
    print(gpt_message);
    wss ws;
    ws << gpt_message.c_str();
    if (dash_selected) {
        ws << "\n\n";
    }
    set_clipboard_text(ws.str());
    SetForegroundWindow(current_window_handle);
    paste_from_clipboard();
}

/** \runtime */
void print_gpt_message() {
    logg("print_gpt_message()");
    thread t([=]() {run_with_exception_handling(threaded_print_gpt_message);});
    t.detach();
}
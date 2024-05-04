/*!
\file print.ixx
\brief This module provides functionality for sending output to the console.
\hardlink
*/
export module print;
import base;
import logger;
import clipboard;
import <Windows.h>;

export {
    void print(const string& s);
    void printnl(const string& s);
    void print_to_screen(const string& msg);
    template<typename... Args> void print(const char* format_string, Args&&... args);
    template<typename... Args> void printnl(const char* format_string, Args&&... args);
}

using print_func = void(*)(const string&);

template<typename... Args>
void print_template(const char* format_string, print_func println, Args&&... args) {
    try {
        if (format_string == nullptr) {
            throw invalid_argument("Format string is null");
        }
        auto formatted_string = vformat(format_string, make_format_args(forward<Args>(args)...));
        println(formatted_string);
    }
    catch (const format_error& e) {
        string error = format("Format error: {}", e.what());
        print(error);
    }
    catch (const invalid_argument& e) {
        string error = format("Invalid argument: {}", e.what());
        print(error);
    }
}
template<typename... Args>
void print(const char* format_string, Args&&... args) {
    print_template(format_string, print, forward<Args>(args)...);
}
template<typename... Args>
void printnl(const char* format_string, Args&&... args) {
    print_template(format_string, printnl, forward<Args>(args)...);
}

void print(const string& s) {
    cout << s << endl;
    logg(s);
}
void printnl(const string& s) {
    cout << s;
    loggnl(s);
}
void print_to_screen(const string& msg) {
    static bool preserve_clipboard = get_preserve_clipboard_value();
    if (!preserve_clipboard) {
        print(msg);
        wss ws;
        ws << msg.c_str() << L"\n\n";
        set_clipboard_text(ws.str());
        paste_from_clipboard();
    }
    else if (preserve_clipboard) {
        wstring clipboard_text = get_clipboard_text();
        print(msg);
        wss ws;
        ws << msg.c_str() << L"\n\n";
        set_clipboard_text(ws.str());
        paste_from_clipboard();
        Sleep(50);
        set_clipboard_text(clipboard_text);
    }
}
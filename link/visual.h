#pragma once
#include <windows.h>
#include <conio.h>
#include <array>
#include <exception>
#include <functional>
#include <iomanip>
#include <istream>
#include <ostream>
#include <sstream>
#include <thread>
#include <unordered_map>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <logger.h>

using print_func = void(*)(const string&);

void print(const string& s);
void printnl(const string& s);

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

namespace chrono = std::chrono;
namespace this_thread = std::this_thread;
using oss = std::ostringstream;
using iss = std::istringstream;
using wss = std::wostringstream;
using ss = std::stringstream;
using std::mutex;
using std::condition_variable;
using std::unique_lock;
using std::wstring;
using std::function;
using std::unordered_map;
using std::thread;
using std::vector;
using std::array;
using std::exception;
using std::wcout;
using std::setw;
using std::setfill;

string wstr_to_str(const wstring& wstr);
wstring str_to_wstr(const string& str);
wstring utf8_to_utf16(const string& utf8);
string base64_encode(const string& in);
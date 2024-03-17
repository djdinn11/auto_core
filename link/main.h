#pragma once
#include <visual.h>

template<typename Func>
void run_with_exception_handling(Func func) {
    try {
        func();
    }
    catch (const exception& e) {
        print("caught exception: {}", e.what());
    }
    catch (...) {
        print("crash in thread function");
    }
}

extern bool primary;
extern HWND program_window;
extern HHOOK keyboard_hook;
extern DWORD main_thread_id;
extern bool program_closing;

void close_program();
void activate_function_key();
void deactivate_function_key();
void print_to_screen(string msg);
void print_timestamp();
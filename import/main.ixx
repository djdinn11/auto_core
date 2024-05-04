/*!
\file main.ixx
\brief Core support for cross-module communication and integration within the Auto Core framework.
*/
export module main;
import visual;
import <Windows.h>;
import <conio.h>;
import sp;
import itunes;
import logger_t;
import server;
import taskbar;

export bool primary = true;
export HWND close_window;
export HWND program_window;
export HHOOK keyboard_hook;
export DWORD main_thread_id;
export bool program_closing = false;

export {
    void close_program();
    void activate_function_key();
    void deactivate_function_key();
    void print_timestamp();
    void set_focus_auto_core();
}

/** \runtime */
void close_program() {
    program_closing = true;
    stop_server();
    send_iTunes_end_signal();
    send_sp_end_signal();
    if (keyboard_hook != NULL) {
        UnhookWindowsHookEx(keyboard_hook);
    }
    PostThreadMessage(main_thread_id, WM_QUIT, 0, 0);
}

/** \runtime */
void activate_function_key() {
    primary = false;
    print("Function key activated");
}

/** \runtime */
void deactivate_function_key() {
    primary = true;
    print("Function key deactivated");
}

/** \runtime */
void print_timestamp() {
    print_to_screen(get_timestamp());
}

void clear_input_buffer() {
    while (_kbhit()) {
        int getch = _getch();
    }
    cin.clear();
}
void set_focus_auto_core() {
    logg("set_focus_auto_core()");
    clear_input_buffer();
    HWND current_window_hwnd = GetForegroundWindow();
    if (current_window_hwnd != program_window) {
        taskbar.activate_auto_core();
    }
}
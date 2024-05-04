#include <main.h>
#include <numkey.h>
#include <clipboard.h>
#include <server.h>
#include <itunes.h>
#include <sp.h>
#include <clock.h>
#include <taskbar.h>
#include <itunes.h>
#include <logger_t.h>

bool program_closing = false;

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
    log_end();
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
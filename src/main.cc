#include <main.h>
#include <numkey.h>
#include <clipboard.h>
#include <clock.h>
#include <itunes.h>

bool program_closing = false;

void close_program() {
    ac_iTunes.finalize_com();
    program_closing = true;
    if (keyboard_hook != NULL) {
        UnhookWindowsHookEx(keyboard_hook);
    }
    PostThreadMessage(main_thread_id, WM_QUIT, 0, 0);
    logg("end of close_program()");
}
BOOL WINAPI x_close_event(DWORD dwType) {
    if (dwType == CTRL_CLOSE_EVENT && !program_closing) {
        logg("x_close_event() called");
        primary = false;
        PostThreadMessage(main_thread_id, ac_numkey_1, 0, 0);
        Sleep(250);
        logg("end of x_close_event() - CTRL_CLOSE_EVENT");
        return TRUE;
    }
    return FALSE;
}
void activate_function_key() {
    primary = false;
    print("Function key activated");
}
void deactivate_function_key() {
    primary = true;
    print("Function key deactivated");
}
void print_to_screen(string msg) {
    print(msg);
    wss ws;
    ws << msg.c_str() << L"\n\n";
    set_clipboard_text(ws.str());
    paste_from_clipboard();
}
void print_timestamp() {
    print_to_screen(get_timestamp());
}
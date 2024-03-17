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
    log_end();
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
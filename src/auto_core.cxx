import auto_core;
import runtime;
import dash;
import <Windows.h>;
import config;
import end;

void auto_init() {
    SetConsoleOutputCP(CP_UTF8);
    SetUnhandledExceptionFilter(unhandled_exception_handler);
    SetConsoleCtrlHandler(console_close_event, TRUE);
}
void core_init() {
    keyboard_hook = SetWindowsHookEx(WH_KEYBOARD_LL, send_numpad_event, NULL, 0);
    main_thread_id = GetCurrentThreadId();
    program_window = GetConsoleWindow();
    close_window = close_window_hidden_init();
    if (config.start_local_server) {
        start_server();
    }
}
void create_pipe_servers() {
    ac_itunes_pipe = create_pipe_server(L"ac_itunes_pipe");
    ac_sp_pipe = create_pipe_server(L"ac_sp_pipe");
}
void start_components() {
    start_iTunes_component();
    start_sp_component();
}

int main() {
    auto_init();
    core_init();
    log_init();
    crash_check();
    create_pipe_servers();
    start_components();
    config.runtime_enabled ? parse_and_set_action_map() : set_action_map();
    set_taskbar_positions();
    print("Program ready");
    print(get_day_of_week());
    print_task_list();
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0) > 0) {
        try {process_numpad_event(msg);}
        catch (const exception& e) {print("caught exception: {}", e.what());}
        catch (...) {print("uncaught exception");}
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    Sleep(50);
    log_end();
    return 0;
}
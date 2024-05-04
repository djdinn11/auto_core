/*!
\file auto_core.cc
\brief The starting point for Auto Core.

This module contains a function map for key bindings and shortcuts.

Default values are:
numkey 0 - a function key
numkey 1 - activates Auto Core
numkey 0 + 1 - closes Auto Core
*/
#include <auto_core.h>
#include <config.h>
#include <runtime.h>

unordered_map<int, function_state> ac_numkey_event;
bool primary = true;
HWND program_window;
HWND close_window;
HHOOK keyboard_hook;
DWORD main_thread_id;

void set_action_map() {
    ac_numkey_event[numkey_0] = {activate_function_key, deactivate_function_key};
    ac_numkey_event[numkey_1] = {activate_auto_core, close_program};
    ac_numkey_event[numkey_2] = {activate_word, activate_vs_code};
    ac_numkey_event[numkey_3] = {activate_iTunes, print_Katrina_choice};
    ac_numkey_event[numkey_4] = {print_Daniel_choice, activate_chrome};
    ac_numkey_event[numkey_5] = {print_Luna_choice, activate_visual};
    ac_numkey_event[numkey_6] = {iTunes_next_song, activate_discord};
    ac_numkey_event[numkey_7] = {print_gpt_message, activate_folder};
    ac_numkey_event[numkey_8] = {print_spotify_songs, activate_firefox};
    ac_numkey_event[numkey_9] = {print_timestamp, print_Lily_choice};
    ac_numkey_event[numkey_star] = {get_user_sp_queue, print_episode_title};
    ac_numkey_event[numkey_plus] = {print_iTunes_songs, print_next_up_song_list};
    ac_numkey_event[numkey_dot]  = {spotify_next_song, activate_spotify};
    ac_numkey_event[numkey_enter] = {spotify_play_pause, print_Star_choice};
    ac_numkey_event[numkey_dash]  = {sp_switch_player, print_Jose_choice};
    ac_numkey_event[numkey_slash] = {retrieve_and_delete_recycle_bin, remove_iTunes_song};
    ac_numkey_event[numkey_play_pause] = {iTunes_play_pause, print_Eric_choice};
}
void process_numpad_event(const MSG& msg) {
    int vk_code = static_cast<int>(msg.lParam);
    if (taskbar.switch_set) {
        taskbar.switch_windows(vk_code);
        primary = true;
        return;
    }
    auto ac_shortcut = ac_numkey_event.find(vk_code);
    if (ac_shortcut != ac_numkey_event.end()) {
        if (primary) {
            ac_shortcut->second.primary();
        }
        else {
            ac_shortcut->second.secondary();
        }
    }
    taskbar.switch_keycode = vk_code;
    if (!primary && vk_code != numkey_0) {
        primary = true;
    }
}
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
    start_server();
    create_pipe_servers();
    start_components();
    config.runtime_enabled ? parse_and_set_action_map() : set_action_map();
    set_taskbar_positions();
    print("Program ready");
    print(get_day_of_week());
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0) > 0) {
        try {process_numpad_event(msg);}
        catch (const exception& e) {print("caught exception: {}", e.what());}
        catch (...) {print("uncaught exception");}
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}
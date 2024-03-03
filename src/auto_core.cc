#include <auto_core.h>

struct function_state {
    function<void()> primary;
    function<void()> secondary;
};
unordered_map<int, function_state> ac_numkey_event;
void set_action_map() {
    ac_numkey_event[ac_numkey_0] = {activate_function_key, deactivate_function_key};
    ac_numkey_event[ac_numkey_1] = {activate_auto_core, close_program};
    ac_numkey_event[ac_numkey_2] = {activate_word, activate_vs_code};
    ac_numkey_event[ac_numkey_3] = {activate_iTunes, activate_wordpad};
    ac_numkey_event[ac_numkey_4] = {print_Daniel_choice, activate_chrome};
    ac_numkey_event[ac_numkey_5] = {print_next_up_song_list, activate_visual};
    ac_numkey_event[ac_numkey_6] = {iTunes_next_song, activate_discord};
    ac_numkey_event[ac_numkey_7] = {print_gpt_message, activate_folder};
    ac_numkey_event[ac_numkey_8] = {print_spotify_songs, activate_firefox};
    ac_numkey_event[ac_numkey_9] = {print_timestamp, print_Lily_choice};
    ac_numkey_event[ac_numkey_star] = {get_user_sp_queue, print_episode_title};
    ac_numkey_event[ac_numkey_plus] = {print_Luna_choice, print_iTunes_songs};
    ac_numkey_event[ac_numkey_dot]  = {spotify_next_song, activate_spotify};
    ac_numkey_event[ac_numkey_enter] = {spotify_play_pause, print_Star_choice};
    ac_numkey_event[ac_numkey_dash]  = {sp_switch_player, print_Jose_choice};
    ac_numkey_event[ac_numkey_slash] = {retrieve_and_delete_recycle_bin, print_Eric_choice};
    ac_numkey_event[ac_numkey_play_pause] = {iTunes_play_pause, print_Katrina_choice};
}
void process_numpad_event(const MSG& msg) {
    if (taskbar.switch_set) {
        taskbar.switch_windows(msg.message);
        primary = true;
        return;
    }
    auto ac_shortcut = ac_numkey_event.find(msg.message);
    if (ac_shortcut != ac_numkey_event.end()) {
        if (primary) {
            ac_shortcut->second.primary();
        }
        else {
            ac_shortcut->second.secondary();
        }
    }
    taskbar.switch_keycode = msg.message;
    if (!primary && msg.message != ac_numkey_0) {
        primary = true;
    }
}
int main() {
    log_init();
    crash_check();
    run_server();
    start_sp_song_thread();
    MSG msg;
    SetConsoleTitle(L"Auto Core");
    SetUnhandledExceptionFilter(unhandled_exception_handler);
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCtrlHandler(x_close_event, TRUE);
    keyboard_hook = SetWindowsHookEx(WH_KEYBOARD_LL, send_numpad_event, NULL, 0);
    main_thread_id = GetCurrentThreadId();
    set_action_map();
    program_window = GetConsoleWindow();
    print("Program ready");
    while (GetMessage(&msg, NULL, 0, 0) > 0) {
        try {process_numpad_event(msg);}
        catch (const exception& e) {print("caught exception: {}", e.what());}
        catch (...) {print("uncaught exception");}
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    log_end();
    return 0;
}
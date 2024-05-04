/*!
\file auto_core.ixx
\brief The main module.
*/
export module auto_core;
export import core;
import <Windows.h>;

export struct function_state {
    function<void()> primary;
    function<void()> secondary;
};
export unordered_map<int, function_state> ac_numkey_event;

export void set_action_map() {
    ac_numkey_event[numkey_0] = {activate_function_key, deactivate_function_key};
    ac_numkey_event[numkey_1] = {activate_auto_core, close_program};
    ac_numkey_event[numkey_2] = {activate_word, activate_vs_code};
    ac_numkey_event[numkey_3] = {activate_iTunes, activate_notepad};
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
    ac_numkey_event[numkey_dash]  = {print_task_list, print_Jose_choice};
    ac_numkey_event[numkey_slash] = {retrieve_and_delete_recycle_bin, remove_iTunes_song};
    ac_numkey_event[numkey_play_pause] = {iTunes_play_pause, print_Eric_choice};
}
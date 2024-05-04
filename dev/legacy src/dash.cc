#include <dash.h>
#include<numkey.h>

function<void()> get_function_by_name(const string& function_name) {
    static const unordered_map<string, function<void()>> function_map = {
        {"print_iTunes_songs", &print_iTunes_songs},
        {"iTunes_next_song", &iTunes_next_song},
        {"print_next_up_song_list", &print_next_up_song_list},
        {"iTunes_play_pause", &iTunes_play_pause},
        {"remove_iTunes_song", &remove_iTunes_song},
        {"print_Eric_choice", &print_Eric_choice},
        {"print_Katrina_choice", &print_Katrina_choice},
        {"print_Lily_choice", &print_Lily_choice},
        {"print_Star_choice", &print_Star_choice},
        {"print_Luna_choice", &print_Luna_choice},
        {"print_Daniel_choice", &print_Daniel_choice},
        {"print_Jose_choice", &print_Jose_choice},
        {"print_Tabby_choice", &print_Tabby_choice},
        {"print_gpt_message", &print_gpt_message},
        {"close_program", &close_program},
        {"activate_function_key", &activate_function_key},
        {"deactivate_function_key", &deactivate_function_key},
        {"print_timestamp", &print_timestamp},
        {"retrieve_and_delete_recycle_bin", &retrieve_and_delete_recycle_bin},
        {"get_user_sp_queue", &get_user_sp_queue},
        {"print_spotify_songs", &print_spotify_songs},
        {"spotify_play_pause", &spotify_play_pause},
        {"spotify_next_song", &spotify_next_song},
        {"sp_switch_player", &sp_switch_player},
        {"spotify_next_song", &spotify_next_song},
        {"print_episode_title", &print_episode_title},
        {"activate_auto_core", &activate_auto_core},
        {"activate_folder", &activate_folder},
        {"activate_word", &activate_word},
        {"activate_vs_code", &activate_vs_code},
        {"activate_iTunes", &activate_iTunes},
        {"activate_discord", &activate_discord},
        {"activate_chrome", &activate_chrome},
        {"activate_spotify", &activate_spotify},
        {"activate_visual", &activate_visual},
        {"activate_firefox", &activate_firefox},
        {"activate_wordpad", &activate_wordpad},
    };
    auto it = function_map.find(function_name);
    if (it != function_map.end()) {
        return it->second;
    }
    else {
        return nullptr;
    }
}
int get_numkey_vk_code(const string & vk_code_string) {
    static const unordered_map<string, int> numkey_vk_code_map = {
        {"numkey_0", numkey_0},
        {"numkey_1", numkey_1},
        {"numkey_2", numkey_2},
        {"numkey_3", numkey_3},
        {"numkey_4", numkey_4},
        {"numkey_5", numkey_5},
        {"numkey_6", numkey_6},
        {"numkey_7", numkey_7},
        {"numkey_8", numkey_8},
        {"numkey_9", numkey_9},
        {"numkey_star", numkey_star},
        {"numkey_plus", numkey_plus},
        {"numkey_dot", numkey_dot},
        {"numkey_enter", numkey_enter},
        {"numkey_dash", numkey_dash},
        {"numkey_slash", numkey_slash},
        {"numkey_play_pause", numkey_play_pause},
    };
    auto it = numkey_vk_code_map.find(vk_code_string);
    if (it != numkey_vk_code_map.end()) {
        return it->second;
    }
    else {
        return -1;
    }
}

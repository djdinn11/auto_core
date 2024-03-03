#include <config.h>

function<void()> get_function_by_name(const string& function_name) {
    static const unordered_map<string, function<void()>> functionMap ={
        {"activate_function_key", &activate_function_key},
        {"deactivate_function_key", &deactivate_function_key},
        {"activate_auto_core", &activate_auto_core},
        {"close_program", &close_program},
        {"activate_word", &activate_word},
        {"activate_taskbar_10", &activate_taskbar_10},
        {"activate_itunes", &activate_itunes},
        {"spotify_play_pause", &spotify_play_pause},
        {"print_daniel_choice", &print_daniel_choice},
        {"activate_chrome", &activate_chrome},
        {"print_lily_choice", &print_lily_choice},
        {"activate_visual", &activate_visual},
        {"print_luna_choice", &print_luna_choice},
        {"activate_discord", &activate_discord},
        {"print_gpt_message", &print_gpt_message},
        {"activate_folder", &activate_folder},
        {"print_spotify_songs", &print_spotify_songs},
        {"activate_firefox", &activate_firefox},
        {"print_timestamp", &print_timestamp},
        {"activate_taskbar_9", &activate_taskbar_9},
        {"get_user_sp_queue", &get_user_sp_queue},
        {"print_episode_title", &print_episode_title},
        {"itunes_next_song", &itunes_next_song},
        {"print_itunes_songs", &print_itunes_songs},
        {"spotify_next_song", &spotify_next_song},
        {"activate_spotify", &activate_spotify},
        {"print_choice_display", &print_choice_display},
        {"print_star_choice", &print_star_choice},
        {"sp_switch_player", &sp_switch_player},
        {"print_jose_choice", &print_jose_choice},
        {"retrieve_and_delete_recycle_bin", &retrieve_and_delete_recycle_bin},
        {"print_eric_choice", &print_eric_choice}
    };
    auto it = functionMap.find(function_name);
    if (it != functionMap.end()) {
        return it->second;
    }
    else {
        return nullptr;
    }
}

void parse_and_set_action_map() {
    ifstream config_file(R"(config.ini)");
    string line;
    getline(config_file, line);
    while (getline(config_file, line)) {
        size_t opening_brace = line.find('{');
        size_t closing_brace = line.find('}');
        string inside_braces = line.substr(opening_brace + 1, closing_brace - opening_brace - 1);
        size_t first_comma = inside_braces.find(',');
        size_t second_comma = inside_braces.rfind(',');
        string key_str = inside_braces.substr(0, first_comma);
        string primary = inside_braces.substr(first_comma + 2, second_comma - first_comma - 2);
        string secondary = inside_braces.substr(second_comma + 2);
        int key = stoi(key_str);
        print("{} = {}, {}.", key, primary, secondary);
          if (key == numkey_0) {
              ac_numkey_event[AC_NUMKEY_0] ={get_function_by_name(primary), get_function_by_name(secondary)};
          }
          else if (key == numkey_1) {
              ac_numkey_event[AC_NUMKEY_1] ={get_function_by_name(primary), get_function_by_name(secondary)};
          }
          else if (key == numkey_2) {
              ac_numkey_event[AC_NUMKEY_2] ={get_function_by_name(primary), get_function_by_name(secondary)};
          }
          else if (key == numkey_3) {
              ac_numkey_event[AC_NUMKEY_3] ={get_function_by_name(primary), get_function_by_name(secondary)};
          }
          else if (key == numkey_4) {
              ac_numkey_event[AC_NUMKEY_4] ={get_function_by_name(primary), get_function_by_name(secondary)};
          }
          else if (key == numkey_5) {
              ac_numkey_event[AC_NUMKEY_5] ={get_function_by_name(primary), get_function_by_name(secondary)};
          }
          else if (key == numkey_6) {
              ac_numkey_event[AC_NUMKEY_6] ={get_function_by_name(primary), get_function_by_name(secondary)};
          }
          else if (key == numkey_7) {
              ac_numkey_event[AC_NUMKEY_7] ={get_function_by_name(primary), get_function_by_name(secondary)};
          }
          else if (key == numkey_8) {
              ac_numkey_event[AC_NUMKEY_8] ={get_function_by_name(primary), get_function_by_name(secondary)};
          }
          else if (key == numkey_9) {
              ac_numkey_event[AC_NUMKEY_9] ={get_function_by_name(primary), get_function_by_name(secondary)};
          }
          else if (key == numkey_star) {
              ac_numkey_event[AC_NUMKEY_STAR] ={get_function_by_name(primary), get_function_by_name(secondary)};
          }
          else if (key == numkey_plus) {
              ac_numkey_event[AC_NUMKEY_PLUS] ={get_function_by_name(primary), get_function_by_name(secondary)};
          }
          else if (key == numkey_enter) {
              ac_numkey_event[AC_NUMKEY_ENTER] ={get_function_by_name(primary), get_function_by_name(secondary)};
          }
          else if (key == numkey_dash) {
              ac_numkey_event[AC_NUMKEY_DASH] ={get_function_by_name(primary), get_function_by_name(secondary)};
          }
          else if (key == numkey_dot) {
              ac_numkey_event[AC_NUMKEY_DOT] ={get_function_by_name(primary), get_function_by_name(secondary)};
          }
          else if (key == numkey_slash) {
              ac_numkey_event[AC_NUMKEY_SLASH] ={get_function_by_name(primary), get_function_by_name(secondary)};
              break;
          }
          print("{} is set", key);
      }
      config_file.close();
}
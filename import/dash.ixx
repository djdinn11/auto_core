/*!
 * \file dash.ixx
 * \brief This module is used for runtime configuration if enabled.
*/
export module dash;
export import core;
import auto_core;
import <Windows.h>;

export {
    function<void()> get_function_by_name(const string& function_name);
    int get_numkey_vk_code(const string& vk_code_string);
    void parse_and_set_action_map();
}

void parse_and_set_action_map() {
    ifstream config_file(R"(.\config\runtime.ini)");
    string line;
    while (getline(config_file, line)) {
        size_t opening_bracket = line.find('[');
        size_t closing_bracket = line.find(']');
        string key_string = line.substr(opening_bracket + 1, closing_bracket - opening_bracket - 1);
        size_t opening_brace = line.find('{');
        size_t comma_after_parenthese = line.find("),");
        size_t comma_delimiter = line.find(',');
        if (comma_after_parenthese != string::npos) {
            comma_delimiter = comma_after_parenthese + 1;
        }
        size_t closing_brace = line.find('}');
        int key = get_numkey_vk_code(key_string);
        string primary = line.substr(opening_brace + 1, comma_delimiter - opening_brace - 1);
        string secondary = line.substr(comma_delimiter + 2, closing_brace - comma_delimiter - 2);
        print("{} = {}, {}", key, primary, secondary);
        if (key == numkey_0) {
            ac_numkey_event[numkey_0] = {get_function_by_name(primary), get_function_by_name(secondary)};
        }
        else if (key == numkey_1) {
            ac_numkey_event[numkey_1] = {get_function_by_name(primary), get_function_by_name(secondary)};
        }
        else if (key == numkey_2) {
            ac_numkey_event[numkey_2] = {get_function_by_name(primary), get_function_by_name(secondary)};
        }
        else if (key == numkey_3) {
            ac_numkey_event[numkey_3] = {get_function_by_name(primary), get_function_by_name(secondary)};
        }
        else if (key == numkey_4) {
            ac_numkey_event[numkey_4] = {get_function_by_name(primary), get_function_by_name(secondary)};
        }
        else if (key == numkey_5) {
            ac_numkey_event[numkey_5] = {get_function_by_name(primary), get_function_by_name(secondary)};
        }
        else if (key == numkey_6) {
            ac_numkey_event[numkey_6] = {get_function_by_name(primary), get_function_by_name(secondary)};
        }
        else if (key == numkey_7) {
            ac_numkey_event[numkey_7] = {get_function_by_name(primary), get_function_by_name(secondary)};
        }
        else if (key == numkey_8) {
            ac_numkey_event[numkey_8] = {get_function_by_name(primary), get_function_by_name(secondary)};
        }
        else if (key == numkey_9) {
            ac_numkey_event[numkey_9] = {get_function_by_name(primary), get_function_by_name(secondary)};
        }
        else if (key == numkey_star) {
            ac_numkey_event[numkey_star] = {get_function_by_name(primary), get_function_by_name(secondary)};
        }
        else if (key == numkey_plus) {
            ac_numkey_event[numkey_plus] = {get_function_by_name(primary), get_function_by_name(secondary)};
        }
        else if (key == numkey_enter) {
            ac_numkey_event[numkey_enter] = {get_function_by_name(primary), get_function_by_name(secondary)};
        }
        else if (key == numkey_dash) {
            ac_numkey_event[numkey_dash] = {get_function_by_name(primary), get_function_by_name(secondary)};
        }
        else if (key == numkey_dot) {
            ac_numkey_event[numkey_dot] = {get_function_by_name(primary), get_function_by_name(secondary)};
        }
        else if (key == numkey_slash) {
            ac_numkey_event[numkey_slash] = {get_function_by_name(primary), get_function_by_name(secondary)};
        }

        else if (key == numkey_play_pause) {
            ac_numkey_event[numkey_play_pause] = {get_function_by_name(primary), get_function_by_name(secondary)};
        }
        print("{} is set", key);
    }
    config_file.close();
}

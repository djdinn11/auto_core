/*!
\file runtime.ixx
\brief This module contains runtime maps and configurations if enabled.
*/
export module runtime;
import visual;
import numkey;
import main;
import taskbar;
import auto_core;
import <Windows.h>;

export {
    LRESULT CALLBACK send_numpad_event(int nCode, WPARAM wParam, LPARAM lParam);
    void process_numpad_event(const MSG& msg);
}

export {
    constexpr int ac_numkey_0 = WM_APP + 96;
    constexpr int ac_numkey_1 = WM_APP + 97;
    constexpr int ac_numkey_2 = WM_APP + 98;
    constexpr int ac_numkey_3 = WM_APP + 99;
    constexpr int ac_numkey_4 = WM_APP + 100;
    constexpr int ac_numkey_5 = WM_APP + 101;
    constexpr int ac_numkey_6 = WM_APP + 102;
    constexpr int ac_numkey_7 = WM_APP + 103;
    constexpr int ac_numkey_8 = WM_APP + 104;
    constexpr int ac_numkey_9 = WM_APP + 105;
    constexpr int ac_numkey_star = WM_APP + 106;
    constexpr int ac_numkey_plus = WM_APP + 107;
    constexpr int ac_numkey_enter = WM_APP + 108;
    constexpr int ac_numkey_dash = WM_APP + 109;
    constexpr int ac_numkey_dot = WM_APP + 110;
    constexpr int ac_numkey_slash = WM_APP + 111;
    constexpr int ac_numkey_play_pause = WM_APP + 112;
}
LRESULT CALLBACK send_numpad_event(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode >= 0 && wParam == WM_KEYDOWN) {
        KBDLLHOOKSTRUCT* p = reinterpret_cast<KBDLLHOOKSTRUCT*>(lParam);
        int vk_code = p->vkCode;
        if (vk_code == enter_key_vk && (p->flags & LLKHF_EXTENDED)) {
            vk_code = 108;
        }
        else if (vk_code == media_play_pause_vk) {
            vk_code = 112;
        }
        if (vk_code >= numkey_0 && vk_code <= numkey_play_pause) {
            logg("vk_code = {}", vk_code);
            if (vk_code == numkey_0) {
                PostThreadMessage(main_thread_id, ac_numkey_0, 1, vk_code);
            }
            else if (vk_code == numkey_1) {
                PostThreadMessage(main_thread_id, ac_numkey_1, 1, vk_code);
            }
            else if (vk_code == numkey_2) {
                PostThreadMessage(main_thread_id, ac_numkey_2, 1, vk_code);
            }
            else if (vk_code == numkey_3) {
                PostThreadMessage(main_thread_id, ac_numkey_3, 1, vk_code);
            }
            else if (vk_code == numkey_4) {
                PostThreadMessage(main_thread_id, ac_numkey_4, 1, vk_code);
            }
            else if (vk_code == numkey_5) {
                PostThreadMessage(main_thread_id, ac_numkey_5, 1, vk_code);
            }
            else if (vk_code == numkey_6) {
                PostThreadMessage(main_thread_id, ac_numkey_6, 1, vk_code);
            }
            else if (vk_code == numkey_7) {
                PostThreadMessage(main_thread_id, ac_numkey_7, 1, vk_code);
            }
            else if (vk_code == numkey_8) {
                PostThreadMessage(main_thread_id, ac_numkey_8, 1, vk_code);
            }
            else if (vk_code == numkey_9) {
                PostThreadMessage(main_thread_id, ac_numkey_9, 1, vk_code);
            }
            else if (vk_code == numkey_star) {
                PostThreadMessage(main_thread_id, ac_numkey_star, 1, vk_code);
            }
            else if (vk_code == numkey_plus) {
                PostThreadMessage(main_thread_id, ac_numkey_plus, 1, vk_code);
            }
            else if (vk_code == numkey_enter) {
                PostThreadMessage(main_thread_id, ac_numkey_enter, 1, vk_code);
            }
            else if (vk_code == numkey_dash) {
                PostThreadMessage(main_thread_id, ac_numkey_dash, 1, vk_code);
            }
            else if (vk_code == numkey_dot) {
                PostThreadMessage(main_thread_id, ac_numkey_dot, 1, vk_code);
            }
            else if (vk_code == numkey_slash) {
                PostThreadMessage(main_thread_id, ac_numkey_slash, 1, vk_code);
            }
            else if (vk_code == numkey_play_pause) {
                PostThreadMessage(main_thread_id, ac_numkey_play_pause, 1, vk_code);
            }
            return 1;
        }
    }
    return CallNextHookEx(NULL, nCode, wParam, lParam);
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

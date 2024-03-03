#include <numkey.h>

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
                PostThreadMessage(main_thread_id, ac_numkey_0, 0, 0);
            }
            else if (vk_code == numkey_1) {
                PostThreadMessage(main_thread_id, ac_numkey_1, 0, 0);
            }
            else if (vk_code == numkey_2) {
                PostThreadMessage(main_thread_id, ac_numkey_2, 0, 0);
            }
            else if (vk_code == numkey_3) {
                PostThreadMessage(main_thread_id, ac_numkey_3, 0, 0);
            }
            else if (vk_code == numkey_4) {
                PostThreadMessage(main_thread_id, ac_numkey_4, 0, 0);
            }
            else if (vk_code == numkey_5) {
                PostThreadMessage(main_thread_id, ac_numkey_5, 0, 0);
            }
            else if (vk_code == numkey_6) {
                PostThreadMessage(main_thread_id, ac_numkey_6, 0, 0);
            }
            else if (vk_code == numkey_7) {
                PostThreadMessage(main_thread_id, ac_numkey_7, 0, 0);
            }
            else if (vk_code == numkey_8) {
                PostThreadMessage(main_thread_id, ac_numkey_8, 0, 0);
            }
            else if (vk_code == numkey_9) {
                PostThreadMessage(main_thread_id, ac_numkey_9, 0, 0);
            }
            else if (vk_code == numkey_star) {
                PostThreadMessage(main_thread_id, ac_numkey_star, 0, 0);
            }
            else if (vk_code == numkey_plus) {
                PostThreadMessage(main_thread_id, ac_numkey_plus, 0, 0);
            }
            else if (vk_code == numkey_enter) {
                PostThreadMessage(main_thread_id, ac_numkey_enter, 0, 0);
            }
            else if (vk_code == numkey_dash) {
                PostThreadMessage(main_thread_id, ac_numkey_dash, 0, 0);
            }
            else if (vk_code == numkey_dot) {
                PostThreadMessage(main_thread_id, ac_numkey_dot, 0, 0);
            }
            else if (vk_code == numkey_slash) {
                PostThreadMessage(main_thread_id, ac_numkey_slash, 0, 0);
            }
            else if (vk_code == numkey_play_pause) {
                PostThreadMessage(main_thread_id, ac_numkey_play_pause, 0, 0);
            }
            return 1;
        }
    }
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}
/*!
\file numkey.cc
\brief Implementation of numeric keypad event handling.

This file contains the implementation for handling numeric keypad inputs. It includes functions for
translating numeric key codes to corresponding application-specific messages or actions, processing
key events, and posting messages to the main application thread or specific modules as required.

Dependencies:
- `numkey.h`: Defines the key codes and related constants used throughout this implementation.
- `main.h`: Utilizes utility functions or variables defined in the main application module, necessary for integrating the numeric keypad functionality into the broader application context.

Special Considerations:
- This module is designed to work with a global keyboard hook to intercept and process numeric keypad inputs regardless of the application's focus state.
- Care has been taken to ensure that key events are processed efficiently to minimize the impact on the application's performance, especially under high input rates.

\see numkey.h for the definitions of key codes and constants.
\see main.h for integration with the main application module.
*/

#include <numkey.h>

/*!
* \brief Global keyboard hook callback to process numpad and media key events.
*
* This function is designed to be set as a callback for a global keyboard hook. It intercepts
* numpad and media play/pause key events, translating them into custom application messages
* that are then posted to the main thread message queue.
*
* \param nCode A code the hook procedure uses to determine how to process the message.
* \param wParam The identifier of the keyboard message. This parameter can be WM_KEYDOWN,
* WM_KEYUP, WM_SYSKEYDOWN, or WM_SYSKEYUP.
* \param lParam A pointer to a KBDLLHOOKSTRUCT structure that contains details about the message.
*
* \return If the function processes the keyboard message, it returns 1. Otherwise, it calls
* CallNextHookEx and returns its value.
*
* \note This function is specifically designed to handle keyboard events for the numeric keypad
* and the media play/pause key. It maps these keys to custom-defined messages (e.g., ac_numkey_0,
* ac_numkey_play_pause) and posts them to the application's main thread. The custom messages are
* defined with WM_APP as a base to avoid conflict with system message values.
*
* \see KBDLLHOOKSTRUCT for more information on the keyboard message structure.
* \see PostThreadMessage for details on how messages are posted to the thread message queue.
* \see main_thread_id, which should be set to the identifier of the application's main thread.
*/
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
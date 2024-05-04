/*!
\file numkey.h
\brief Defines key codes and messages for numeric keypad and special keys handling within Auto Core.

\note Auto Core uses a custom value of 112 for the media play/pause key, while the actual vk code is 179. This deviation
allows for consistent handling of application-specific messages. The highest numpad vk code used is 111 for the slash key.
\note Auto Core uses a custom value of 108 for the numpad enter, while the actual vk code is 13--the same as the main keyboard enter vk code.
However, the numpad enter key is intended to have a distinct behavior within Auto Core. To differentiate it, we check for the LLKHF_EXTENDED flag,
which is set for the numpad enter key press but not for the main keyboard enter key press.
*/

#pragma once
#include <visual.h>
#include <main.h>

LRESULT CALLBACK send_numpad_event(int nCode, WPARAM wParam, LPARAM lParam);

#define ac_numkey_0 (WM_APP + 96)
#define ac_numkey_1 (WM_APP + 97)
#define ac_numkey_2 (WM_APP + 98)
#define ac_numkey_3 (WM_APP + 99)
#define ac_numkey_4 (WM_APP + 100)
#define ac_numkey_5 (WM_APP + 101)
#define ac_numkey_6 (WM_APP + 102)
#define ac_numkey_7 (WM_APP + 103)
#define ac_numkey_8 (WM_APP + 104)
#define ac_numkey_9 (WM_APP + 105)
#define ac_numkey_star  (WM_APP + 106)
#define ac_numkey_plus  (WM_APP + 107)
#define ac_numkey_enter (WM_APP + 108)
#define ac_numkey_dash  (WM_APP + 109)
#define ac_numkey_dot   (WM_APP + 110)
#define ac_numkey_slash (WM_APP + 111)
#define ac_numkey_play_pause (WM_APP + 112)

const int enter_key_vk = 13;
const int media_play_pause_vk = 179;
const int numkey_0 = 96;
const int numkey_1 = 97;
const int numkey_2 = 98;
const int numkey_3 = 99;
const int numkey_4 = 100;
const int numkey_5 = 101;
const int numkey_6 = 102;
const int numkey_7 = 103;
const int numkey_8 = 104;
const int numkey_9 = 105;
const int numkey_star = 106;
const int numkey_plus = 107;
const int numkey_enter = 108;
const int numkey_dash = 109;
const int numkey_dot = 110;
const int numkey_slash = 111;
const int numkey_play_pause = 112;
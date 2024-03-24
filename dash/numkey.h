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
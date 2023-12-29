#pragma once
#include <visual.h>

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
const int numkey_minus = 109;
const int numkey_period = 110;
const int numkey_divide = 111;

void send_winkey(int position);
void send_winkey_with_number(int number);
void press_and_hold_winkey();
void release_winkey();
void set_clipboard_text(const wstring& text);
void simulate_paste();
void simulate_save();
void print_to_screen(string msg);
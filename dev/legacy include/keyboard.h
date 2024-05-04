/*!
\file keyboard.h
\brief Supports the simulation of keyboard events.
*/
#pragma once
#include <visual.h>

void send_winkey(int position);
void send_winkey_and_number(int number);
void press_and_hold_winkey();
void release_winkey();
void send_alt_tab();
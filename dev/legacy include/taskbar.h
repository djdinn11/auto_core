/*!
\file taskbar.h
\brief Enables quick access to taskbar applications within the first 10 positions, enhancing task switching and application management.

This module leverages Windows shortcuts to facilitate rapid switching and management of frequently used applications,
streamlining the user's workflow.

\todo Run tests on iTunes. See the code below.
void Taskbar::activate_iTunes() {
	if (ac_iTunes.initialized)
	{
		send_winkey(position["itunes"]);
	}
	else {ac_iTunes.initialize_com();}
}
*/
#pragma once
#include <visual.h>
#include <main.h>

class Taskbar {
public:
	int switch_position;
	int switch_keycode;
	bool switch_set;
	void switch_windows(int keycode);
	void activate_auto_core();
	void activate_folder();
	void activate_word();
	void activate_vs_code();
	void activate_iTunes();
	void activate_chrome();
	void activate_visual();
	void activate_discord();
	void activate_firefox();
	void activate_spotify();
	int folder_windows = 0;
	int word_windows = 0;
	int vs_code_windows = 0;
	int chrome_windows = 0;
	int visual_windows = 0;
	int firefox_windows = 0;
	bool winkey_locked;
};

extern Taskbar taskbar;
extern unordered_map<string, int> position;

void set_taskbar_positions();
void activate_auto_core();
void activate_folder();
void activate_word();
void activate_vs_code();
void activate_iTunes();
void activate_discord();
void activate_chrome();
void activate_spotify();
void activate_visual();
void activate_firefox();
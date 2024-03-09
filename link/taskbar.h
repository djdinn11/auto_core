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
	void activate_taskbar_9();
	void activate_taskbar_10();
	void activate_taskbar_10_multiple();
	int folder_windows = 0;
	int word_windows = 0;
	int vs_code_windows = 0;
	int chrome_windows = 0;
	int visual_windows = 0;
	int firefox_windows = 0;
	bool winkey_locked;
};

extern Taskbar taskbar;

wstring get_window_title(HWND hwnd);
wstring get_window_class(HWND hwnd);

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
void activate_taskbar_9();
void activate_taskbar_10();
void activate_taskbar_10_multiple();
void set_focus_auto_core();
#include <print.h>
#include <keyboard.h>
#include <clock.h>
#include <gpt.hpp>
#include <star.h>
#include <Spotify.h>
#include <iTunes.h>
#include <choice.h>
#include <taskbar.h>

void print_to_screen(string msg) {
    print(msg);
    wss ws;
    ws << msg.c_str() << L"\n";
    set_clipboard_text(ws.str());
    simulate_paste();
}
void print_Star_choice() {
    int choice_number = getRandomNumber(1, 3);
    string select_msg = f("Star selects {}.\n", choice_number);
    print_to_screen(select_msg);
}
void print_Lily_choice() {
    int choice_number = getRandomNumber(1, 3);
    string select_msg = f("Luna selects {}.\n", choice_number);
    print_to_screen(select_msg);
}
void print_gpt_message() {
	HWND currentWindowHandle = GetForegroundWindow();
    activate_Auto_Core();
    string gpt_message = get_gpt_message();
	print(gpt_message + "\n");
	wss ws;
	ws << gpt_message.c_str();
	set_clipboard_text(ws.str());
	SetForegroundWindow(currentWindowHandle);
	simulate_paste();
}
void print_timestamp() {
    string timestamp = get_timestamp() + "\n";
    print_to_screen(timestamp);
}
void print_episode_title() {
    set_episode_title();
    print_to_screen(episode_title);
    simulate_save();
}
void print_iTunes_song() {
    wstring iTunes_wstr = ac_iTunes.get_current_track();
    string iTunes_str = wstringToString(iTunes_wstr);
    if (!iTunes_str.empty()) {
        print(iTunes_str + "\n");
    }
    set_clipboard_text(iTunes_wstr + L"\n\n");
    Sleep(50);
    simulate_paste();
}
void print_Spotify_song() {
    string song = ac_Spotify.get_current_song();
    if (song.empty()) {
        set_clipboard_text(L"\n\n");
        simulate_paste();
        return;
    }
    song += "\n";
    print(song);
    wss ws;
    ws << Utf8ToUtf16(song).c_str() << L"\n";
    set_clipboard_text(ws.str());
    Sleep(50);
    simulate_paste();
}
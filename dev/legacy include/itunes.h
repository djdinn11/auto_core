/*!
\file itunes.h
\brief This module provides support for music player intregation with iTunes.
\todo Run tests on whether iTunes is started or not.

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

void start_iTunes_component();
void print_iTunes_songs();
void print_next_up_song_list();
void iTunes_play_pause();
void iTunes_prev_song();
void iTunes_next_song();
void update_iTunes_logger();
void send_iTunes_end_signal();
void remove_iTunes_song();

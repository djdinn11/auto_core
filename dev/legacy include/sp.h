/*!
\file sp.h
\brief Integrates Spotify functionality within Auto Core, providing music player automation and control.

Facilitates interaction with Spotify, allowing Auto Core to automate music playback and playlist management,
thereby enriching the user's audio experience.
*/
#pragma once
#include <visual.h>

void start_sp_component();
void get_user_sp_queue();
void sp_song_thread();
void start_sp_song_thread();
void print_spotify_songs();
void spotify_play_pause();
void spotify_prev_song();
void sp_switch_player();
void download_album_cover();
void spotify_next_song();
void send_sp_end_signal();
void update_sp_logger();
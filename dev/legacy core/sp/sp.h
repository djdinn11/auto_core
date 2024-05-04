#pragma once
#include <visual.h>
#include <nlohmann/json.hpp>
#include <cpr/cpr.h>

using json = nlohmann::json;
using namespace cpr;

class Spotify {
public:
    Spotify();
    void get_current_song();
    bool download_album_cover();
    void play_pause();
    void next_song();
    void prev_song();
    string get_user_queue();
    int last_status_code;
    vector<string> song_history;
    string last_song;
    string client_id;
    string client_secret;
    string credentials_64;
    string access_token;
    string refresh_token;
    string album_url;
    int start_stamp;
    int timerate;
    bool check_timerate();
    void extract_tokens();
    bool refresh_tokens();
    int pause_song();
    int play_song();
    int music_song_count;
    string tokens_path;
    string devices_path;
    string codes_path;
    int remaining_song_duration_ms;
    bool next_song_clicked;
    bool is_spotify_playing();
    string desktop_device_id;
    string mobile_device_id;
    void switch_player();
    int minutes_stamp;
    bool song_history_contains(string song);
    int song_history_index = 0;
    int string_array_size = 52;
    array<string, 52> song_history_array;
    void get_devices();
    void get_credentials();
    string authorization_header;
    string content_type;
    string content_length;
    bool is_playing;
    void transfer_playback(string device_id);
    void post_next_or_prev(string url);
    bool is_spotify_open();
    void start_playback_on_desktop();
    void start_playback_on_mobile();
    string format_song_title(const json& song_details);
    string format_artist_name(const json& artists);
    void calculate_remaining_song_duration_ms(const json& song_details);
    void update_devices();
    int sp_position;
    void get_sp_position();
    void activate();
};

extern Spotify ac_spotify;

void get_user_sp_queue();
void sp_song_thread();
void start_sp_song_thread();
void print_spotify_songs();
void spotify_play_pause();
void spotify_prev_song();
void sp_switch_player();
void download_album_cover();
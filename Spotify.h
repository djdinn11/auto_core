#pragma once
#include <visual.h>

class Spotify {
public:
    Spotify();
    string get_current_song();
    bool download_album_cover();
    void GetUserPlaylists();
    void play_pause();
    void next_song();
    void prev_song();
private:
    string last_song;
    string client_id;
    string client_secret;
    string credentials;
    string credentials_64;
    string access_token;
    string refresh_token;
    string album_url;
    int start_stamp;
    int timerate;
    bool CheckTimerate();
    void ExtractTokens();
    void RefreshTokens();
    int Pause();
    int Play();
};

extern Spotify ac_Spotify;
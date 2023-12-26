#pragma once
#include <visual.h>

class Spotify {
public:
    Spotify();
    void RefreshTokens();
    string GetCurrentSong();
    bool DownloadAlbumCover();
    void GetUserPlaylists();
    int Pause();
    int Play();
    void PlayPause();
    void Next();
    void Previous();
    string prev_song;
private:
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
};

extern Spotify mySpotify;
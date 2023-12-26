#pragma once 
#include <visual.h>
#include <comdef.h>

struct TrackInfo {
    wstring name;
    wstring artist;
    wstring album;
    int duration;
    wstring location; 
};

class iTunes {
public:
    iTunes();
    ~iTunes();
    void playPause();
    void nextSong();
    void prevSong();
    void initializeCOM();
    void finalizeCOM();
    wstring getCurrentTrackInfo();
private:
    IDispatch* iTunesApp = nullptr;
    IDispatch* pCurrentTrack = nullptr;
    HRESULT hr;
    TrackInfo currentTrack;
    IDispatch* getCurrentTrackCOMObject();
    TrackInfo getTrackInfo();
};

extern iTunes myiTunes;
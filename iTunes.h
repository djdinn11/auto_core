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
    void play_pause();
    void next_song();
    void prev_song();
    void initialize_COM();
    void finalize_COM();
    wstring get_current_track();
private:
    IDispatch* iTunesApp = nullptr;
    IDispatch* pCurrentTrack = nullptr;
    HRESULT hr;
    TrackInfo currentTrack;
    IDispatch* getCurrentTrackCOMObject();
    TrackInfo getTrackInfo();
    bool initialized;
};

extern iTunes ac_iTunes;
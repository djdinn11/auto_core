#include "sp_thread.h"
#include "clock.h"
#include "logger_c.h"

mutex sp_mtx;
condition_variable sp_cv;
bool sp_playback_state_change;

const int sleep_timerate_ms = 15000;
const int speed_boost_ms = 5000;
const int speed_boost_code = 15;
const int extra_time = 1500;
const int processing_delay = 450;

void start_sp_song_thread() {
    thread t(sp_song_thread);
    t.detach();
}

/*! \runtime */
void spotify_next_song() {
    ac_spotify.next_song();
    sp_playback_state_change = true;
    sp_cv.notify_one();
}

void sp_song_thread() {
    sp_logger.logg_and_logg("sp_thread started");
    try {
        unique_lock<mutex> lock(sp_mtx);
        int sleep_time_ms;
        ac_spotify.get_current_song();
        if (ac_spotify.remaining_song_duration_ms == 0) {
            ac_spotify.remaining_song_duration_ms = sleep_timerate_ms;
        }
        while (true) {
            sp_playback_state_change = false;
            if (!ac_spotify.is_playing) {
                sp_logger.loggnl("Spotify not playing - ");
                sleep_time_ms = sleep_timerate_ms;
            }
            else if (ac_spotify.last_status_code == speed_boost_code) {
                sp_logger.logg_and_print("speed boost!");
                sleep_time_ms = speed_boost_ms;
            }
            else if (ac_spotify.remaining_song_duration_ms < sleep_timerate_ms) {
                sleep_time_ms = ac_spotify.remaining_song_duration_ms + extra_time;
            }
            else {
                sleep_time_ms = sleep_timerate_ms;
            }
            sp_logger.logg("sleep time {} seconds at {}", sleep_time_ms / 1000, get_timestamp_with_seconds());
            if (sp_cv.wait_for(lock, chrono::milliseconds(sleep_time_ms), [] {return sp_playback_state_change;})) {
                sp_logger.logg("sp_playback_state_change at {}", get_timestamp_with_seconds());
                Sleep(processing_delay);
            }
            ac_spotify.get_current_song();
        }
    }
    catch (const exception& e) {
        sp_logger.logg_and_print("sp_song_thread() has crashed: {}", e.what());
    }
    catch (...) {
        sp_logger.logg_and_print("sp_song_thread() has crashed due to an unknown exception");
    }
}
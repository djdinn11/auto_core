#include <itunes_t.h>

mutex iT_mtx;
condition_variable iT_cv;
bool iT_playback_state_change;

void iTunes_next_song() {
    logg("iTunes_next_song()");
    ac_iTunes.next_song();
    iT_playback_state_change = true;
    iT_cv.notify_one();
}
void iTunes::start_iTunes_thread() {
    Sleep(250);
    logg("iTunes_thread started");
    const int sleep_timerate_secs = 15;
    const int extra_time_ms = 100;
    const int processing_delay_ms = 252;
    try {
        unique_lock<mutex> lock(iT_mtx);
        int sleep_time_secs;
        while (true) {
            iT_playback_state_change = false;
            if (ac_iTunes.initialized) {
                ac_iTunes.get_current_track();
            }
            else {
                ac_iTunes.remaining_song_duration = -1;
            }
            if (ac_iTunes.remaining_song_duration > sleep_timerate_secs) {
                sleep_time_secs = sleep_timerate_secs;
            }
            else if (ac_iTunes.remaining_song_duration == -1) {
                sleep_time_secs = sleep_timerate_secs;
            }
            else if (ac_iTunes.remaining_song_duration < sleep_timerate_secs) {
                sleep_time_secs = ac_iTunes.remaining_song_duration;
                Sleep(extra_time_ms);
            }
            else {
                sleep_time_secs = sleep_timerate_secs;
            }
            logg("iTunes sleep time {} seconds at {}", sleep_time_secs, get_timestamp_with_seconds());
            if (iT_cv.wait_for(lock, chrono::seconds(sleep_time_secs), [] {return iT_playback_state_change; })) {
                if (ac_iTunes.end_thread) {
                    break;
                }
                logg("iT_playback_state_change at {}", get_timestamp_with_seconds());
                Sleep(processing_delay_ms);
            }
        }
    }
    catch (const exception& e) {
        print("iTunes_song_thread() has crashed: {}", e.what());
    }
    catch (...) {
        print("iTunes_song_thread() has crashed due to an unknown exception");
    }
    logg("end of iTunes thread");
}
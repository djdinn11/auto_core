/*!
\file sp.ixx
\brief Integrates Spotify functionality within Auto Core, providing music player automation and control.
*/
export module sp;
import base;
import pipes;
import <Windows.h>;

export HANDLE ac_sp_pipe;

export {
    void start_sp_component();
    void get_user_sp_queue();
    void print_spotify_songs();
    void spotify_play_pause();
    void spotify_prev_song();
    void sp_switch_player();
    void download_album_cover();
    void spotify_next_song();
    void send_sp_end_signal();
    void update_sp_logger();
}

void start_sp_component() {
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));
    TCHAR app_name[] = TEXT(R"(.\core\sp\sp_ac.exe)");
    if (!CreateProcess(app_name, NULL, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi)) {
        cerr << "CreateProcess failed (" << GetLastError() << ").\n";
    }
    else {
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    }
}

/*! \runtime */
void get_user_sp_queue() {
    send_pipe_command(ac_sp_pipe, 4);
}

/*! \runtime */
void print_spotify_songs() {
    send_pipe_command(ac_sp_pipe, 3);
}

/*! \runtime */
void spotify_play_pause() {
    send_pipe_command(ac_sp_pipe, 1);
}

/*! \runtime */
void spotify_next_song() {
    send_pipe_command(ac_sp_pipe, 2);
}

/*! \runtime */
void sp_switch_player() {
    send_pipe_command(ac_sp_pipe, 6);
}
void download_album_cover() {
    send_pipe_command(ac_sp_pipe, 8);
}

void send_sp_end_signal() {
    send_pipe_command(ac_sp_pipe, 0);
}

void update_sp_logger() {
    send_pipe_command(ac_sp_pipe, 5);
}
/*!
\file itunes.ixx
\brief This module provides support for music player intregation with iTunes.
*/
export module itunes;
import visual;
import pipes;
import <Windows.h>;

export bool iTunes_component_started;
export HANDLE ac_itunes_pipe;

export {
    void start_iTunes_component();
    void print_iTunes_songs();
    void print_next_up_song_list();
    void iTunes_play_pause();
    void iTunes_prev_song();
    void iTunes_next_song();
    void update_iTunes_logger();
    void send_iTunes_end_signal();
    void remove_iTunes_song();
}

/*!
* \brief Starts the iTunes component.
*/
void start_iTunes_component() {
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));
    TCHAR app_name[] = TEXT(R"(.\core\itunes\ac_itunes.exe)");
    if (!CreateProcess(app_name, NULL, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi)) {
        print("CreateProcess failed ({})", GetLastError());
    }
    else {
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    }
    iTunes_component_started = true;
}

/** \runtime */
void print_iTunes_songs() {
    send_pipe_command(ac_itunes_pipe, 3);
}
/** \runtime */
void iTunes_next_song() {
    send_pipe_command(ac_itunes_pipe, 2);
}
/** \runtime */
void print_next_up_song_list() {
    send_pipe_command(ac_itunes_pipe, 4);
}
/** \runtime */
void iTunes_play_pause() {
    send_pipe_command(ac_itunes_pipe, 1);
}

void iTunes_prev_song() {
    send_pipe_command(ac_itunes_pipe, 6);
}

void update_iTunes_logger() {
    send_pipe_command(ac_itunes_pipe, 5);
}

void send_iTunes_end_signal() {
    send_pipe_command(ac_itunes_pipe, 0);
}
/** \runtime */
void remove_iTunes_song() {
    send_pipe_command(ac_itunes_pipe, 9);
}
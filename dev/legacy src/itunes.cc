#include <itunes.h>
#include <pipes.h>

bool iTunes_component_started;
HANDLE ac_itunes_pipe;

/*!
* \brief Stars the iTunes component.
* \todo Run tests on whether iTunes is open. The default is that iTunes is already running. This regards taskbar.cc.
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

/*!
* \brief Stars the iTunes component.
* \todo Run tests on whether iTunes is open. The default is that iTunes is already running. This regards taskbar.cc.
*/

//// Function to start the iTunes component
//void start_iTunes_component() {
//    STARTUPINFO si;
//    ZeroMemory(&si, sizeof(si));
//    si.cb = sizeof(si);
//    ZeroMemory(&pi_iTunes, sizeof(pi_iTunes));
//    TCHAR app_name[] = TEXT(R"(.\core\itunes\ac_itunes.exe)");
//    if (!CreateProcess(app_name, NULL, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi_iTunes)) {
//        print("CreateProcess failed ({})", GetLastError());
//        iTunes_component_started =  false;
//    }
//    iTunes_component_started =  true;
//}
//
//// Function to forcefully terminate the iTunes component
//void stop_iTunes_component() {
//    if (TerminateProcess(pi_iTunes.hProcess, 0)) {
//        print("iTunes process terminated successfully");
//    }
//    else {
//        print("Failed to terminate iTunes process ({})", GetLastError());
//    }
//    CloseHandle(pi_iTunes.hProcess);
//    CloseHandle(pi_iTunes.hThread);
//}

/** \runtime */
//void print_iTunes_songs() {
//    send_pipe_command(ac_itunes_pipe, 3);
//}
///** \runtime */
//void iTunes_next_song() {
//    send_pipe_command(ac_itunes_pipe, 2);
//}
///** \runtime */
//void print_next_up_song_list() {
//    send_pipe_command(ac_itunes_pipe, 4);
//}
///** \runtime */
//void iTunes_play_pause() {
//    send_pipe_command(ac_itunes_pipe, 1);
//}
//
//void iTunes_prev_song() {
//    send_pipe_command(ac_itunes_pipe, 6);
//}
//
//void update_iTunes_logger() {
//    send_pipe_command(ac_itunes_pipe, 5);
//}
//
//void send_iTunes_end_signal() {
//    send_pipe_command(ac_itunes_pipe, 0);
//    stop_iTunes_component();
//}
///** \runtime */
//void remove_iTunes_song() {
//    send_pipe_command(ac_itunes_pipe, 9);
//}
#include <base.h>
#include <logger_t.h>
#include <visual.h>
#include <pipes.h>
#include <itunes.h>
#include <itunes_t.h>
#include <slash_i.h>

void set_command_map() {
    command_map[0] = {[]() {iTunes_logger.logg("iTunes is shutting down"); end_process = true; }};
    command_map[1] = {iTunes_play_pause};
    command_map[2] = {iTunes_next_song};
    command_map[3] = {print_iTunes_songs};
    command_map[4] = {print_next_up_song_list};
    command_map[5] = {update_iTunes_logger};
    command_map[6] = {iTunes_prev_song};
    command_map[9] = {remove_iTunes_song};
}

int main() {
    log_init();
    print("ac_itunes.exe");
    set_command_map();
    HANDLE ac_itunes_pipe = connect_to_pipe_server(L"ac_itunes_pipe"); 
    if (ac_itunes_pipe != NULL) {
        process_pipe_commands(ac_itunes_pipe);
    }
    else {
        print("Failed to connect to pipe server.");
    }
    ac_iTunes.finalize_com();
    iTunes_logger.logg_and_logg("ac_itunes.exe has ended");
    CloseHandle(ac_itunes_pipe);
    return 0;
}

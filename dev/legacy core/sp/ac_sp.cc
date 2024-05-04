#include <visual.h>
#include <logger_t.h>
#include <sp.h>
#include <sp_thread.h>
#include <pipes.h>

void set_command_map() {
    command_map[0] = {[]() { sp_logger.logg("Spotify is shutting down"); end_process = true; }};
    command_map[1] = {spotify_play_pause};
    command_map[2] = {spotify_next_song};
    command_map[3] = {print_spotify_songs};
    command_map[4] = {get_user_sp_queue};
    command_map[5] = {update_sp_logger};
    command_map[6] = {sp_switch_player};
    command_map[8] = {download_album_cover};
}
    
int main() {
    log_init();
    print("sp_ac.exe");
    set_command_map();
    start_sp_song_thread();
    HANDLE ac_sp_pipe = connect_to_pipe_server(L"ac_sp_pipe"); // Ensure this function sets up the pipe correctly
    if (ac_sp_pipe != NULL) {
        process_pipe_commands(ac_sp_pipe);
    }
    else {
        print("Failed to connect to pipe server.");
    }
    sp_logger.logg_and_logg("sp_ac.exe has ended");
    CloseHandle(ac_sp_pipe);
    return 0;
}

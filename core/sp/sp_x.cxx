import visual;
import sp_c;
import sp_t;
import sp_x;
import pipes;
import <Windows.h>;

wstring pipe_name = L"ac_sp_pipe";

void end_sp() {
    sp_logger.logg("Spotify is shutting down");
    ac_spotify.end_thread = true;
    sp_playback_state_change = true;
    sp_cv.notify_one();
    end_process = true;
}

void set_command_map() {
    command_map[0] = {[]() {  end_sp(); }};
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
    set_command_map();
    start_sp_song_thread();
    HANDLE ac_sp_pipe = connect_to_pipe_server(pipe_name);
    if (ac_sp_pipe != NULL) {
        sp_logger.logg("connected to pipe '{}' server", wstr_to_str(pipe_name));
        process_pipe_commands(ac_sp_pipe);
    }
    else {
        sp_logger.logg_and_print("Failed to connect to pipe server.");
    }
    sp_logger.logg_and_logg("sp_ac.exe has ended");
    sp_logger.close_log_file();
    CloseHandle(ac_sp_pipe);
    close_main_log_file();
    return 0;
}

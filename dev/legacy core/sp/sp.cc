#include <sp.h>
#include <logger_t.h>
#include <keyboard.h>
#include <thread.h>
#include <utils.h>

Spotify ac_spotify;
HWND spotify_window_hwnd;

json parse(const string& s) {
    return json::parse(s);
}
BOOL CALLBACK enum_spotify_premium_window(HWND hwnd, LPARAM lParam) {
    const size_t max_length = 15;
    const int length = GetWindowTextLength(hwnd);
    if (length != max_length) {
        return TRUE;
    }
    wstring window_title(length, L'\0');
    if (!GetWindowTextW(hwnd, &window_title[0], length + 1)) {
        return TRUE;
    }
    if (window_title == L"Spotify Premium") {
        *reinterpret_cast<bool*>(lParam) = true;
        sp_logger.logg_and_print("spotify window found");
        spotify_window_hwnd = hwnd;
        return FALSE;
    }
    return TRUE;
}
Spotify::Spotify() {
    timerate = 55;
    start_stamp = 0;
    get_sp_position();
    tokens_path = R"(.\star\sp_tokens.rc)";
    devices_path = R"(.\star\sp_devices.rc)";
    codes_path = R"(.\star\sp_codes.rc)";
    content_type = "Content-Type: application/json";
    content_length = "Content-Length: 0";
}
void Spotify::get_sp_position() {
    ifstream taskbar_config_file(R"(.\config\taskbar.ini)");
    string line;
    while (getline(taskbar_config_file, line)) {
        size_t found_spotify = line.find("spotify");
        if (found_spotify != string::npos) {
            sp_position = stoi(line.substr(0, 1));
            break;
        }
    }
}
void Spotify::activate() {
    send_winkey(sp_position);
}
void Spotify::get_devices() {
    ifstream rc(devices_path);
    getline(rc, desktop_device_id);
    getline(rc, mobile_device_id);
    rc.close();
}
void Spotify::update_devices() {
    string url = "https://api.spotify.com/v1/me/player/devices";
    auto response = Get(
        Url {url},
        Header {{authorization_header, content_type}}
    );
    bool device_id_changed = false;
    auto devices = parse(response.text);
    for (const auto& device : devices["devices"]) {
        if (device["name"] == "DESKTOP-DNP5C1N" && desktop_device_id != device["id"]) {
            desktop_device_id = device["id"];
            device_id_changed = true;
        }
        else if (device["name"] == "iPhone" && mobile_device_id != device["id"]) {
            mobile_device_id = device["id"];
            device_id_changed = true;
        }
    }
    if (device_id_changed) {
        ofstream rc(devices_path);
        if (rc.is_open()) {
            oss os;
            os << desktop_device_id << "\n"
                << mobile_device_id;
            rc << os.str();
            rc.close();
        }
    }
}
void Spotify::get_credentials() {
    ifstream rc(codes_path);
    getline(rc, client_id);
    getline(rc, client_secret);
    string credentials = client_id + ":" + client_secret;
    credentials_64 = base64_encode(credentials);
    rc.close();
}
void Spotify::extract_tokens() {
    get_credentials();
    get_devices();
    ifstream rc(tokens_path);
    getline(rc, access_token);
    getline(rc, refresh_token);
    string time_str;
    getline(rc, time_str);
    start_stamp = stoi(time_str);
    rc.close();
}
bool Spotify::check_timerate() {
    minutes_stamp = get_minutes_stamp();
    if (minutes_stamp - start_stamp >= timerate) {
        return true;
    }
    else if (minutes_stamp - start_stamp > 0) {
        return false;
    }
    else if ((minutes_stamp + 1440) - start_stamp < timerate) {
        return false;
    }
    else {
        return true;
    }
}
bool Spotify::refresh_tokens() {
    if (access_token.empty()) {
        extract_tokens();
    }
    if (!check_timerate()) {
        authorization_header = "Authorization: Bearer " + access_token;
        return true;
    }
    start_stamp = minutes_stamp - 1;
    Response response = Post(Url {"https://accounts.spotify.com/api/token"},
        Header {{"Content-Type", "application/x-www-form-urlencoded"},
                    {"Authorization", "Basic " + credentials_64}},
        Payload {{"grant_type", "refresh_token"},
                     {"refresh_token", refresh_token}});
    if (response.status_code == 200) {
        auto response_json = parse(response.text);
        if (response_json.contains("access_token")) {
            access_token = response_json["access_token"];
            ofstream rc(tokens_path);
            if (rc.is_open()) {
                oss os;
                os << access_token << "\n"
                    << refresh_token << "\n"
                    << to_string(start_stamp);
                rc << os.str();
                rc.close();
            }
        }
        authorization_header = "Authorization: Bearer " + access_token;
        sp_logger.logg_and_logg("refresh_tokens() - tokens refreshed");
        return true;
    }
    else if (response.status_code == 429) {
        sp_logger.logg_and_print("Error: Rate Limit Reached\nStatus Code {} - {}", response.status_code, response.text);
        return false;
    }
    else {
        sp_logger.logg_and_print("Error: \nStatus Code {} - {}", response.status_code, response.text);
        return false;
    }
}
void Spotify::get_current_song() {
    if (!refresh_tokens()) {
        return;
    }
    string url = "https://api.spotify.com/v1/me/player/currently-playing";
    auto response = Get(
        Url {url},
        Header {{authorization_header, content_type}}
    );
    last_status_code = 1;
    if (response.status_code != 200) {
        if (response.status_code == 204) {
            is_playing = false;
        }
        return;
    }
    auto song_details = parse(response.text);
    is_playing = song_details["is_playing"];
    if (!song_details["item"].contains("name")) {
        sp_logger.logg_and_logg("djai++ is talking");
        last_status_code = 15;
        return;
    }
    string current_song = format_song_title(song_details["item"]);
    calculate_remaining_song_duration_ms(song_details);
    if (current_song == last_song) {
        return;
    }
    sp_logger.loggnl_and_loggnl("now playing: ");
    sp_logger.logg_and_print(current_song);
    last_song = current_song;
    song_history.push_back(current_song);
    return;
}
void Spotify::calculate_remaining_song_duration_ms(const json& song_details) {
    int progress_ms = song_details["progress_ms"];
    int duration_ms = song_details["item"]["duration_ms"];
    remaining_song_duration_ms = duration_ms - progress_ms;
}
string Spotify::format_artist_name(const json& artists) {
    string artist {};
    if (artists.size() == 1) {
        artist = artists[0]["name"];
    }
    else {
        for (size_t i = 0; i < artists.size(); ++i) {
            artist += artists[i]["name"];
            if (i < artists.size() - 1) {
                artist += ", ";
            }
        }
    }
    return artist;
}
string Spotify::format_song_title(const json& song_details) {
    const string name = song_details["name"];
    const string artist = format_artist_name(song_details["artists"]);
    const string album = song_details["album"]["name"];
    int duration = song_details["duration_ms"] / 1000;
    oss output;
    oss dur;
    dur << duration / 60 << ":" << setw(2) << setfill('0') << duration % 60;
    output << '[' << name << "] [" << artist << "] [" << album << "] [" << dur.str() << ']';
    return output.str();
}
string Spotify::get_user_queue() {
    try {
        if (!refresh_tokens()) {
            return "Unable to refresh tokens";
        }
        string url = "https://api.spotify.com/v1/me/player/queue";
        auto response = Get(
            Url {url},
            Header {{authorization_header, content_type}}
        );
        if (response.status_code != 200) {
            sp_logger.logg_and_print("Failed to retrieve queue");
            return "";
        }
        json queue_details = parse(response.text);
        oss output;
        string current_song;
        if (!queue_details["currently_playing"].is_null()) {
            current_song = format_song_title(queue_details["currently_playing"]);
            song_history_contains(current_song);
        }
        for (const auto& item : queue_details["queue"]) {
            string song = format_song_title(item);
            if (!song_history_contains(song)) {
                output << song << '\n';
            }
        }
        output << current_song;
        return output.str();
    }
    catch (...) {
        sp_logger.logg_and_print("An exception occurred in get_user_queue");
        return "";
    }
}
bool Spotify::download_album_cover() {
    if (!refresh_tokens()) {
        return false;
    }
    string url = "https://api.spotify.com/v1/me/player/currently-playing";
    auto response = Get(
        Url {url},
        Header {{authorization_header, content_type}}
    );
    if (response.status_code != 200) {
        sp_logger.logg_and_print("Failed to retrieve song");
        return "";
    }
    auto song_details = parse(response.text);
    string album_cover_url;
    if (!song_details["item"]["album"]["images"].empty()) {
        album_cover_url = song_details["item"]["album"]["images"][0]["url"].get<string>();
    }
    else {
        return false;
    }
    auto album_response = Get(Url {album_cover_url});
    string filepath = "cover.jpg";
    if (album_response.status_code == 200) {
        ofstream file(filepath, ios::binary);
        file.write(album_response.text.c_str(), album_response.text.size());
        file.close();
        return true;
    }
    else {
        return false;
    }
}
int Spotify::pause_song() {
    if (!refresh_tokens()) {
        return 429;
    }
    auto response = Put(
        Url {"https://api.spotify.com/v1/me/player/pause"},
        Header {
            {"Authorization", "Bearer " + access_token},
            {"Content-Type", "application/json"},
            {"Content-Length", "0"}
        });
    if (response.status_code != 204) {
        sp_logger.logg_and_print("Error: Status Code {} - {}", response.status_code, response.text);
    }
    return response.status_code;
}
void Spotify::transfer_playback(string device_id) {
    if (!refresh_tokens()) {
        return;
    }
    string url = "https://api.spotify.com/v1/me/player";
    string body = format(R"({{"device_ids": ["{}"], "play": true}})", device_id);
    auto response = Put(
        Url {url},
        Header {{authorization_header, content_type}},
        Body {body}
    );
    if (response.status_code != 204) {
        sp_logger.logg_and_print("Error: Status Code {} - {}", response.status_code, response.text);
    }
}
void Spotify::start_playback_on_desktop() {
    transfer_playback(desktop_device_id);
}
void Spotify::start_playback_on_mobile() {
    transfer_playback(mobile_device_id);
}
void Spotify::switch_player() {
    if (!refresh_tokens()) {
        return;
    }
    update_devices();
    string url = "https://api.spotify.com/v1/me/player";
    auto response = Get(
        Url {url},
        Header {{authorization_header, content_type}}
    );
    if (response.status_code == 204) {
        play_pause();
        return;
    }
    if (response.status_code != 200) {
        sp_logger.logg_and_print("Error: Status Code {} - {}", response.status_code, response.text);
        return;
    }
    auto playback_details = parse(response.text);
    string current_device_id = playback_details["device"]["id"];
    if (current_device_id == desktop_device_id) {
        start_playback_on_mobile();
    }
    else if (current_device_id == mobile_device_id) {
        start_playback_on_desktop();
    }
    else {
        sp_logger.logg_and_print("Device not added");
    }
}
int Spotify::play_song() {
    if (!refresh_tokens()) {
        return 429;
    }
    auto response = Put(
        Url {"https://api.spotify.com/v1/me/player/play"},
        Header {
            {"Authorization", "Bearer " + access_token},
            {"Content-Type", "application/json"},
            {"Content-Length", "0"},
        }
    );
    if (response.status_code == 404) {
        sp_logger.logg_and_print("no active device");
    }
    else if (response.status_code != 204) {
        sp_logger.logg_and_print("Error: Status Code {} - {}", response.status_code, response.text);
    }
    return response.status_code;
}
bool Spotify::is_spotify_open() {
    bool spotifyWindowFound = false;
    EnumWindows(enum_spotify_premium_window, reinterpret_cast<LPARAM>(&spotifyWindowFound));
    return spotifyWindowFound;
}
bool Spotify::is_spotify_playing() {
    if (!refresh_tokens()) {
        return false;
    }
    string url = "https://api.spotify.com/v1/me/player/currently-playing";
    auto response = Get(
        Url {url},
        Header {{authorization_header, content_type}}
    );
    if (response.status_code != 200) {
        return false;
    }
    auto playback_details = parse(response.text);
    if (!playback_details.contains("is_playing")) {
        return false;
    }
    bool is_playing = playback_details["is_playing"];
    return is_playing;
}
void start_playback_sp_thread() {
    ac_spotify.activate();
    int total_sleep_time {};
    int sleep_duration = 500;
    int time_limit_ms = 10000;
    int processing_delay = 1500;
    while (!ac_spotify.is_spotify_open() && total_sleep_time < time_limit_ms) {
        this_thread::sleep_for(chrono::milliseconds(sleep_duration));
        total_sleep_time += sleep_duration;
    }
    this_thread::sleep_for(chrono::milliseconds(processing_delay));
    ac_spotify.start_playback_on_desktop();
}
void Spotify::play_pause() {
    if (!refresh_tokens()) {
        sp_logger.logg_and_print("tokens not refreshed in Spotify::play_pause()");
        return;
    }
    if (is_spotify_playing()) {
        sp_logger.logg_and_logg("is_spotify_playing() == true");
        pause_song();
        return;
    }
    if (play_song() == 204) {
        sp_logger.logg_and_logg("play_song() == 204");
        return;
    }
    if (is_spotify_open()) {
        sp_logger.logg_and_logg("is_spotify_open() == true");
        start_playback_on_desktop();
    }
    else {
        sp_logger.logg_and_logg("starting Spotify");
        thread t(start_playback_sp_thread);
        t.detach();
    }
}
void Spotify::post_next_or_prev(string url) {
    if (!refresh_tokens()) {
        return;
    }
    auto response = Post(
        Url {url},
        Header {{authorization_header, content_type}}
    );
    if (response.status_code != 204) {
        sp_logger.logg_and_print("post_next_or_prev() - Error: Status Code {} - {}", response.status_code, response.text);
    }
}
void Spotify::next_song() {
    string url = "https://api.spotify.com/v1/me/player/next";
    post_next_or_prev(url);
}
void Spotify::prev_song() {
    string url = "https://api.spotify.com/v1/me/player/previous";
    post_next_or_prev(url);
}
bool Spotify::song_history_contains(string current_song) {
    for (const auto& song : song_history_array) {
        if (song == current_song) {
            return true;
        }
    }
    song_history_array[song_history_index] = current_song;
    song_history_index += 1;
    if (song_history_index == string_array_size) {
        song_history_index = 0;
    }
    return false;
}
bool get_user_queue_thread_started = false;
void get_user_sp_queue_thread() {
    string user_queue = ac_spotify.get_user_queue();
    sp_logger.logg_and_print(user_queue);
    set_clipboard_text(str_to_wstr(user_queue) + L"\n\n");
    Sleep(50);
    paste_from_clipboard();
    get_user_queue_thread_started = false;
}

/** \runtime */
void get_user_sp_queue() {
    sp_logger.logg_and_logg("get_user_sp_queue()");
    if (!get_user_queue_thread_started) {
        get_user_queue_thread_started = true;
        thread t([=]() {run_with_exception_handling(get_user_sp_queue_thread); });
        t.detach();
    }
}

/** \runtime */
void print_spotify_songs() {
    sp_logger.logg_and_logg("print_spotify_songs()");
    oss song_text;
    ac_spotify.get_current_song();
    if (!ac_spotify.song_history.empty()) {
        for (const auto& song : ac_spotify.song_history) {
            if (song != ac_spotify.last_song) {
                song_text << song << '\n';
            }
        }
        ac_spotify.song_history.clear();
    }
    song_text << ac_spotify.last_song << '\n';
    string song_text_str = song_text.str();
    sp_logger.loggnl_and_printnl(song_text_str);
    set_clipboard_text(str_to_wstr(song_text_str) + L"\n");
    Sleep(50);
    paste_from_clipboard();
}
void spotify_play_pause_thread() {
    ac_spotify.play_pause();
}

/** \runtime */
void spotify_play_pause() {
    sp_logger.logg_and_logg("spotify_play_pause()");
    thread t(spotify_play_pause_thread);
    t.detach();
}

void spotify_prev_song() {
    ac_spotify.prev_song();
}

/** \runtime */
void sp_switch_player() {
    sp_logger.logg_and_logg("sp_switch_player()");
    ac_spotify.switch_player();
}
void download_album_cover() {
    ac_spotify.download_album_cover();
}
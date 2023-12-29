#include <Spotify.h>
#include <nlohmann/json.hpp>
#include <cpr/cpr.h>
#include <clock.h>

string sp_path_tokens = R"(C:\DJ\My Folder\Auto Core\sp_tokens.rc)";

using json = nlohmann::json;
using namespace std;
using namespace cpr;

json parse(const string& s) {
    return json::parse(s);
}
Spotify::Spotify() {
    timerate = 55;
    start_stamp = 0;
}

void Spotify::ExtractTokens() {
    ifstream rc(sp_path_tokens);
    if (!rc.is_open()) {
        cerr << "Unable to open the file." << endl;
        return;
    }
    getline(rc, access_token);
    getline(rc, refresh_token);
    string time_str;
    getline(rc, time_str);
    start_stamp = stoi(time_str);
    getline(rc, client_id);
    getline(rc, client_secret);
    rc.close();
    credentials = client_id + ":" + client_secret;
    credentials_64 = base64_encode(credentials);
}
bool Spotify::CheckTimerate() {
    set_minutes_stamp();
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
void Spotify::RefreshTokens() {
    if (access_token.empty()) {
        ExtractTokens();
    }
    if (!CheckTimerate()) {
        return;
    }
    start_stamp = minutes_stamp - 1;
    Response r = Post(Url{ "https://accounts.spotify.com/api/token" },
        Header{ {"Content-Type", "application/x-www-form-urlencoded"},
                    {"Authorization", "Basic " + credentials_64} },
        Payload{ {"grant_type", "refresh_token"},
                     {"refresh_token", refresh_token} });
    if (r.status_code == 200) {
        auto response_json = parse(r.text);
        if (response_json.contains("access_token")) {
            access_token = response_json["access_token"];
            ofstream rc(sp_path_tokens);
            if (rc.is_open()) {
                oss os;
                os << access_token << "\n"
                    << refresh_token << "\n"
                    << to_string(start_stamp) << "\n"
                    << client_id << "\n"
                    << client_secret;
                rc << os.str();
                rc.close();
            }
        }
    }
}
string Spotify::get_current_song() {
    RefreshTokens();
    auto response = Get(
        Url{ "https://api.spotify.com/v1/me/player/currently-playing" },
        Header{ {"Authorization", "Bearer " + access_token} }
    );
    if (response.status_code != 200) {
        cerr << "Failed to retrieve song" << endl;
        return "";
    }
    auto song_details = parse(response.text);
    string song_name = song_details["item"]["name"].get<string>();
    auto artists = song_details["item"]["artists"];
    string artist_name;
    if (artists.size() == 1) {
        artist_name = artists[0]["name"].get<string>();
    }
    else {
        artist_name = "";
        for (size_t i = 0; i < artists.size(); ++i) {
            artist_name += artists[i]["name"].get<string>();
            if (i < artists.size() - 1) {
                artist_name += ", ";
            }
        }
    }
    string album_name = song_details["item"]["album"]["name"].get<string>();
    int duration = song_details["item"]["duration_ms"].get<int>() / 1000; // retrieved in milliseconds
    ss s;
    s << "[" << song_name << "] [" << artist_name << "] [" << album_name << "] [" << duration << " secs]";
    string current_song = s.str();
    if (current_song == last_song) {
        return "";
    }
    last_song = current_song;
    return current_song;
}
bool Spotify::download_album_cover() {
    RefreshTokens();
    auto response = Get(
        Url{"https://api.spotify.com/v1/me/player/currently-playing"},
        Header{{"Authorization", "Bearer " + access_token}}
    );
    if (response.status_code != 200) {
        cerr << "Failed to retrieve song" << endl;
        return "";
    }
    auto song_details = parse(response.text);
    string album_cover_url;
    if (!song_details["item"]["album"]["images"].empty()) {
        album_cover_url = song_details["item"]["album"]["images"][0]["url"].get<string>();
    }
    else {
        album_cover_url = "No cover available";
    }
    auto album_response = Get(Url{album_cover_url});
    string filepath = "cover.jpg";
    if (album_response.status_code == 200) {
        ofstream file(filepath, ios::binary);
        file.write(album_response.text.c_str(), album_response.text.size());
        file.close();
        return true;
    }
    else {
        cerr << "Failed to download the image: Status code " << album_response.status_code << endl;
        return false;
    }
}
void Spotify::GetUserPlaylists() {
    RefreshTokens();
    auto response = Get(
        Url{ "https://api.spotify.com/v1/me/playlists" },
        Header{ {"Authorization", "Bearer " + access_token} }
    );
    if (response.status_code != 200) {
        cerr << "Failed to retrieve playlists: " << response.text << endl;
        return;
    }
    auto playlists_json = parse(response.text);
    for (const auto& playlist : playlists_json["items"]) {
        cout << "Playlist Name: " << playlist["name"] << endl;
        cout << "Playlist ID: " << playlist["id"] << "\n" << endl;
    }
}
int Spotify::Pause() {
    RefreshTokens();
    auto response = Put(
        Url{ "https://api.spotify.com/v1/me/player/pause" },
        Header{
            {"Authorization", "Bearer " + access_token},
            {"Content-Type", "application/json"},
            {"Content-Length", "0"}
        });
    return response.status_code;
}
int Spotify::Play() {
    RefreshTokens();
    auto response = Put(
        Url{ "https://api.spotify.com/v1/me/player/play" },
        Header{
            {"Authorization", "Bearer " + access_token},
            {"Content-Type", "application/json"},
            {"Content-Length", "0"}  // Add this line
        }
    );
    return response.status_code;
}
void Spotify::play_pause() {
    int status = Pause();
    if (status == 403) {
        status = Play();
    }
    else if (status != 204) {
        cerr << "Failed to play/pause song: " << endl;
    }
}
void Spotify::next_song() {
    RefreshTokens();
    auto response = Post(
        Url{ "https://api.spotify.com/v1/me/player/next" },
        Header{ {"Authorization", "Bearer " + access_token} }
    );
    if (response.status_code != 204) {
        cerr << "Failed to go to next song: " << response.text << endl;
    }
}
void Spotify::prev_song() {
    RefreshTokens();
    auto response = Post(
        Url{ "https://api.spotify.com/v1/me/player/previous" },
        Header{ {"Authorization", "Bearer " + access_token} }
    );
    if (response.status_code != 204) {
        cerr << "Failed to go to previous song: " << response.text << endl;
    }
}
void print_Spotify_song() {
    string song = ac_Spotify.get_current_song();
    if (song.empty()) {
        set_clipboard_text(L"\n\n");
        simulate_paste();
        return;
    }
    song += "\n";
    print(song);
    wss ws;
    ws << Utf8ToUtf16(song).c_str() << L"\n";
    set_clipboard_text(ws.str());
    Sleep(50);
    simulate_paste();
}
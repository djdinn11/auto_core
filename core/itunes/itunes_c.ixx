export module itunes;
import visual;
import itunes_x;
import <Windows.h>;
import <comdef.h>;
import <atlbase.h>;

struct TrackInfo {
    wstring name;
    wstring artist;
    wstring album;
    int duration;
    wstring location;
};
export class iTunes {
public:
    iTunes();
    ~iTunes();
    void play_pause();
    void next_song();
    void prev_song();
    void initialize_com();
    void finalize_com();
    vector<wstring> song_history;
    wstring last_retrieved_song;
    wstring get_current_track();
    TrackInfo current_track;
    bool initialized;
    bool is_playing();
    wstring track_location;
    HRESULT hr;
    CComPtr<IDispatch> iTunes_app = nullptr;
    CComPtr<IDispatch> p_current_track = nullptr;
    CComPtr<IDispatch> get_current_track_com_object();
    TrackInfo get_track_info();
    int get_current_playback_position();
    int remaining_song_duration;
    bool end_thread;
    thread iTunes_thread;
    void start_iTunes_thread();
    void remove_track();
    void recycle_bin_track();
    void delete_track();
};

export iTunes ac_iTunes;
export mutex iT_mtx;
export condition_variable iT_cv;
export bool iT_playback_state_change;

export {
    void print_iTunes_songs();
    void print_next_up_song_list();
    void iTunes_play_pause();
    void iTunes_prev_song();
    string replace_tabs_with_brackets(const string& input);
}

BOOL CALLBACK enum_iTunes_window(HWND hwnd, LPARAM lParam) {
    const size_t max_length = 6;
    const int length = GetWindowTextLength(hwnd);
    if (length != max_length) {
        return TRUE;
    }
    wstring window_title(length, L'\0');
    if (!GetWindowTextW(hwnd, &window_title[0], length + 1)) {
        return TRUE;
    }
    if (window_title == L"iTunes") {
        *reinterpret_cast<bool*>(lParam) = true;
        return FALSE;
    }
    return TRUE;
}
bool is_iTunes_open() {
    bool iTunes_window_found = false;
    EnumWindows(enum_iTunes_window, reinterpret_cast<LPARAM>(&iTunes_window_found));
    return iTunes_window_found;
}
bool iTunes::is_playing() {
    if (!initialized || iTunes_app == nullptr) {
        return false;
    }
    const OLECHAR* szPlayerState = L"PlayerState";
    BSTR bstrPlayerState = SysAllocString(szPlayerState);
    DISPID dispidPlayerState;
    hr = iTunes_app->GetIDsOfNames(IID_NULL, &bstrPlayerState, 1, LOCALE_USER_DEFAULT, &dispidPlayerState);
    SysFreeString(bstrPlayerState);
    if (FAILED(hr)) {
        return false;
    }
    DISPPARAMS dispparamsNoArgs = {NULL, NULL, 0, 0};
    VARIANT varResult;
    VariantInit(&varResult);
    hr = iTunes_app->Invoke(dispidPlayerState, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYGET, &dispparamsNoArgs, &varResult, NULL, NULL);
    if (FAILED(hr)) {
        return false;
    }
    bool is_playing = false;
    if (V_VT(&varResult) == VT_I4) {
        /* ITPlayerStateStopped = 0, ITPlayerStatePlaying = 1, ITPlayerStateFastForward = 2, ITPlayerStateRewind = 3 */
        is_playing = V_I4(&varResult) == 1;
    }
    VariantClear(&varResult);
    return is_playing;
}
iTunes::iTunes() {
    if (is_iTunes_open()) {
        initialize_com();
    }
}
iTunes::~iTunes() {
    finalize_com();
}
void iTunes::initialize_com() {
    if (initialized) {
        return;
    }
    hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);  // Change to STA
    if (FAILED(hr)) {
        return;
    }
    CLSID clsid;
    hr = CLSIDFromProgID(L"iTunes.Application", &clsid);
    if (FAILED(hr)) {
        CoUninitialize();
        return;
    }
    hr = CoCreateInstance(clsid, NULL, CLSCTX_LOCAL_SERVER, IID_IDispatch, (void**)&iTunes_app);
    if (FAILED(hr)) {
        CoUninitialize();
        return;
    }
    iTunes_thread = thread(&iTunes::start_iTunes_thread, this);
    iTunes_thread.detach();
    initialized = true;
}
void iTunes::finalize_com() {
    end_thread = true;
    iT_playback_state_change = true;
    iT_cv.notify_one();
    if (p_current_track != nullptr) {
        p_current_track = nullptr;
    }
    if (iTunes_app != nullptr) {
        iTunes_app = nullptr;
    }
    CoUninitialize();
    iTunes_logger.logg("end of iTunes::finalize_com()");
}
CComPtr<IDispatch> iTunes::get_current_track_com_object() {
    if (iTunes_app == nullptr) {
        return nullptr;
    }
    const OLECHAR* szMember = L"CurrentTrack";
    BSTR bstrMember = SysAllocString(szMember);
    if (!bstrMember) {
        return nullptr;
    }
    DISPID dispidCurrentTrack;
    hr = iTunes_app->GetIDsOfNames(IID_NULL, &bstrMember, 1, LOCALE_USER_DEFAULT, &dispidCurrentTrack);
    SysFreeString(bstrMember);
    if (FAILED(hr)) {
        return nullptr;
    }
    DISPPARAMS dispparamsNoArgs = {NULL, NULL, 0, 0};
    VARIANT varResult;
    VariantInit(&varResult);
    hr = iTunes_app->Invoke(dispidCurrentTrack, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYGET, &dispparamsNoArgs, &varResult, NULL, NULL);
    if (FAILED(hr)) {
        CoUninitialize();
        return nullptr;
    }
    if (V_VT(&varResult) != VT_DISPATCH || V_DISPATCH(&varResult) == NULL) {
        VariantClear(&varResult);
        return nullptr;
    }
    p_current_track = V_DISPATCH(&varResult);
    const OLECHAR* szName = L"Name";
    BSTR bstrName = SysAllocString(szName);
    DISPID dispidName;
    hr = p_current_track->GetIDsOfNames(IID_NULL, &bstrName, 1, LOCALE_USER_DEFAULT, &dispidName);
    SysFreeString(bstrName);
    if (FAILED(hr)) {
        CoUninitialize();
        return nullptr;
    }
    return p_current_track;
}
TrackInfo iTunes::get_track_info() {
    TrackInfo info;
    DISPPARAMS dispparamsNoArgs = {NULL, NULL, 0, 0};
    VARIANT varResult;
    DISPID dispid;
    struct PropertyInfo {
        const wchar_t* name;
        wstring& value;
    };
    PropertyInfo properties[] = {
        {L"Name", info.name},
        {L"Artist", info.artist},
        {L"Album", info.album},
        {L"Location", info.location},
    };
    for (const auto& prop : properties) {
        BSTR bstrProp = SysAllocString(prop.name);
        hr = p_current_track->GetIDsOfNames(IID_NULL, &bstrProp, 1, LOCALE_USER_DEFAULT, &dispid);
        VariantInit(&varResult);
        hr = p_current_track->Invoke(dispid, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYGET, &dispparamsNoArgs, &varResult, NULL, NULL);
        if (SUCCEEDED(hr) && V_VT(&varResult) == VT_BSTR) {
            if (V_BSTR(&varResult) != NULL) {
                prop.value = V_BSTR(&varResult);
            }
            else {
                iTunes_logger.logg_and_logg("iTunes error with V_BSTR in get_track_info");
                prop.value = L"";
            }
        }
        VariantClear(&varResult);
        SysFreeString(bstrProp);
    }
    BSTR bstrDuration = SysAllocString(L"Duration");
    hr = p_current_track->GetIDsOfNames(IID_NULL, &bstrDuration, 1, LOCALE_USER_DEFAULT, &dispid);
    VariantInit(&varResult);
    hr = p_current_track->Invoke(dispid, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYGET, &dispparamsNoArgs, &varResult, NULL, NULL);
    if (SUCCEEDED(hr) && V_VT(&varResult) == VT_I4) {
        info.duration = V_I4(&varResult);
    }
    VariantClear(&varResult);
    SysFreeString(bstrDuration);
    return info;
}
void iTunes::play_pause() {
    if (!initialized) {
        initialize_com();
    }
    DISPID dispidPlayPause;
    const OLECHAR* szPlayPause = L"PlayPause";
    BSTR bstrPlayPause = SysAllocString(szPlayPause);
    iTunes_app->GetIDsOfNames(IID_NULL, &bstrPlayPause, 1, LOCALE_USER_DEFAULT, &dispidPlayPause);
    SysFreeString(bstrPlayPause);
    DISPPARAMS dispparamsNoArgs = {NULL, NULL, 0, 0};
    iTunes_app->Invoke(dispidPlayPause, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_METHOD, &dispparamsNoArgs, NULL, NULL, NULL);
}
void iTunes::next_song() {
    if (!initialized) {
        initialize_com();
    }
    DISPID dispidNextTrack;
    const OLECHAR* szNextTrack = L"NextTrack";
    BSTR bstrNextTrack = SysAllocString(szNextTrack);
    iTunes_app->GetIDsOfNames(IID_NULL, &bstrNextTrack, 1, LOCALE_USER_DEFAULT, &dispidNextTrack);
    SysFreeString(bstrNextTrack);
    DISPPARAMS dispparamsNoArgs = {NULL, NULL, 0, 0};
    iTunes_app->Invoke(dispidNextTrack, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_METHOD, &dispparamsNoArgs, NULL, NULL, NULL);
}
void iTunes::prev_song() {
    if (!initialized) {
        initialize_com();
    }
    DISPID dispidPreviousTrack;
    const OLECHAR* szPreviousTrack = L"PreviousTrack";
    BSTR bstrPreviousTrack = SysAllocString(szPreviousTrack);
    iTunes_app->GetIDsOfNames(IID_NULL, &bstrPreviousTrack, 1, LOCALE_USER_DEFAULT, &dispidPreviousTrack);
    SysFreeString(bstrPreviousTrack);
    DISPPARAMS dispparamsNoArgs = {NULL, NULL, 0, 0};
    iTunes_app->Invoke(dispidPreviousTrack, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_METHOD, &dispparamsNoArgs, NULL, NULL, NULL);
}
wstring iTunes::get_current_track() {
    if (!initialized) {
        initialize_com();
    }
    p_current_track = get_current_track_com_object();
    if (!p_current_track) {
        remaining_song_duration = -1;
        return L"";
    }
    TrackInfo curr_song = get_track_info();
    int duration = curr_song.duration;
    int playback_position = get_current_playback_position();
    if (playback_position == 0) {
        remaining_song_duration = duration;
    }
    else if (playback_position > 0) {
        remaining_song_duration = duration - playback_position;
    }
    else if (playback_position == -1) {
        remaining_song_duration = -1;
    }
    wss dur;
    dur << duration / 60 << ':' << setw(2) << setfill(L'0') << duration % 60;
    wss ws;
    ws << '[' << curr_song.name << "] [" << curr_song.artist << "] [" << curr_song.album << "] [" << dur.str() << ']';
    track_location = curr_song.location;
    wstring current_song = ws.str();
    if (last_retrieved_song != current_song) {
        iTunes_logger.loggnl_and_loggnl("current song: ");
        iTunes_logger.logg_and_print(wstr_to_str(current_song));
        song_history.push_back(current_song);
    }
    else if (song_history.empty()) {
        iTunes_logger.logg_and_print(wstr_to_str(current_song));
        song_history.push_back(current_song);
    }
    last_retrieved_song = current_song;
    return current_song;
}
int iTunes::get_current_playback_position() {
    if (!initialized || iTunes_app == nullptr) {
        return -1;
    }
    const OLECHAR* szPlayerPosition = L"PlayerPosition";
    BSTR bstrPlayerPosition = SysAllocString(szPlayerPosition);
    DISPID dispidPlayerPosition;
    hr = iTunes_app->GetIDsOfNames(IID_NULL, &bstrPlayerPosition, 1, LOCALE_USER_DEFAULT, &dispidPlayerPosition);
    SysFreeString(bstrPlayerPosition);
    if (FAILED(hr)) {
        return -1;
    }
    DISPPARAMS dispparamsNoArgs = {NULL, NULL, 0, 0};
    VARIANT varResult;
    VariantInit(&varResult);
    hr = iTunes_app->Invoke(dispidPlayerPosition, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYGET, &dispparamsNoArgs, &varResult, NULL, NULL);
    if (FAILED(hr)) {
        return -1;
    }
    int currentPosition = -1;
    if (V_VT(&varResult) == VT_I4) {
        currentPosition = V_I4(&varResult);
    }
    VariantClear(&varResult);
    return currentPosition;
}

/** \runtime */
void print_next_up_song_list() {
    iTunes_logger.logg_and_logg("print_next_up_song_list()");
    auto next_up_list = wstr_to_str(get_clipboard_text());
    iss list_stream(next_up_list);
    oss formatted_list;
    string item;
    while (getline(list_stream, item, '\n')) {
        auto formatted_item = replace_tabs_with_brackets(item);
        formatted_list << formatted_item << "\n";
    }
    auto formatted_str = formatted_list.str();
    iTunes_logger.loggnl_and_printnl(formatted_str);
    set_clipboard_text(str_to_wstr(formatted_str));
    Sleep(50);
    paste_from_clipboard();
}

/** \runtime */
void iTunes_play_pause() {
    iTunes_logger.logg_and_logg("iTunes_play_pause()");
    ac_iTunes.play_pause();
    ac_iTunes.get_current_track();
}

void iTunes_prev_song() {
    iTunes_logger.logg_and_logg("iTunes_prev_song()");
    ac_iTunes.prev_song();
    ac_iTunes.get_current_track();
}

/** \runtime */
void print_iTunes_songs() {
    iTunes_logger.logg_and_logg("print_iTunes_songs()");
    wss song_text;
    ac_iTunes.get_current_track();
    if (!ac_iTunes.song_history.empty()) {
        for (const auto& song : ac_iTunes.song_history) {
            song_text << song << L"\n";
        }
        if (ac_iTunes.song_history.size() != 1) {
            iTunes_logger.loggnl_and_printnl(wstr_to_str(song_text.str()));
        }
        ac_iTunes.song_history.clear();
    }
    else {
        song_text << L"\n";
    }
    song_text << L"\n";
    set_clipboard_text(song_text.str());
    Sleep(50);
    paste_from_clipboard();
}
string replace_tabs_with_brackets(const string& input) {
    oss output;
    output << '[';
    for (char ch : input) {
        if (ch == '\t') {
            output << "] [";
        }
        else if (ch == '\r') {
        }
        else {
            output << ch;
        }
    }
    output << ']';
    return output.str();
}
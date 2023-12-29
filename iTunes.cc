#include <iTunes.h>

BOOL CALLBACK EnumWindowsProciTunes(HWND hwnd, LPARAM lParam) {
    const int length = GetWindowTextLength(hwnd) + 1;
    wstring windowTitle(length, L'\0');
    GetWindowText(hwnd, &windowTitle[0], length);
    if (windowTitle.find(L"iTunes") != wstring::npos) {
        *reinterpret_cast<bool*>(lParam) = true;
        return FALSE;
    }
    return TRUE;
}

bool is_iTunes_open() {
    bool iTunesWindowFound = false;
    EnumWindows(EnumWindowsProciTunes, reinterpret_cast<LPARAM>(&iTunesWindowFound));
    return iTunesWindowFound;
}

iTunes::iTunes() {
    if (is_iTunes_open()) {
        initialize_COM();
    }
}
iTunes::~iTunes() {
    finalize_COM();
}
void iTunes::initialize_COM() {
    if (initialized) {
        return;
    }
    hr = CoInitialize(NULL);
    if (FAILED(hr)) {
        cerr << "Failed to initialize COM, HRESULT: " << hr << endl;
        return;
    }
    CLSID clsid;
    hr = CLSIDFromProgID(L"iTunes.Application", &clsid);
    if (FAILED(hr)) {
        cerr << "Failed to get CLSID from ProgID, HRESULT: " << hr << endl;
        CoUninitialize();
        return;
    }
    hr = CoCreateInstance(clsid, NULL, CLSCTX_LOCAL_SERVER, IID_IDispatch, (void**)&iTunesApp);
    if (FAILED(hr)) {
        cerr << "Failed to create iTunes instance, HRESULT: " << hr << endl;
        CoUninitialize();
        return;
    }
    initialized = true;
}
void iTunes::finalize_COM() {
    if (pCurrentTrack != nullptr) {
        pCurrentTrack->Release();
        pCurrentTrack = nullptr;
    }
    if (iTunesApp != nullptr) {
        iTunesApp->Release();
        iTunesApp = nullptr;
    }
    CoUninitialize();
}
IDispatch* iTunes::getCurrentTrackCOMObject() {
    if (iTunesApp == nullptr) {
        cerr << "iTunesApp is not initialized" << endl;
        return nullptr;
    }
    const OLECHAR* szMember = L"CurrentTrack";
    BSTR bstrMember = SysAllocString(szMember);
    if (!bstrMember) {
        cerr << "Failed to allocate BSTR for member name" << endl;
        return nullptr;
    }
    DISPID dispidCurrentTrack;
    hr = iTunesApp->GetIDsOfNames(IID_NULL, &bstrMember, 1, LOCALE_USER_DEFAULT, &dispidCurrentTrack);
    SysFreeString(bstrMember);
    if (FAILED(hr)) {
        cerr << "Failed to get DISPID for CurrentTrack, HRESULT: " << hex << hr << endl;
        return nullptr;
    }
    DISPPARAMS dispparamsNoArgs ={NULL, NULL, 0, 0};
    VARIANT varResult;
    VariantInit(&varResult);
    hr = iTunesApp->Invoke(dispidCurrentTrack, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYGET, &dispparamsNoArgs, &varResult, NULL, NULL);
    if (FAILED(hr)) {
        cerr << "Invoke failed" << endl;
        iTunesApp->Release();
        CoUninitialize();
        return nullptr;
    }
    if (V_VT(&varResult) != VT_DISPATCH || V_DISPATCH(&varResult) == NULL) {
        cerr << "No current track available" << endl;
        return nullptr;
    }
    IDispatch* pCurrentTrack = V_DISPATCH(&varResult);
    const OLECHAR* szName = L"Name";
    BSTR bstrName = SysAllocString(szName);
    DISPID dispidName;
    hr = pCurrentTrack->GetIDsOfNames(IID_NULL, &bstrName, 1, LOCALE_USER_DEFAULT, &dispidName);
    SysFreeString(bstrName);
    if (FAILED(hr)) {
        cerr << "Failed to get DISPID for Name" << endl;
        pCurrentTrack->Release();
        iTunesApp->Release();
        CoUninitialize();
        return nullptr;
    }
    return (FAILED(hr)) ? nullptr : V_DISPATCH(&varResult);
}
TrackInfo iTunes::getTrackInfo() {
    TrackInfo info;
    DISPPARAMS dispparamsNoArgs ={NULL, NULL, 0, 0};
    VARIANT varResult;
    DISPID dispid;
    struct PropertyInfo {
        const wchar_t* name;
        wstring& value;
    };
    PropertyInfo properties[] ={
        {L"Name", info.name},
        {L"Artist", info.artist},
        {L"Album", info.album},
        {L"Location", info.location},
    };
    for (const auto& prop:properties) {
        BSTR bstrProp = SysAllocString(prop.name);
        hr = pCurrentTrack->GetIDsOfNames(IID_NULL, &bstrProp, 1, LOCALE_USER_DEFAULT, &dispid);
        VariantInit(&varResult);
        hr = pCurrentTrack->Invoke(dispid, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYGET, &dispparamsNoArgs, &varResult, NULL, NULL);
        if (SUCCEEDED(hr) && V_VT(&varResult) == VT_BSTR) {
            prop.value = V_BSTR(&varResult);
        }
        VariantClear(&varResult);
        SysFreeString(bstrProp);
    }
    BSTR bstrDuration = SysAllocString(L"Duration");
    hr = pCurrentTrack->GetIDsOfNames(IID_NULL, &bstrDuration, 1, LOCALE_USER_DEFAULT, &dispid);
    VariantInit(&varResult);
    hr = pCurrentTrack->Invoke(dispid, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYGET, &dispparamsNoArgs, &varResult, NULL, NULL);
    if (SUCCEEDED(hr) && V_VT(&varResult) == VT_I4) {
        info.duration = V_I4(&varResult);
    }
    VariantClear(&varResult);
    SysFreeString(bstrDuration);
    DISPID dispidDelete;
    const OLECHAR* szDelete = L"Delete";
    BSTR bstrDelete = SysAllocString(szDelete);
    hr = pCurrentTrack->GetIDsOfNames(IID_NULL, &bstrDelete, 1, LOCALE_USER_DEFAULT, &dispidDelete);
    SysFreeString(bstrDelete);
    dispparamsNoArgs ={NULL, NULL, 0, 0};
    hr = pCurrentTrack->Invoke(dispidDelete, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_METHOD, &dispparamsNoArgs, NULL, NULL, NULL);
    return info;
}
void iTunes::play_pause() {
    if (!initialized) {
        cout << "iTunes not started\n";
        return;
    }
    DISPID dispidPlayPause;
    const OLECHAR* szPlayPause = L"PlayPause";
    BSTR bstrPlayPause = SysAllocString(szPlayPause);
    iTunesApp->GetIDsOfNames(IID_NULL, &bstrPlayPause, 1, LOCALE_USER_DEFAULT, &dispidPlayPause);
    SysFreeString(bstrPlayPause);
    DISPPARAMS dispparamsNoArgs ={NULL, NULL, 0, 0};
    iTunesApp->Invoke(dispidPlayPause, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_METHOD, &dispparamsNoArgs, NULL, NULL, NULL);
}
void iTunes::next_song() {
    if (!initialized) {
        cout << "iTunes not started\n";
        return;
    }
    DISPID dispidNextTrack;
    const OLECHAR* szNextTrack = L"NextTrack";
    BSTR bstrNextTrack = SysAllocString(szNextTrack);
    iTunesApp->GetIDsOfNames(IID_NULL, &bstrNextTrack, 1, LOCALE_USER_DEFAULT, &dispidNextTrack);
    SysFreeString(bstrNextTrack);
    DISPPARAMS dispparamsNoArgs ={NULL, NULL, 0, 0};
    iTunesApp->Invoke(dispidNextTrack, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_METHOD, &dispparamsNoArgs, NULL, NULL, NULL);
}
void iTunes::prev_song() {
    if (!initialized) {
        cout << "iTunes not started\n";
        return;
    }
    DISPID dispidPreviousTrack;
    const OLECHAR* szPreviousTrack = L"PreviousTrack";
    BSTR bstrPreviousTrack = SysAllocString(szPreviousTrack);
    iTunesApp->GetIDsOfNames(IID_NULL, &bstrPreviousTrack, 1, LOCALE_USER_DEFAULT, &dispidPreviousTrack);
    SysFreeString(bstrPreviousTrack);
    DISPPARAMS dispparamsNoArgs ={NULL, NULL, 0, 0};
    iTunesApp->Invoke(dispidPreviousTrack, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_METHOD, &dispparamsNoArgs, NULL, NULL, NULL);
}
wstring iTunes::get_current_track() {
    if (!initialized) {
        initialize_COM();
    }
    pCurrentTrack = getCurrentTrackCOMObject();
    if (!pCurrentTrack) {
        return L"";
    }
    TrackInfo curr_song = getTrackInfo();
    wss ws;
    ws << "[" << curr_song.name << "] [" << curr_song.artist << "] [" << curr_song.album << "] [" << curr_song.duration << " secs]";
    pCurrentTrack->Release();
    pCurrentTrack = nullptr;
    if (!DeleteFile(curr_song.location.c_str())) {
        DWORD error = GetLastError();
        string error_msg = "File note deleted";
        string error_code = to_string(error);
        if (error == 32) {
            error_msg += " - File locked by iTunes (error code: " + error_code + ")";
        }
        else {
            error_msg += " - Error code: " + error_code;
        }
        print(error_msg);
    }
    return ws.str();
}
void print_iTunes_song() {
    wstring iTunes_wstr = ac_iTunes.get_current_track();
    string iTunes_str = wstringToString(iTunes_wstr);
    if (!iTunes_str.empty()) {
        print(iTunes_str + "\n");
    }
    set_clipboard_text(iTunes_wstr + L"\n\n");
    Sleep(50);
    simulate_paste();
}
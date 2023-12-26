#include <iTunes.h>

iTunes::iTunes() {
    initializeCOM();
}
iTunes::~iTunes() {
    finalizeCOM();
}
void iTunes::initializeCOM() {
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
}
void iTunes::finalizeCOM() {
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
void iTunes::playPause() {
    DISPID dispidPlayPause;
    const OLECHAR* szPlayPause = L"PlayPause";
    BSTR bstrPlayPause = SysAllocString(szPlayPause);
    iTunesApp->GetIDsOfNames(IID_NULL, &bstrPlayPause, 1, LOCALE_USER_DEFAULT, &dispidPlayPause);
    SysFreeString(bstrPlayPause);
    DISPPARAMS dispparamsNoArgs ={NULL, NULL, 0, 0};
    iTunesApp->Invoke(dispidPlayPause, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_METHOD, &dispparamsNoArgs, NULL, NULL, NULL);
}
void iTunes::nextSong() {
    DISPID dispidNextTrack;
    const OLECHAR* szNextTrack = L"NextTrack";
    BSTR bstrNextTrack = SysAllocString(szNextTrack);
    iTunesApp->GetIDsOfNames(IID_NULL, &bstrNextTrack, 1, LOCALE_USER_DEFAULT, &dispidNextTrack);
    SysFreeString(bstrNextTrack);
    DISPPARAMS dispparamsNoArgs ={NULL, NULL, 0, 0};
    iTunesApp->Invoke(dispidNextTrack, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_METHOD, &dispparamsNoArgs, NULL, NULL, NULL);
}
void iTunes::prevSong() {
    DISPID dispidPreviousTrack;
    const OLECHAR* szPreviousTrack = L"PreviousTrack";
    BSTR bstrPreviousTrack = SysAllocString(szPreviousTrack);
    iTunesApp->GetIDsOfNames(IID_NULL, &bstrPreviousTrack, 1, LOCALE_USER_DEFAULT, &dispidPreviousTrack);
    SysFreeString(bstrPreviousTrack);
    DISPPARAMS dispparamsNoArgs ={NULL, NULL, 0, 0};
    iTunesApp->Invoke(dispidPreviousTrack, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_METHOD, &dispparamsNoArgs, NULL, NULL, NULL);
}

wstring iTunes::getCurrentTrackInfo() {
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


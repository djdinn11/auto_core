/*!
\file taskbar_11.ixx
\brief Provides support for accessing applications not pinned to the taskbar or in positions 11 and above.
*/
export module taskbar_11;
import visual;
import <Windows.h>;

export {
    void activate_wordpad();
    void activate_notepad();
}

int wordpad_windows;
HWND wordpad_hwnd;
int notepad_windows;
HWND notepad_hwnd;

BOOL CALLBACK enum_wordpad_windows(HWND hwnd, LPARAM lParam) {
    const int buffer_size = 1024;
    TCHAR window_title[buffer_size];
    if (GetWindowText(hwnd, window_title, buffer_size) > 0 && IsWindowVisible(hwnd)) {
        wstring title(window_title);
        if (title.length() >= 7 && title.substr(title.length() - 7) == L"WordPad") {
            wordpad_hwnd = hwnd;
            wordpad_windows++;
        }
    }
    return TRUE;
}
BOOL CALLBACK enum_notepad_windows(HWND hwnd, LPARAM lParam) {
    const int buffer_size = 1024;
    TCHAR window_title[buffer_size];
    if (GetWindowText(hwnd, window_title, buffer_size) > 0 && IsWindowVisible(hwnd)) {
        wstring title(window_title);
        if (title.length() >= 7 && title.substr(title.length() - 7) == L"Notepad") {
            notepad_hwnd = hwnd;
            notepad_windows++;
        }
    }
    return TRUE;
}

/** \runtime */
void activate_wordpad() {
    wordpad_windows = 0;
    EnumWindows(enum_wordpad_windows, 0);
    if (!wordpad_windows) {
        logg("activate_wordpad() - launch new");
        HWND hwnd = NULL;
        LPCWSTR operation = L"open";
        LPCWSTR file = L"wordpad.exe";
        LPCWSTR parameters = NULL;
        LPCWSTR directory = NULL;
        int showCmd = SW_SHOWNORMAL;
        ShellExecute(hwnd, operation, file, parameters, directory, showCmd);
    }
    else if (wordpad_windows == 1)
    {
        HWND current_window = GetForegroundWindow();
        if (IsIconic(wordpad_hwnd)) {
            ShowWindow(wordpad_hwnd, SW_RESTORE);
            SetForegroundWindow(wordpad_hwnd);
            logg("activate_wordpad() - restore");
        }
        else if (current_window == wordpad_hwnd) {
            ShowWindow(wordpad_hwnd, SW_MINIMIZE);
            logg("activate_wordpad() - minimize");
        }
        else {
            logg("activate_wordpad() - set focus");
            SetForegroundWindow(wordpad_hwnd);
        }
    }
    else {
        logg("activate_wordpad() - multiple windows detected");
        SetForegroundWindow(wordpad_hwnd);
    }
}

/** \runtime */
void activate_notepad() {
    notepad_windows = 0;
    EnumWindows(enum_notepad_windows, 0);
    if (!notepad_windows) {
        logg("activate_notepad() - launch new");
        HWND hwnd = NULL;
        LPCWSTR operation = L"open";
        LPCWSTR file = L"notepad.exe";
        LPCWSTR parameters = NULL;
        LPCWSTR directory = NULL;
        int showCmd = SW_SHOWNORMAL;
        ShellExecute(hwnd, operation, file, parameters, directory, showCmd);
    }
    else if (notepad_windows == 1)
    {
        HWND current_window = GetForegroundWindow();
        if (IsIconic(notepad_hwnd)) {
            ShowWindow(notepad_hwnd, SW_RESTORE);
            SetForegroundWindow(notepad_hwnd);
            logg("activate_notepad() - restore");
        }
        else if (current_window == notepad_hwnd) {
            ShowWindow(notepad_hwnd, SW_MINIMIZE);
            logg("activate_notepad() - minimize");
        }
        else {
            logg("activate_notepad() - set focus");
            SetForegroundWindow(notepad_hwnd);
        }
    }
    else {
        logg("activate_notepad() - multiple windows detected");
        SetForegroundWindow(notepad_hwnd);
    }
}
#include <auto_core.h>
#include <format>
#include <print>

Spotify mySpotify{};
iTunes myiTunes{};
HHOOK keyboardHook;
DWORD mainThreadId;
bool primary = true;
bool closing_program = false;
int word_windows = 0;
bool word_set = false;

void close_program() {
    myiTunes.finalizeCOM();
    if (keyboardHook != NULL) {
        UnhookWindowsHookEx(keyboardHook);
    }
    CoUninitialize();
}

HWND CreateMessageWindow() {
    WNDCLASSEX wcex ={0};
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.lpfnWndProc = DefWindowProc;
    wcex.hInstance = GetModuleHandle(NULL);
    wcex.lpszClassName = TEXT("MessageOnlyWindowClass");
    RegisterClassEx(&wcex);
    HWND hwnd = CreateWindowEx(0, wcex.lpszClassName, TEXT(""), 0, 0, 0, 0, 0, HWND_MESSAGE, NULL, wcex.hInstance, NULL);
    return hwnd;
}

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam) {
    const int bufferSize = 1024;
    TCHAR windowTitle[bufferSize];

    if (GetWindowText(hwnd, windowTitle, bufferSize) > 0 && IsWindowVisible(hwnd)) {
        wstring title(windowTitle);
        if (title.length() >= 4 && title.substr(title.length() - 4) == L"Word") {
            word_windows += 1;
        }
    }
    return TRUE;
}

LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode >= 0 && wParam == WM_KEYDOWN) {
        KBDLLHOOKSTRUCT* p = reinterpret_cast<KBDLLHOOKSTRUCT*>(lParam);
        int vkCode = p->vkCode;
        if (primary) {
            closing_program = false;
        }
        if (word_set && vkCode == numkey_2) {
            send_winkey_with_number(3);
            return 1;
        }
        else if (word_set && (vkCode > numkey_0 && vkCode < numkey_out_of_range)) {
            release_winkey();
            word_set = false;
            primary = true;
            return 1;
        }
        if (vkCode == numkey_1 && closing_program) {
            PostThreadMessage(mainThreadId, WM_CLOSE_PROGRAM, 0, 0);
            return 1;
        }
        else if (vkCode == numkey_1) {
            activate_Auto_Core();
        }
        else if (vkCode == numkey_2) {
            word_windows = 0;
            EnumWindows(EnumWindowsProc, 0);
            if (word_windows < 2) {
                activate_Word();
            }
            else {
                press_and_hold_winkey();
                send_winkey_with_number(3);
                word_set = true;
                primary = false;
                return 1;
            }
        }
        else if (vkCode == numkey_3) {
            activate_iTunes();
        }
        else if (vkCode == numkey_4) {
            if (primary) { PostThreadMessage(mainThreadId, WM_ITUNES_PREV, 0, 0); }
            else { activate_Chrome(); }
        }
        else if (vkCode == numkey_5) {
            if (primary) { PostThreadMessage(mainThreadId, WM_ITUNES_PLAY, 0, 0); }
            else { activate_Visual(); }
        }
        else if (vkCode == numkey_6) {
            if (primary) { PostThreadMessage(mainThreadId, WM_ITUNES_NEXT, 0, 0); }
            else { activate_Discord(); }
        }
        else if (vkCode == numkey_7) {
            if (primary) { PostThreadMessage(mainThreadId, WM_PRINT_GPT, 0, 0); }
            else { activate_Folder(); }
        }
        else if (vkCode == numkey_8) {
            if (primary) { PostThreadMessage(mainThreadId, WM_SP_CURR, 0, 0); }
            else { activate_Taskbar_8(); }
        }
        else if (vkCode == numkey_9) {
            if (primary) { PostThreadMessage(mainThreadId, WM_PRINT_TIME, 0, 0); }
            else { PostThreadMessage(mainThreadId, WM_SP_NEXT, 0, 0); }
        }
        else if (vkCode == numkey_plus) {
            if (primary) { PostThreadMessage(mainThreadId, WM_ITUNES_CURR, 0, 0); }
            else { PostThreadMessage(mainThreadId, WM_LILY_CHOICE, 0, 0); }
        }
        else if (vkCode == numkey_star) {
            if (primary) { PostThreadMessage(mainThreadId, WM_STAR_CHOICE, 0, 0); }
            else { PostThreadMessage(mainThreadId, WM_STAR_TITLE, 0, 0); }
        }
        else if (vkCode == numkey_0) {
            closing_program = !closing_program;
            primary = !primary;
            if (word_set) {
                word_set = false;
                release_winkey();
            }
            cout << (closing_program ? "Exiting program\n" : "Exiting deactivated\n");
            return 1;
        }
        if (vkCode > numkey_0 && vkCode < numkey_out_of_range) {
            if (!primary) {
                primary = true;
            }
            return 1;
        }
    }
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

void ProcessMessage(const MSG& msg) {
    if (msg.message == WM_STAR_TITLE) {
        print_episode_title();
    }
    else if (msg.message == WM_STAR_CHOICE) {
        print_choice_star();
    }
    else if (msg.message == WM_LILY_CHOICE) {
        print_choice_lily();
    }
    else if (msg.message == WM_ITUNES_CURR) {
        print_iTunes_song();
    }
    else if (msg.message == WM_ITUNES_PREV) {
        myiTunes.prevSong();
    }
    else if (msg.message == WM_ITUNES_PLAY) {
        myiTunes.playPause();
    }
    else if (msg.message == WM_ITUNES_NEXT) {
        myiTunes.nextSong();
    }
    else if (msg.message == WM_SP_CURR) {
        try {
            print_Spotify_song();
        }
        catch (...) {
            cerr << "Spotify error" << endl;
        }
    }
    else if (msg.message == WM_SP_PREV) {
        mySpotify.Previous();
    }
    else if (msg.message == WM_SP_PLAY) {
        mySpotify.PlayPause();
    }
    else if (msg.message == WM_SP_NEXT) {
        mySpotify.Next();
    }
    else if (msg.message == WM_PRINT_TIME) {
        print_timestamp();
    }
    else if (msg.message == WM_PRINT_GPT) {
        thread t(print_gpt_message);
        t.detach();
    }
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    HWND hwnd = CreateMessageWindow();
    keyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, NULL, 0);
    MSG msg;
    mainThreadId = GetCurrentThreadId();
    print("Program ready\n");
    while (GetMessage(&msg, NULL, 0, 0) > 0) {
        if (msg.message == WM_CLOSE_PROGRAM) {
            close_program();
            HWND consoleWindow = GetConsoleWindow();
            if (consoleWindow != NULL) {
                PostMessage(consoleWindow, WM_CLOSE, 0, 0);
            }
            break;
        }
        try {
            ProcessMessage(msg);
        }
        catch (const std::exception& e) {
            cerr << "Caught Exception: " << e.what() << endl;
        }
        catch (...) {
            cerr << "Uncaught Exception" << endl;
        }

        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    UnhookWindowsHookEx(keyboardHook);
    exit(0);
    return 0;
}
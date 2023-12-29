#include <auto_core.h>
#include <format>
#include <print>

Spotify ac_Spotify{};
iTunes ac_iTunes{};
HHOOK keyboardHook;
DWORD mainThreadId;
bool primary = true;
int word_windows = 0;
bool word_set = false;

void close_program() {
    ac_iTunes.finalize_COM();
    if (keyboardHook != NULL) {
        UnhookWindowsHookEx(keyboardHook);
    }
    PostThreadMessage(mainThreadId, WM_QUIT, 0, 0);
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

BOOL CALLBACK EnumWordWindows(HWND hwnd, LPARAM lParam) {
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
LRESULT CALLBACK SendNumpadEvent(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode >= 0 && wParam == WM_KEYDOWN) {
        KBDLLHOOKSTRUCT* p = reinterpret_cast<KBDLLHOOKSTRUCT*>(lParam);
        int vkCode = p->vkCode;
        if (vkCode >= numkey_0 && vkCode <= numkey_divide) {
            if (vkCode == numkey_0) {
                PostThreadMessage(mainThreadId, AC_NUMKEY_0, 0, 0);
            }
            else if (vkCode == numkey_1) {
                PostThreadMessage(mainThreadId, AC_NUMKEY_1, 0, 0);
            }
            else if (vkCode == numkey_2) {
                PostThreadMessage(mainThreadId, AC_NUMKEY_2, 0, 0);
            }
            else if (vkCode == numkey_3) {
                PostThreadMessage(mainThreadId, AC_NUMKEY_3, 0, 0);
            }
            else if (vkCode == numkey_4) {
                PostThreadMessage(mainThreadId, AC_NUMKEY_4, 0, 0);
            }
            else if (vkCode == numkey_5) {
                PostThreadMessage(mainThreadId, AC_NUMKEY_5, 0, 0);
            }
            else if (vkCode == numkey_6) {
                PostThreadMessage(mainThreadId, AC_NUMKEY_6, 0, 0);
            }
            else if (vkCode == numkey_7) {
                PostThreadMessage(mainThreadId, AC_NUMKEY_7, 0, 0);
            }
            else if (vkCode == numkey_8) {
                PostThreadMessage(mainThreadId, AC_NUMKEY_8, 0, 0);
            }
            else if (vkCode == numkey_9) {
                PostThreadMessage(mainThreadId, AC_NUMKEY_9, 0, 0);
            }
            else if (vkCode == numkey_star) {
                PostThreadMessage(mainThreadId, AC_NUMKEY_STAR, 0, 0);
            }
            else if (vkCode == numkey_plus) {
                PostThreadMessage(mainThreadId, AC_NUMKEY_PLUS, 0, 0);
            }
            else if (vkCode == numkey_enter) {
                PostThreadMessage(mainThreadId, AC_NUMKEY_ENTER, 0, 0);
            }
            else if (vkCode == numkey_minus) {
                PostThreadMessage(mainThreadId, AC_NUMKEY_MINUS, 0, 0);
            }
            else if (vkCode == numkey_period) {
                PostThreadMessage(mainThreadId, AC_NUMKEY_PERIOD, 0, 0);
            }
            else if (vkCode == numkey_divide) {
                PostThreadMessage(mainThreadId, AC_NUMKEY_DIVIDE, 0, 0);
            }
            return 1;
        }
    }
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}
void ProcessNumpadEvent(const MSG& msg) {
    if (msg.message == AC_NUMKEY_0 && word_set || word_set && msg.message != AC_NUMKEY_2) {
        release_winkey();
        word_set = false;  
    }
    else if (msg.message == AC_NUMKEY_0) {
        if (primary) {
            primary = false;
            cout << "Function key activated\n";
        }
        else {
            primary = true;
            cout << "Function key deactivated\n";
        }
    }
    else if (msg.message == AC_NUMKEY_1) {
        if (primary) {
            activate_Auto_Core();
        }
        else {
            close_program();
        }
    }
    else if (msg.message == AC_NUMKEY_2) {
        if (word_set) {
            send_winkey_with_number(taskbar.word);
        }
        else {
            word_windows = 0;
            EnumWindows(EnumWordWindows, 0);
            if (word_windows < 2) {
                activate_Word();
            }
            else {
                press_and_hold_winkey();
                send_winkey_with_number(taskbar.word);
                word_set = true;
                primary = false;
            }
        }
    }
    else if (msg.message == AC_NUMKEY_3) {
            activate_iTunes();
    }
    else if (msg.message == AC_NUMKEY_4) {
        if (primary) {
            ac_iTunes.prev_song();
        }
        else {
            activate_Chrome();
        }
    }
    else if (msg.message == AC_NUMKEY_5) {
        if (primary) {
            ac_iTunes.play_pause();
        }
        else {
            activate_Visual();
        }
    }
    else if (msg.message == AC_NUMKEY_6) {
        if (primary) {
            ac_iTunes.next_song();
        }
        else {
            activate_Discord();
        }
    }
    else if (msg.message == AC_NUMKEY_7) {
        if (primary) {
            thread t(print_gpt_message);
            t.detach();
        }
        else {
            activate_Folder();
        }
    }
    else if (msg.message == AC_NUMKEY_8) {
        if (primary) {
            try {
                print_Spotify_song();
            }
            catch (...) {
                cerr << "Spotify error" << endl;
            }
        }
        else {
            activate_Taskbar_8();
        }
    }
    else if (msg.message == AC_NUMKEY_9) {
        if (primary) {
            print_timestamp();
        }
        else {
            ac_Spotify.next_song();
        }
    }
    else if (msg.message == AC_NUMKEY_STAR) {
        if (primary) {
            print_Star_choice();
        }
        else {
            print_episode_title();
        }
    }
    else if (msg.message == AC_NUMKEY_PLUS) {
        if (primary) {
            print_iTunes_song();
        }
        else {
            print_Lily_choice();
        }
    }
    if (!primary && msg.message != AC_NUMKEY_0) {
        primary = true;
    }
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    HWND hwnd = CreateMessageWindow();
    keyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, SendNumpadEvent, NULL, 0);
    MSG msg;
    mainThreadId = GetCurrentThreadId();
    print("Program ready\n");
    while (GetMessage(&msg, NULL, 0, 0) > 0) {
        try {
            ProcessNumpadEvent(msg);
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
    return 0;
}
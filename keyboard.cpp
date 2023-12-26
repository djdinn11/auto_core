#include <keyboard.h>

void send_winkey(int position) {
    INPUT inputs[4] ={};
    ZeroMemory(inputs, sizeof(inputs));
    inputs[0].type = INPUT_KEYBOARD;
    inputs[0].ki.wVk = VK_RWIN;
    inputs[1].type = INPUT_KEYBOARD;
    inputs[1].ki.wVk = 0x30 + position;
    inputs[2].type = INPUT_KEYBOARD;
    inputs[2].ki.wVk = inputs[1].ki.wVk;
    inputs[3].type = INPUT_KEYBOARD;
    inputs[3].ki.wVk = VK_RWIN;
    inputs[2].ki.dwFlags = KEYEVENTF_KEYUP;
    inputs[3].ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(4, inputs, sizeof(INPUT));
}
void send_winkey_with_number(int number) {
    INPUT inputs[2] ={};
    ZeroMemory(inputs, sizeof(inputs));
    inputs[0].type = INPUT_KEYBOARD;
    inputs[0].ki.wVk = 0x30 + number;
    inputs[1].type = INPUT_KEYBOARD;
    inputs[1].ki.wVk = 0x30 + number;
    inputs[1].ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(2, inputs, sizeof(INPUT));
}
void press_and_hold_winkey() {
    INPUT input ={0};
    input.type = INPUT_KEYBOARD;
    input.ki.wVk = VK_RWIN;
    SendInput(1, &input, sizeof(INPUT));
}
void release_winkey() {
    INPUT input ={0};
    input.type = INPUT_KEYBOARD;
    input.ki.wVk = VK_RWIN;
    input.ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(1, &input, sizeof(INPUT));
}
void set_clipboard_text(const wstring& text) {
    if (OpenClipboard(nullptr)) {
        EmptyClipboard();
        HGLOBAL hClipboardData;
        size_t size = (text.size() + 1) * sizeof(wchar_t);
        hClipboardData = GlobalAlloc(GMEM_MOVEABLE, size);
        if (hClipboardData != nullptr) {
            wchar_t* pchData = static_cast<wchar_t*>(GlobalLock(hClipboardData));
            if (pchData != nullptr) {
                memcpy(pchData, text.c_str(), size);
                GlobalUnlock(hClipboardData);
                SetClipboardData(CF_UNICODETEXT, hClipboardData);
            }
        }
        CloseClipboard();
    }
}
void simulate_paste() {
    INPUT inputs[4] ={};
    inputs[0].type = INPUT_KEYBOARD;
    inputs[0].ki.wVk = VK_CONTROL;
    inputs[1].type = INPUT_KEYBOARD;
    inputs[1].ki.wVk = 'V';
    inputs[2].type = INPUT_KEYBOARD;
    inputs[2].ki.wVk = 'V';
    inputs[2].ki.dwFlags = KEYEVENTF_KEYUP;
    inputs[3].type = INPUT_KEYBOARD;
    inputs[3].ki.wVk = VK_CONTROL;
    inputs[3].ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));
}
void simulate_save() {
    INPUT inputs[4] ={};
    inputs[0].type = INPUT_KEYBOARD;
    inputs[0].ki.wVk = VK_CONTROL;
    inputs[1].type = INPUT_KEYBOARD;
    inputs[1].ki.wVk = 'S';
    inputs[2].type = INPUT_KEYBOARD;
    inputs[2].ki.wVk = 'S';
    inputs[2].ki.dwFlags = KEYEVENTF_KEYUP;
    inputs[3].type = INPUT_KEYBOARD;
    inputs[3].ki.wVk = VK_CONTROL;
    inputs[3].ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));
}
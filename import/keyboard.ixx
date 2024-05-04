/*!
\file keyboard.ixx
\brief Supports the simulation of keyboard events.
*/
export module keyboard;
import base;
import <Windows.h>;

export {
    void send_winkey(int position);
    void send_winkey_and_number(int number);
    void press_and_hold_winkey();
    void release_winkey();
    void send_alt_tab();
};

void send_winkey(int position) {
    INPUT inputs[4] = {};
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
void send_winkey_and_number(int number) {
    INPUT inputs[2] = {};
    ZeroMemory(inputs, sizeof(inputs));
    inputs[0].type = INPUT_KEYBOARD;
    inputs[0].ki.wVk = 0x30 + number;
    inputs[1].type = INPUT_KEYBOARD;
    inputs[1].ki.wVk = 0x30 + number;
    inputs[1].ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(2, inputs, sizeof(INPUT));
}
void press_and_hold_winkey() {
    INPUT input = {0};
    input.type = INPUT_KEYBOARD;
    input.ki.wVk = VK_RWIN;
    SendInput(1, &input, sizeof(INPUT));
}
void release_winkey() {
    INPUT input = {0};
    input.type = INPUT_KEYBOARD;
    input.ki.wVk = VK_RWIN;
    input.ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(1, &input, sizeof(INPUT));
}
void send_alt_tab() {
    INPUT inputs[4] = {};
    inputs[0].type = INPUT_KEYBOARD;
    inputs[0].ki.wVk = VK_MENU;
    inputs[1].type = INPUT_KEYBOARD;
    inputs[1].ki.wVk = VK_TAB;
    inputs[2].type = INPUT_KEYBOARD;
    inputs[2].ki.wVk = VK_TAB;
    inputs[2].ki.dwFlags = KEYEVENTF_KEYUP;
    inputs[3].type = INPUT_KEYBOARD;
    inputs[3].ki.wVk = VK_MENU;
    inputs[3].ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));
}
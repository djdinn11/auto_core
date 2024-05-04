#include <iostream>
#include <vector>
#include <Windows.h>
#include <iomanip>
#include <sstream>
#include <ostream>
#include <string>

using std::setw;
using std::setfill;
using std::uppercase;
using std::hex;
using std::wcout;
using std::endl;
using std::wstring;
using std::cout;
using std::cin;

bool enumerate_only_visible_windows = true;
const int max_class_name = 256;
int window_counter = 0;

void display_character_issue(wchar_t c) {
    if (c == 0x200B) {
        wcout << L"***zero width space [0x200B] detected***" << endl;
    }
    else {
        wcout << L"***[U+" << hex << uppercase << setw(4) << setfill(L'0') << static_cast<int>(c) << L"] detected!***" << endl;
    }
}
wstring parse_and_retrieve_title(const wstring& title) {
    wstring filtered_title;
    filtered_title.reserve(title.size());
    for (wchar_t c : title) {
        if (c == L'\0') break;
        if (iswprint(c) || c == L' ') {
            filtered_title += c;
        }
        else {
            display_character_issue(c);
        }
    }
    return filtered_title;
}

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam) {
    int length = GetWindowTextLength(hwnd) + 1;
    if (enumerate_only_visible_windows && !IsWindowVisible(hwnd)) {
        return TRUE;  // Skip non-visible windows if configured to do so.
    }
    wstring title(length, L'\0');
    wstring class_name(max_class_name, L'\0');
    GetWindowTextW(hwnd, &title[0], length);
    GetClassNameW(hwnd, &class_name[0], max_class_name);
    window_counter++;
    cout << window_counter << endl;
    title = parse_and_retrieve_title(title);
    wcout << title << endl;
    wcout << class_name << endl;
    return TRUE;
}
int main() {
    EnumWindows(EnumWindowsProc, 0);
    cout << "Press enter to exit...";
    cin.get();
    return 0;
}
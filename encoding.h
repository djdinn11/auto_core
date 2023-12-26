#pragma once
#include <Windows.h>
#include <iomanip>
#include <string>

using namespace std;

wstring get_executable_dir();
string wstringToString(const wstring& wstr);
wstring stringToWstring(const string& str);
wstring Utf8ToUtf16(const string& utf8);
string base64_encode(const string& in);
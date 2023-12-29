#pragma once
#include <Windows.h>
#include <iomanip>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <print>
#include <format>

using namespace std;

using ss = stringstream;
using oss = ostringstream;
using wss = wostringstream;

#define f format

void print(const std::string& s);

wstring get_executable_dir();
string wstringToString(const wstring& wstr);
wstring stringToWstring(const string& str);
wstring Utf8ToUtf16(const string& utf8);
string base64_encode(const string& in);
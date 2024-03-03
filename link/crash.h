#pragma once
#include <visual.h>
#include <windows.h>

using std::ios_base;

LONG WINAPI unhandled_exception_handler(EXCEPTION_POINTERS* exceptionInfo);
void restart_program(string error_report);
void crash_check();
/*!
\file crash.h
\brief Provides crash handling support for Auto Core, enabling resilience and continuous operation.

In case of a crash, Auto Core is designed to automatically restart, maintaining its functionality as a keyboard manager.
This module ensures that crashes are logged and reported, requiring user acknowledgment. Offers guidelines for internal updates to improve crash handling.
*/
#pragma once
#include <visual.h>

LONG WINAPI unhandled_exception_handler(EXCEPTION_POINTERS* exceptionInfo);
void restart_program(const string& error_report);
void crash_check();
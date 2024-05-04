/*!
\file end.h
\brief Handles system shutdown events, ensuring graceful termination of Auto Core.

By monitoring a hidden window for shutdown events, this module allows Auto Core to respond appropriately to system shutdowns.
\todo Verify that this module works by reviewing the logs.
*/
#pragma once
#include <visual.h>

BOOL WINAPI console_close_event(DWORD dwType);
HWND close_window_hidden_init();
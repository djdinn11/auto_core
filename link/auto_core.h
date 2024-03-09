#pragma once
#include <visual.h>
#include <choice.h>
#include <clipboard.h>
#include <clock.h>
#include <crash.h>
#include <dash.h>
#include <itunes.h>
#include <itunes_t.h>
#include <keyboard.h>
#include <logger.h>
#include <logger_c.h>
#include <main.h>
#include <numkey.h>
#include <server.h>
#include <slash.h>
#include <slash_i.h>
#include <sp_thread.h>
#include <spotify.h>
#include <star.h>
#include <taskbar.h>
#include <taskbar_11.h>

bool primary = true;
HWND program_window;
HHOOK keyboard_hook;
DWORD main_thread_id;
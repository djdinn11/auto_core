#pragma once

#include <star.h>
#include <Spotify.h>
#include <iTunes.h>
#include <keyboard.h>
#include <taskbar.h>
#include <thread>
#include <queue>
#include <print.h>
#include <choice.h>
#include <tchar.h>
#include <vector>
#include <visual.h>

#define WM_CLOSE_PROGRAM (WM_APP + 0)
#define WM_STAR_TITLE    (WM_APP + 1)
#define WM_SP_CURR       (WM_APP + 2)
#define WM_ITUNES_CURR   (WM_APP + 3)
#define WM_ITUNES_PREV   (WM_APP + 4)
#define WM_ITUNES_PLAY   (WM_APP + 5)
#define WM_ITUNES_NEXT   (WM_APP + 6)
#define WM_SP_PREV       (WM_APP + 7)
#define WM_SP_PLAY       (WM_APP + 8)
#define WM_SP_NEXT       (WM_APP + 9)
#define WM_PRINT_GPT     (WM_APP + 10)
#define WM_PRINT_TIME    (WM_APP + 11)
#define WM_LILY_CHOICE   (WM_APP + 12)
#define WM_STAR_CHOICE   (WM_APP + 13)
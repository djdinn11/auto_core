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

#define AC_CLOSE (WM_APP + 0)
#define AC_NUMKEY_0 (WM_APP + 96)
#define AC_NUMKEY_1 (WM_APP + 97)
#define AC_NUMKEY_2 (WM_APP + 98)
#define AC_NUMKEY_3 (WM_APP + 99)
#define AC_NUMKEY_4 (WM_APP + 100)
#define AC_NUMKEY_5 (WM_APP + 101)
#define AC_NUMKEY_6 (WM_APP + 102)
#define AC_NUMKEY_7 (WM_APP + 103)
#define AC_NUMKEY_8 (WM_APP + 104)
#define AC_NUMKEY_9 (WM_APP + 105)
#define AC_NUMKEY_STAR   (WM_APP + 106)
#define AC_NUMKEY_PLUS   (WM_APP + 107)
#define AC_NUMKEY_ENTER  (WM_APP + 108)
#define AC_NUMKEY_MINUS  (WM_APP + 109)
#define AC_NUMKEY_PERIOD (WM_APP + 110)
#define AC_NUMKEY_DIVIDE (WM_APP + 111)



//#define WM_CLOSE_PROGRAM (WM_APP + 0)
//#define WM_STAR_TITLE    (WM_APP + 1)
//#define WM_SP_CURR       (WM_APP + 2)
//#define WM_ITUNES_CURR   (WM_APP + 3)
//#define WM_ITUNES_PREV   (WM_APP + 4)
//#define WM_ITUNES_PLAY   (WM_APP + 5)
//#define WM_ITUNES_NEXT   (WM_APP + 6)
//#define WM_SP_PREV       (WM_APP + 7)
//#define WM_SP_PLAY       (WM_APP + 8)
//#define WM_SP_NEXT       (WM_APP + 9)
//#define WM_PRINT_GPT     (WM_APP + 10)
//#define WM_PRINT_TIME    (WM_APP + 11)
//#define WM_LILY_CHOICE   (WM_APP + 12)
//#define WM_STAR_CHOICE   (WM_APP + 13)
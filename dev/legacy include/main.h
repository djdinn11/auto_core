/*!
\file main.h
\brief Core support for cross-module communication and integration within the Auto Core framework.
*/
#pragma once
#include <visual.h>
#include <thread.h>

extern bool primary;
extern HWND program_window;
extern HHOOK keyboard_hook;
extern DWORD main_thread_id;
extern bool program_closing;
extern HANDLE ac_itunes_pipe;
extern HANDLE ac_sp_pipe;

void close_program();
void activate_function_key();
void deactivate_function_key();

void print_timestamp();

void set_focus_auto_core();
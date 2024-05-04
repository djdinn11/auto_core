#pragma once
#include <visual.h>

extern unordered_map<int, function<void()>> command_map;
extern bool end_process;

HANDLE create_pipe_server(const wstring& pipe_name);
HANDLE connect_to_pipe_server(const wstring& pipe_name);
bool send_pipe_command(HANDLE h_pipe, int command);
void process_pipe_commands(HANDLE h_pipe);
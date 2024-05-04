/*!
\file pipes.ixx
\brief This module provides support for inter-process communication using system pipes.
\hardlink
*/
export module pipes;
import base;
import logger;
import print;
import utils;
import <Windows.h>;

export unordered_map<int, function<void()>> command_map;
export bool end_process;

export {
    HANDLE create_pipe_server(const wstring& pipe_name);
    HANDLE connect_to_pipe_server(const wstring& pipe_name);
    bool send_pipe_command(HANDLE h_pipe, int command);
    void process_pipe_commands(HANDLE h_pipe);
}

HANDLE create_pipe_server(const wstring& pipe_name) {
    HANDLE h_pipe = CreateNamedPipe(
        (LR"(\\.\pipe\)" + pipe_name).c_str(),
        PIPE_ACCESS_DUPLEX,
        PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
        1, 1024, 1024, 0, NULL);

    if (h_pipe == INVALID_HANDLE_VALUE) {
        print("Failed to create pipe '{}'. Error: {}", wstr_to_str(pipe_name), GetLastError());
        return NULL;
    }
    logg("pipe '{}' created", wstr_to_str(pipe_name));
    return h_pipe;
}
HANDLE connect_to_pipe_server(const wstring& pipe_name) {
    HANDLE h_pipe = CreateFile(
        (LR"(\\.\pipe\)" + pipe_name).c_str(),
        GENERIC_READ | GENERIC_WRITE,
        0, NULL, OPEN_EXISTING, 0, NULL);
    if (h_pipe == INVALID_HANDLE_VALUE) {
        print("Failed to connect to pipe '{}'. Error: {}", wstr_to_str(pipe_name), GetLastError());
        return NULL;
    }
    logg("connected to pipe '{}' server", wstr_to_str(pipe_name));
    return h_pipe;
}
bool send_pipe_command(HANDLE h_pipe, int command) {
    DWORD bytesWritten;
    return WriteFile(h_pipe, &command, sizeof(command), &bytesWritten, NULL) && (bytesWritten == sizeof(command));
}
void process_pipe_commands(HANDLE h_pipe) {
    int command;
    DWORD bytesRead;
    while (true) {
        BOOL success = ReadFile(h_pipe, &command, sizeof(command), &bytesRead, NULL);
        if (success && bytesRead == sizeof(command)) {
            auto action = command_map.find(command);
            if (action != command_map.end()) {
                action->second();
            }
            else {
                print("Invalid command received.");
            }
        }
        else {
            print("Failed to read command. Error: {}", GetLastError());
            break;
        }
        if (end_process) {
            break;
        }
    }
}
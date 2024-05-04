#include <server.h>
#include <logger_s.h>

PROCESS_INFORMATION pi;

bool start_server() {
    STARTUPINFO si;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));
    if (!CreateProcess(LR"(.\core\server\server.exe)",
        NULL, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi)) {
        print("CreateProcess failed {}", GetLastError());
        return false;
    }
    return true;
}
void stop_server() {
    if (TerminateProcess(pi.hProcess, 0)) {
        log_server_end("server process terminated successfully");

    }
    else {
        log_server_end("Failed to terminate server process {}", GetLastError());
    }
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
}
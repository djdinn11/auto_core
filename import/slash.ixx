/*!
\file slash.ixx
\brief Manages the emptying of the Recycle Bin.
*/
export module slash;
import base;
import logger;
import print;
import clipboard;
import utils;
import <Windows.h>;

export void retrieve_and_delete_recycle_bin();

void call_slash_exe(const wstring& exe_path) {
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));
    LPWSTR szCmdline = _wcsdup(exe_path.c_str());
    if (!CreateProcess(NULL, szCmdline, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi)) {
        print("error with slash module - {}", GetLastError());
    }
    else {
        WaitForSingleObject(pi.hProcess, INFINITE);
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    }
    free(szCmdline);
}

/** \runtime */
void retrieve_and_delete_recycle_bin() {
    logg("retrieve_and_delete_recycle_bin()");
    call_slash_exe(LR"(.\core\slash\slash.exe)");
    //wstring slash_text = get_clipboard_text();
    //printnl(wstr_to_str(slash_text));
    //paste_from_clipboard();
}
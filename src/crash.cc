#include <crash.h>
#include <DbgHelp.h>
#include <clock.h>
#include <main.h>

string crash_log = R"(.\log\crash.log)";
string crash_folder = R"(.\log\crash\)";

void crash_check() {
    if (fs::exists(crash_log)) {
        print("crash bandicoot!");
        logg("crash detected");
    }
}
void restart_program(string error_report) {
    ofstream log_crash(crash_log, ios_base::app);
    if (log_crash.is_open()) {
        string crash_report = format("{}\ncrash at {} {}", error_report, get_timestamp_with_seconds(), get_datestamp());
        cerr << crash_report << endl;
        log_crash << crash_report;
        log_crash.close();
    }
    wstring restart_cmd = L"auto_core.exe";
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));
    if (CreateProcess(NULL, &restart_cmd[0], NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi)) {
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
        close_program();
        logg("restarting auto_core.exe at {}", get_datetime_stamp_with_seconds());
        log_end();
        ExitProcess(1);
    }
}
string get_crash_name() {
    string crash_name = "bandicoot_" + get_datestamp();
    string crash_path = crash_folder + crash_name + ".dmp";
    int counter = 0;
    while (fs::exists(crash_path)) {
        counter++;
        crash_name = "bandicoot_" + get_datestamp() + "_" + to_string(counter);
        crash_path = crash_folder + crash_name + ".dmp";
    }
    return crash_name;
}
void create_mini_dump(EXCEPTION_POINTERS* pExceptionPointers, const wstring& wfullPath) {
    HANDLE hFile = CreateFile(wfullPath.c_str(), GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile != NULL && hFile != INVALID_HANDLE_VALUE) {
        MINIDUMP_EXCEPTION_INFORMATION mdei;
        mdei.ThreadId = GetCurrentThreadId();
        mdei.ExceptionPointers = pExceptionPointers;
        mdei.ClientPointers = FALSE;
        MINIDUMP_TYPE mdt = static_cast<MINIDUMP_TYPE>(
            MiniDumpNormal | MiniDumpWithFullMemory |
            MiniDumpWithHandleData | MiniDumpWithUnloadedModules |
            MiniDumpWithThreadInfo);
        BOOL rv = MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(), hFile, mdt, &mdei, NULL, NULL);
        CloseHandle(hFile);
    }
}
LONG WINAPI unhandled_exception_handler(EXCEPTION_POINTERS* exceptionInfo) {
    wstring crash_folder_wstr = str_to_wstr(crash_folder);
    CreateDirectory(crash_folder_wstr.c_str(), NULL);
    string crash_dmt_name = get_crash_name();
    wstring crash_log_name = str_to_wstr(crash_dmt_name);
    wstring filepath = crash_folder_wstr + crash_log_name + L".dmp";
    create_mini_dump(exceptionInfo, filepath);
    wstring crash_folder_crash_files = crash_folder_wstr + crash_log_name + L"\\";
    CreateDirectory(crash_folder_crash_files.c_str(), NULL);
    wstring current_exe_path = LR"(.\auto_core.exe)";
    wstring copy_exe_path = crash_folder_crash_files + L"auto_core.exe";
    wstring current_pdb_path = LR"(.\visual\auto_core.pdb)";
    wstring copy_pdb_path = crash_folder_crash_files + L"auto_core.pdb";
    CopyFile(current_exe_path.c_str(), copy_exe_path.c_str(), FALSE);
    CopyFile(current_pdb_path.c_str(), copy_pdb_path.c_str(), FALSE);
    string error_report = "Unhandled exception occurred.";
    error_report += format("\nSee {} for a crash log", crash_dmt_name);
    error_report += "\nException Code: " + to_string(exceptionInfo->ExceptionRecord->ExceptionCode);
    error_report += "\nException Address: " + to_string(reinterpret_cast<uintptr_t>(exceptionInfo->ExceptionRecord->ExceptionAddress));
    restart_program(error_report);
    return EXCEPTION_EXECUTE_HANDLER;
}
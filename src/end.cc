#include <Windows.h>
#include <logger.h>
#include <main.h>
#include <numkey.h>
#include <end.h>

LRESULT CALLBACK close_procedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_QUERYENDSESSION:
        logg("close_procedure() - WM_QUERYENDSESSION");
        return TRUE;
    case WM_ENDSESSION:
        if (wParam == TRUE) {
            logg("close_procedure() - WM_ENDSESSION");
            primary = false;
            PostThreadMessage(main_thread_id, ac_numkey_1, 0, 0);
            close_program();
            return TRUE;
        }
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}
HWND close_window_hidden_init() {
    const wchar_t CLASS_NAME[] = L"Auto Core Close Window Hidden Class";
    WNDCLASS wc ={};
    wc.lpfnWndProc = close_procedure;
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = CLASS_NAME;
    RegisterClass(&wc);
    HWND hWnd = CreateWindowEx(0,
        CLASS_NAME,
        L"Auto Core Close Window Hidden",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        NULL,  
        NULL,
        wc.hInstance,
        NULL
    );
    return hWnd;
}
BOOL WINAPI console_close_event(DWORD dwType) {
    if (!program_closing) {
        switch (dwType) {
        case CTRL_CLOSE_EVENT:
            logg("console_close_event() - CTRL_CLOSE_EVENT");
            primary = false;
            PostThreadMessage(main_thread_id, ac_numkey_1, 0, 0);
            return TRUE;
        case CTRL_BREAK_EVENT:
            logg("console_close_event() - CTRL_BREAK_EVENT");
            primary = false;
            PostThreadMessage(main_thread_id, ac_numkey_1, 0, 0);
            return TRUE;
        case CTRL_C_EVENT:
            logg("console_close_event() - CTRL_C_EVENT");
            primary = false;
            PostThreadMessage(main_thread_id, ac_numkey_1, 0, 0);
            return TRUE;
        default:
            logg("console_close_event() - default");
            break;
        }
    }
    return FALSE;
}
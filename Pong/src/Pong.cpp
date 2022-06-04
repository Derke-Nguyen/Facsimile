#include <windows.h>

bool IsRunning = true;

LRESULT WinProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    
    LRESULT result = 0;

    switch (msg) {
    case WM_CLOSE:
    case WM_DESTROY:
        IsRunning = false;

    default:
        result = DefWindowProcW(hWnd, msg, wParam, lParam);
        break;
    }

    return result;
}

int WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow) {
    // window classes have associated procedures, the procedure processes messages and controls behavior and appearance
    WNDCLASSW wnd = { 0 };
    // this will force a redraw of the window if it's moved or adjusted
    wnd.style = CS_VREDRAW | CS_HREDRAW; 
    // pointer to window procedure
    wnd.lpfnWndProc = WinProcedure;
    // Name of class that will be registered 
    wnd.lpszClassName = L"GameWindowClass";

    //Fill out window class
    RegisterClassW(&wnd);

    //Create window
    HWND hwnd = CreateWindowExW(0, wnd.lpszClassName, L"Pong", WS_VISIBLE | WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 900, 600, 0, 0, 0, 0);

    while (IsRunning) {
        MSG message;
        while (PeekMessageW(&message, hwnd, 0, 0, PM_REMOVE)) {
            TranslateMessage(&message);
            DispatchMessage(&message);
        }

    }
}
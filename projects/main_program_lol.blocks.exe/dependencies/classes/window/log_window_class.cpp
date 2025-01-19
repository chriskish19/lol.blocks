#include "log_window_class.hpp"

window::log_window::log_window() {
    
}

void window::log_window::go()
{
    window_settings();
    create_window();
    SetWindowText(m_window_handle, READ_ONLY_STRING("LOG WINDOW"));
    message_pump();
}

LRESULT window::log_window::ThisWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg) {
    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        // Set text color and background
        SetTextColor(hdc, RGB(0, 0, 0));       // Black text
        SetBkColor(hdc, RGB(255, 255, 255));  // White background

        // Display the current string
        RECT rect;
        GetClientRect(hwnd, &rect);
        
        utilities::logger::logs* logs_p = m_logs.get_logs_p();
        for (size_t i = 0; i < logs_p->get_vec_log_size(); ++i) {
            DrawText(hdc, logs_p->get_log_by_index(i).c_str(), -1, &rect, DT_LEFT | DT_TOP);
        }
        
        EndPaint(hwnd, &ps);

        break;
    }
    case WM_COMMAND: {
        switch (LOWORD(wParam)) {

        } // end of switch (LOWORD(wParam))
        break;
    }

    } // end of switch (uMsg)

    // no default switches needed
    return starter::ThisWindowProc(hwnd, uMsg, wParam, lParam);
}

void window::log_window::message_pump()
{
    // Run the message loop.
    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

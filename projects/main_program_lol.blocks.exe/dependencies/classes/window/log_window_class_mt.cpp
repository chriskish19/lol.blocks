#include "log_window_class_mt.hpp"

window::log_window::log_window() {

}

void window::log_window::go()
{
    create_window();
    message_pump();
}

LRESULT window::log_window::ThisWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    return LRESULT();
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

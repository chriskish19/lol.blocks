#include "main_window_class_mt.hpp"

window::window_class_mt::~window_class_mt()
{
	if (m_thread_runner != nullptr) {
		delete m_thread_runner;
	}

    if (m_wcmt_latches != nullptr) {
        delete m_wcmt_latches;
    }
}

void window::window_class_mt::go()
{
#if ENABLE_DEEP_LOGS
    global::log_to_system_log_window(READ_ONLY_STRING("Launching master thread inside main_window_class_mt..."));
#endif
    // this-> is actually on a different instance of master_thread than run_windows_class_mt's instance
	auto j_thread_p = this->launch_master_thread(&run_windows_class_mt::threads_go, m_thread_runner);

#if ENABLE_ALL_EXCEPTIONS
    if (j_thread_p == nullptr) {
        throw errors::pointer_is_nullptr(READ_ONLY_STRING("auto j_thread_p"));
    }
#endif


#if ENABLE_DEEP_LOGS
    if (j_thread_p != nullptr) {
        global::log_to_system_log_window(READ_ONLY_STRING("master thread successfully launched inside main_window_class_mt..."));
    }
#endif
}

void window::window_class_mt::wait() noexcept
{
    // wait here
    std::mutex local_mtx;
    std::unique_lock<std::mutex> local_lock(local_mtx);
    m_wcmt_latches->m_safe_exit.wait(local_lock, [this]
        {
            return m_wcmt_latches->m_safe_exit_gate_latch.load();
        });
}

window::window_class_mt::run_windows_class_mt::~run_windows_class_mt()
{
    if (m_wm != nullptr) {
        delete m_wm;
    }
}

void window::window_class_mt::run_windows_class_mt::threads_go()
{
	// launch a first thread window
	this->launch_thread(&window_manager::windows_message_handler, m_wm);

	// creates new windows on thread_master
	this->launch_thread(&run_windows_class_mt::new_window_gate, this);

	// exit program thread
	all_windows_closed_gate();
}

void window::window_class_mt::run_windows_class_mt::all_windows_closed_gate() noexcept
{
	std::mutex local_mtx;
	std::unique_lock<std::mutex> local_lock(local_mtx);
	m_wm->m_public_all_windows_closed_signaler.wait(local_lock, [this]
		{
			return m_wm->m_all_windows_closed_gate_latch.load();
		});

	// begin to exit the program
	m_exit_new_window_gate.store(true);
	m_wm->m_latches->m_new_window_gate_latch.store(true);
	m_wm->m_latches->m_window_create_signaler.notify_all();  // get the thread moving again if its stalled
}

void window::window_class_mt::run_windows_class_mt::new_window_gate() noexcept
{
	while (m_exit_new_window_gate.load() == false) {
		std::mutex local_mtx;
		std::unique_lock<std::mutex> local_lock(local_mtx);
		m_wm->m_latches->m_window_create_signaler.wait(local_lock, [this]
			{
				return m_wm->m_latches->m_new_window_gate_latch.load();
			});
		m_wm->m_latches->m_new_window_gate_latch.store(false);

		// double check were not in a exit scenario
		if (m_exit_new_window_gate.load() == false) {
			this->launch_thread(&window_manager::windows_message_handler, m_wm);
		}
	}

	m_wm->m_latches->m_safe_exit_gate_latch.store(true);
	m_wm->m_latches->m_safe_exit.notify_all();
}

void window::window_class_mt::window_manager::windows_message_handler()
{
    m_open_window_count++;

#if USING_WIDE_STRINGS
    string window_number = std::to_wstring(m_open_window_count);
#endif

#if USING_NARROW_STRINGS
    string window_number = std::to_string(m_open_window_count);
#endif

    string new_window_name = READ_ONLY_STRING("Display Window #") + window_number;
    string new_logger_name = READ_ONLY_STRING("Logger Window #") + window_number;

    log_window* new_logger = new window_class_log_window(new_logger_name);
    new_logger->go();

    window_relative* new_window = new window_relative(new_window_name,m_latches);


#if TESTING

    dx::draw* new_dx_draw = new dx::draw(new_window->get_window_width(), new_window->get_window_height(),
        new_window->get_window_handle(),new_window_name);

    // launch the logic
    std::jthread new_window_logic_thread(&window_relative::run_window_logic_draw_primatives, new_window, new_dx_draw, new_logger);
#else

    dx::devices_11* new_dx_device = new dx::devices_11(new_window->get_window_width(), new_window->get_window_height(),
        new_window->get_window_handle(),new_window_name);

    // launch the logic
    std::jthread new_window_logic_thread(&window_relative::run_window_logic, new_window, new_dx_device, new_logger);

#endif



    // Run the message loop.
    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    m_open_window_count--;

    if (m_open_window_count.load() == 0) {
        m_all_windows_closed_gate_latch.store(true);
        m_public_all_windows_closed_signaler.notify_all();
    }

    // exit the function
    new_window->m_public_exit_run_window_logic.store(true);




    // cleanup
    if (new_logger != nullptr) {
        delete new_logger;
    }

    if (new_window != nullptr) {
        delete new_window;
    }
#if TESTING
    if (new_dx_draw != nullptr) {
        delete new_dx_draw;
    }
#else
    if (new_dx_device != nullptr) {
        delete new_dx_device;
    }
#endif
}

LRESULT window::window_class_mt::window_relative::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) noexcept
{
    // reroute to private window proc
    window_relative* p_window_rerouter = nullptr;

    if (uMsg == WM_NCCREATE)
    {
        // Store the pointer to the window instance in the user data associated with the HWND.
        CREATESTRUCT* pCreate = (CREATESTRUCT*)lParam;
        p_window_rerouter = (window_relative*)pCreate->lpCreateParams;
        SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)p_window_rerouter);
    }
    else
    {
        // Retrieve the pointer to the window instance from the user data associated with the HWND.
        p_window_rerouter = (window_relative*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
    }

    if (p_window_rerouter)
    {
        return p_window_rerouter->PrivateWindowProc(hwnd, uMsg, wParam, lParam);
    }
    else
    {
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}

LRESULT window::window_class_mt::window_relative::PrivateWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) noexcept
{
    switch (uMsg) {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;

        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);

            // All painting occurs here, between BeginPaint and EndPaint.

            FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

            EndPaint(hwnd, &ps);

            break;
        }
        case WM_COMMAND: {
            switch (LOWORD(wParam)) {
                case static_cast<int>(window_menu_ids::Create): // menu button called "Create New Window"
                {
                    // signal to window_class_mt to create a new thread window
                    m_latches->m_new_window_gate_latch.store(true);
                    m_latches->m_window_create_signaler.notify_all();
                    break;
                }
                case static_cast<int>(window_menu_ids::view_log_window):
                {
                    m_show_log_window = !m_show_log_window;
                    view_log_window(m_show_log_window);
                    break;
                }
                default:
                    return DefWindowProc(hwnd, uMsg, wParam, lParam);
            } // end of switch (LOWORD(wParam))
            break;
        }
        case WM_CLOSE: 
        {
            // signal to window_class_mt to kill the thread??
            break;
        }

    } // end of switch (uMsg)

    // no default switches needed
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

void window::window_class_mt::window_relative::register_class() noexcept
{
    m_wc.lpfnWndProc = WindowProc;
    m_wc.hInstance = m_hinst;
    m_wc.lpszClassName = m_c_name.c_str();

    RegisterClass(&m_wc);
}

window::window_class_mt::window_relative::window_relative(const string& title, latch* latches_p) noexcept
    :m_title(title),m_latches(latches_p)
{
    if (m_latches->m_is_class_registered == false) {
        this->register_class();
        m_latches->m_is_class_registered.store(true);
    }

    m_window_handle = CreateWindowEx(
        0,                                  // Optional window styles.
        m_c_name.c_str(),                     // Window class
        m_title.c_str(),                      // Window text
        WS_OVERLAPPEDWINDOW,                // Window style

        // Size and position
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

        NULL,                                           // Parent window    
        NULL,                                           // Load the menu here
        m_hinst,                                          // Instance handle
        this // Additional application data
    );

    ShowWindow(m_window_handle, SW_SHOW);

    this->build_relative_window_menu_bar();
}

void window::window_class_mt::window_relative::change_title(const string& new_title) noexcept
{
    SetWindowText(this->m_window_handle, new_title.c_str());
}

errors::codes window::window_class_mt::window_relative::build_relative_window_menu_bar()
{
#if ENABLE_FULL_OPTIMIZATIONS
    HMENU hMenu = CreateMenu();
    HMENU hFileMenu = CreateMenu();
    HMENU hHelpMenu = CreateMenu();
    HMENU h_view_menu = CreateMenu();
    AppendMenu(hHelpMenu, MF_STRING, static_cast<int>(window_menu_ids::Help), READ_ONLY_STRING("&Help"));
    AppendMenu(hFileMenu, MF_STRING, static_cast<int>(window_menu_ids::Create), READ_ONLY_STRING("&Create New Window"));
    AppendMenu(h_view_menu, MF_STRING, static_cast<int>(window_menu_ids::view_log_window), READ_ONLY_STRING("&Log window"));
    AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hFileMenu, READ_ONLY_STRING("&File"));
    AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hHelpMenu, READ_ONLY_STRING("&Help"));
    AppendMenu(hMenu, MF_POPUP, (UINT_PTR)h_view_menu, READ_ONLY_STRING("&View"));
    SetMenu(this->m_window_handle, hMenu);
    return errors::codes::success;
#endif

#if ENABLE_FULL_DEBUG
    HMENU hMenu = CreateMenu();
    if (hMenu == nullptr) {
        string p_name = READ_ONLY_STRING("HMENU hMenu = CreateMenu();");
#if ENABLE_DEEP_LOGS
        // log to SYSTEM_LOG_WINDOW
        global::log_to_system_log_window(p_name + READ_ONLY_STRING("Failed to create menu handle."));
#endif // ENABLE_DEEP_LOGS

#if ENABLE_ALL_EXCEPTIONS
        throw errors::win32_menu_error();
#endif // ENABLE_ALL_EXCEPTIONS
        return errors::codes::win32_menu_error;
    }


    HMENU hFileMenu = CreateMenu();
    if (hFileMenu == nullptr) {
        string p_name = READ_ONLY_STRING("HMENU hFileMenu = CreateMenu();");
#if ENABLE_DEEP_LOGS
        // log to SYSTEM_LOG_WINDOW
        global::log_to_system_log_window(p_name + READ_ONLY_STRING("Failed to create menu handle."));
#endif // ENABLE_DEEP_LOGS

#if ENABLE_ALL_EXCEPTIONS
        throw errors::win32_menu_error();
#endif // ENABLE_ALL_EXCEPTIONS
        return errors::codes::win32_menu_error;
    }


    HMENU hHelpMenu = CreateMenu();
    if (hHelpMenu == nullptr) {
        string p_name = READ_ONLY_STRING("HMENU hHelpMenu = CreateMenu();");
#if ENABLE_DEEP_LOGS
        // log to SYSTEM_LOG_WINDOW
        global::log_to_system_log_window(p_name + READ_ONLY_STRING("Failed to create menu handle."));
#endif // ENABLE_DEEP_LOGS

#if ENABLE_ALL_EXCEPTIONS
        throw errors::win32_menu_error();
#endif // ENABLE_ALL_EXCEPTIONS
        return errors::codes::win32_menu_error;
    }


    HMENU h_view_menu = CreateMenu();
    if (h_view_menu == nullptr) {
        string p_name = READ_ONLY_STRING("HMENU h_view_menu = CreateMenu();");
#if ENABLE_DEEP_LOGS
        // log to SYSTEM_LOG_WINDOW
        global::log_to_system_log_window(p_name + READ_ONLY_STRING("Failed to create menu handle."));
#endif // ENABLE_DEEP_LOGS

#if ENABLE_ALL_EXCEPTIONS
        throw errors::win32_menu_error();
#endif // ENABLE_ALL_EXCEPTIONS
        return errors::codes::win32_menu_error;
    }


    if (AppendMenu(hHelpMenu, MF_STRING, static_cast<int>(window_menu_ids::Help), READ_ONLY_STRING("&Help")) == FALSE) {
#if ENABLE_DEEP_LOGS
        global::log_to_system_log_window(READ_ONLY_STRING("Failed to append menu handle."));
#endif

#if ENABLE_ALL_EXCEPTIONS
        throw errors::win32_menu_error();
#endif // ENABLE_ALL_EXCEPTIONS
        return errors::codes::win32_menu_error;
    }



    AppendMenu(hFileMenu, MF_STRING, static_cast<int>(window_menu_ids::Create), READ_ONLY_STRING("&Create New Window"));
    AppendMenu(h_view_menu, MF_STRING, static_cast<int>(window_menu_ids::view_log_window), READ_ONLY_STRING("&Log window"));
    AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hFileMenu, READ_ONLY_STRING("&File"));
    AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hHelpMenu, READ_ONLY_STRING("&Help"));
    AppendMenu(hMenu, MF_POPUP, (UINT_PTR)h_view_menu, READ_ONLY_STRING("&View"));
    SetMenu(this->m_window_handle, hMenu);

    return errors::codes::success;
#endif // ENABLE_FULL_DEBUG

}

void window::window_class_mt::window_relative::run_window_logic(dx::devices_11* dx11_device_p, log_window* log_p)
{
#if ENABLE_ALL_EXCEPTIONS
    if (log_p == nullptr) {
        throw errors::pointer_is_nullptr(READ_ONLY_STRING("log_window* log_p"));
    }
#endif
    // makes these safe to dereference in here since its run on a thread
    m_log_window_p.store(log_p);
    m_dx11_device_p.store(dx11_device_p);

    // graphics stuff!!
    m_swp_p = m_dx11_device_p.load()->get_swap_p();

#if ENABLE_ALL_EXCEPTIONS
    if (m_swp_p == nullptr) {
        throw errors::pointer_is_nullptr(READ_ONLY_STRING("m_swp_p = dx11_device_p->get_swap_p()"));
    }
#endif

    while (m_public_exit_run_window_logic.load() == false) {
        m_swp_p->Present(1u, 0u);
    }

}

#if TESTING
void window::window_class_mt::window_relative::run_window_logic_draw_primatives(dx::draw* dx_draw_p, log_window* log_p)
{
    utilities::timer game_time;

#if ENABLE_ALL_EXCEPTIONS
    if (log_p == nullptr) {
        throw errors::pointer_is_nullptr(READ_ONLY_STRING("log_window* log_p"));
    }
    if (dx_draw_p == nullptr) {
        throw errors::pointer_is_nullptr(READ_ONLY_STRING("dx::draw* dx_draw_p"));
    }
#endif
    // makes these safe to dereference in here since its run on a thread
    m_log_window_p.store(log_p);
    m_dx_draw_p.store(dx_draw_p);

    // graphics stuff!!
    m_swp_p = m_dx_draw_p.load()->get_swap_p();

#if ENABLE_ALL_EXCEPTIONS
    if (m_swp_p == nullptr) {
        throw errors::pointer_is_nullptr(READ_ONLY_STRING("m_swp_p = dx11_device_p->get_swap_p()"));
    }
#endif

    while (m_public_exit_run_window_logic.load() == false) {
        
        const float c = std::sin(game_time.peek()) / 2.0f + 0.5f;
        m_dx_draw_p.load()->clear_buffer(c, c, 1.0f);

        m_swp_p->Present(1u, 0u);
    }
}
#endif

UINT window::window_class_mt::window_relative::get_window_width()
{
    RECT rc = {};
    if (GetClientRect(m_window_handle, &rc) == FALSE) {
#if ENABLE_ALL_EXCEPTIONS
        throw errors::get_client_rect_failed();
#endif

#if ENABLE_DEEP_LOGS
        global::log_to_system_log_window(READ_ONLY_STRING
        ("GetClientRect(m_window_handle, &rc) failed... trying to get window width."));
#endif
    }

    return rc.right - rc.left;
}

UINT window::window_class_mt::window_relative::get_window_height()
{
    RECT rc = {};
    if (GetClientRect(m_window_handle, &rc) == FALSE) {
#if ENABLE_ALL_EXCEPTIONS
        throw errors::get_client_rect_failed();
#endif

#if ENABLE_DEEP_LOGS
        global::log_to_system_log_window(READ_ONLY_STRING
        ("GetClientRect(m_window_handle, &rc) failed... trying to get window height."));
#endif
    }

    return rc.bottom - rc.top;
}

errors::codes window::window_class_mt::window_relative::view_log_window(bool show)
{
    HWND log_window_handle = m_log_window_p.load()->get_window_handle();
    
    // Get the handle to the menu
    HMENU hMenu = GetMenu(log_window_handle);
    HMENU hSubMenu = GetSubMenu(hMenu, 0); // View menu (first submenu)

    // Update the checkmark
    CheckMenuItem(hSubMenu, static_cast<int>(window_menu_ids::view_log_window),
        MF_BYCOMMAND | (show ? MF_CHECKED : MF_UNCHECKED));

    // Perform action based on the state
    if (show == true) {
        // Show the log window
        ShowWindow(log_window_handle, SW_SHOW);
    }
    else {
        // Hide the log window
        ShowWindow(log_window_handle, SW_HIDE);
    }
    
    
    return errors::codes::success;
}


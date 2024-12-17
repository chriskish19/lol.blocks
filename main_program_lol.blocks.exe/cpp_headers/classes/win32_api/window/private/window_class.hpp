// window class responsible for managing window creation
// supports multiple threads and is non blocking 

#ifndef SOURCE_WINDOW_CLASS_HPP
#define SOURCE_WINDOW_CLASS_HPP

class window_relative : public log_info{
public:
	window_relative() = default;

	window_relative(std::wstring const& c_name, std::wstring const& title, HINSTANCE hinst,HWND main_handle) noexcept;

	~window_relative();

	void change_title(std::wstring const& new_title) noexcept;
	const HWND get_window_handle() noexcept { return m_window_handle; }
	const std::thread::id get_id() noexcept { return m_relative_id; }
	void set_thread_p(std::thread* new_pThread) noexcept { m_p_thread = new_pThread; }
	std::thread* get_thread_p() noexcept { return m_p_thread; }

	std::atomic<bool>* m_public_p_running_logic = new std::atomic<bool>(true);
private:
	HWND m_window_handle = nullptr;
	std::thread::id m_relative_id = std::thread::id();
	std::thread* m_p_thread = nullptr;
};

class window_create : public log_info{
public:
	window_create() = default;

	window_create(std::wstring const& title) noexcept;

	~window_create();

	static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) noexcept;

	HWND get_main_window_handle() noexcept { return m_main_window_handle; }

	unsigned int get_open_window_count() noexcept { return m_open_window_count; }

	std::mutex m_public_mtx_open_window_count;
	std::condition_variable m_public_cv_open_window_count;
	std::atomic<bool> m_public_open_window_count_gate_state = false;

	std::atomic<bool>* m_public_p_running_logic = new std::atomic<bool>(true);
private:
	LRESULT CALLBACK PrivateWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) noexcept;


	void window_settings() noexcept;
	void create_relative() noexcept;
	void close_relative() noexcept;
	void run_relative_message_pump(std::thread::id this_thread_id) noexcept;
	void run_logic_changes(window_relative* active_open_window) noexcept;
	
	HWND m_main_window_handle = nullptr;
	WNDCLASS m_wc = {};
	HINSTANCE m_hinst = GetModuleHandle(NULL);
	std::wstring m_c_name = L"Example mt_window";
	std::wstring m_title;
	std::unordered_map<std::thread::id, window_relative*> m_relative_mp = {};
	std::unordered_map<std::thread*, window_relative*> m_thread_mp = {};


	
	std::condition_variable m_cv_window_created;
	std::atomic<bool> m_window_created_gate_state = false;

	
	std::condition_variable m_cv_window_proc_case_ID_NEWWINDOW_CREATE;
	std::atomic<bool> m_window_proc_case_ID_NEWWINDOW_CREATE = false;

	unsigned int m_open_window_count = 0; 
};


// SOURCE_WINDOW_CLASS_HPP
#endif


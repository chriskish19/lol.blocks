#ifndef SOURCE_WINDOW_CLASS_HPP
#define SOURCE_WINDOW_CLASS_HPP

// stl
#include "main_program_lol.blocks.exe/dependencies/stl/stl_macro_definitions.hpp"

// windows api
#include "main_program_lol.blocks.exe/dependencies/win32api/windows_includes.hpp"

// direct x api
#include "main_program_lol.blocks.exe/dependencies/dx12api/directx_includes.hpp"

// class utilities dependencies
#include "main_program_lol.blocks.exe/dependencies/classes/utilities/logging_sys.hpp"
#include "main_program_lol.blocks.exe/dependencies/classes/utilities/lol.blocks_error_codes.hpp"
#include "main_program_lol.blocks.exe/dependencies/classes/utilities/lol.exceptions.hpp"
#include "main_program_lol.blocks.exe/dependencies/classes/utilities/lol.singleton_manager.hpp"
#include "main_program_lol.blocks.exe/dependencies/classes/utilities/memory_heap_sys.hpp"

namespace main_lol_blocks_exe{
	enum class main_window_menu_ids {
		File=0,
		Help,
		Create
	};


	class window_relative {
	public:
		window_relative() = default;

		window_relative(const std::wstring& c_name,const std::wstring& title, HINSTANCE hinst, HWND main_handle) noexcept;

		~window_relative();

		void change_title(const std::wstring& new_title) noexcept;
		const HWND get_window_handle() noexcept { return m_window_handle; }
		const std::thread::id get_id() noexcept { return m_relative_id; }
		void set_thread_p(std::thread* new_pThread) noexcept { m_p_thread = new_pThread; }
		std::thread* get_thread_p() noexcept { return m_p_thread; }

		std::atomic<bool>* m_public_p_running_logic = new std::atomic<bool>(true);

		utilities::lolblock_ec::codes build_relative_window_menu_bar() noexcept;
	private:
		HWND m_window_handle = nullptr;
		std::thread::id m_relative_id = std::thread::id();
		std::thread* m_p_thread = nullptr;

		win32gui::log_window* m_logging_window = nullptr;
	};

	// this is a singleton!!
	class window_create {
	public:
		inline static window_create* m_window_create_instance=nullptr;

		inline static window_create* get_me_a_window_create_p() noexcept {
			if (m_window_create_instance == nullptr) {
				m_window_create_instance = new window_create(L"main window,lol.blocks");
			}
			return m_window_create_instance;

		}


		~window_create();

		static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) noexcept;

		HWND get_main_window_handle() noexcept { return m_main_window_handle; }

		unsigned int get_open_window_count() noexcept { return m_open_window_count; }

		std::mutex m_public_mtx_open_window_count;
		std::condition_variable m_public_cv_open_window_count;
		std::atomic<bool> m_public_open_window_count_gate_state = false;

		std::atomic<bool>* m_public_p_running_logic = new std::atomic<bool>(true);
	private:
		// dummy constructor for blank objects...
		window_create() = default;

		// Use this constructor for actual window creation!
		window_create(const std::wstring& title) noexcept;


		utilities::lolblock_ec::codes build_menu_bar() noexcept;

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

		win32gui::log_window* m_logging_window = nullptr;
	};
}


// SOURCE_WINDOW_CLASS_HPP
#endif


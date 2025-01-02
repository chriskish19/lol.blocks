#ifndef SOURCE_WINDOW_CLASS_HPP
#define SOURCE_WINDOW_CLASS_HPP

// include win32gui
#include "win32gui.include/win32gui.include.hpp"

// stl
#include "main_program_lol.blocks.exe/dependencies/stl/stl_macro_definitions.hpp"

// windows api
#include "main_program_lol.blocks.exe/dependencies/win32api/windows_includes.hpp"

// class dependencies
#include "main_program_lol.blocks.exe/dependencies/classes/utilities/lol.blocks_error_codes.hpp"

namespace main_lol_blocks_exe{
	extern std::condition_variable* m_public_window_create_signaler;
	extern std::atomic<bool>* m_public_new_window_gate_latch;
	
	enum class main_window_menu_ids {
		File,
		Help,
		Create
	};


	class window_relative {
	public:
		window_relative() = default;

		window_relative(const std::wstring& title) noexcept;

		~window_relative();

		void change_title(const std::wstring& new_title) noexcept;
		const HWND get_window_handle() noexcept { return m_window_handle; }
		static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) noexcept;
		utilities::lolblock_ec::codes build_relative_window_menu_bar() noexcept;
	private:
		bool m_is_class_registered = false;

		HWND m_window_handle = nullptr;

		LRESULT CALLBACK PrivateWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) noexcept;

		WNDCLASS m_wc = {};
		std::wstring m_c_name = L"Example mt_window";
		std::wstring m_title = L"Happy Window";
		HINSTANCE m_hinst = GetModuleHandle(NULL);

		void register_class() noexcept {
			m_wc.lpfnWndProc = WindowProc;
			m_wc.hInstance = m_hinst;
			m_wc.lpszClassName = m_c_name.c_str();

			RegisterClass(&m_wc);
		}

		
	};

	// this is a singleton!!
	class window_manager {
	public:
		inline static window_manager* get_me_a_window_create_p() noexcept {
			if (m_window_create_instance == nullptr) {
				m_window_create_instance = new window_manager();
			}
			return m_window_create_instance;
		}

		~window_manager();

		void windows_message_handler() noexcept {
			m_open_window_count++;
			
			window_relative new_window(L"New Window");

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
		}

		std::atomic<unsigned int> m_open_window_count = 0;
		std::atomic<bool> m_all_windows_closed_gate_latch = false;
		std::mutex m_all_windows_close_same_time;
		std::atomic<bool>* m_new_window_relative_gate_p = m_public_new_window_gate_latch;
		std::condition_variable* m_create_window_signal = m_public_window_create_signaler;
		std::condition_variable m_public_all_windows_closed_signaler;


	private:
		window_manager() = default;

		inline static window_manager* m_window_create_instance = nullptr;
	};
}


// SOURCE_WINDOW_CLASS_HPP
#endif


#ifndef SOURCE_WINDOW_CLASS_HPP
#define SOURCE_WINDOW_CLASS_HPP

// stl
#include "main_program_lol.blocks.exe/dependencies/stl/stl_macro_definitions.hpp"

// windows api
#include "main_program_lol.blocks.exe/dependencies/win32api/windows_includes.hpp"

// global variables
#include "main_program_lol.blocks.exe/dependencies/global/globals.hpp"

// class dependencies
#include "main_program_lol.blocks.exe/dependencies/classes/utilities/lol.blocks_error_codes.hpp"

namespace window{
	
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

		std::atomic<bool> m_public_exit_run_window_logic = false;
		void run_window_logic() noexcept {
			std::wstring new_title = L"Evil Window!";
			const unsigned int star_limit = 50;
			while (m_public_exit_run_window_logic.load() == false) {
				new_title = new_title + L"*";

				if (new_title.size() > star_limit) {
					new_title = L"Evil Window!";
				}

				std::this_thread::sleep_for(std::chrono::milliseconds(50));

				this->change_title(new_title);
			}
		}
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

			// launch the logic
			std::jthread new_window_logic_thread(&window_relative::run_window_logic, &new_window);

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
			new_window.m_public_exit_run_window_logic.store(true);
		}

		std::atomic<unsigned int> m_open_window_count = 0;
		std::atomic<bool> m_all_windows_closed_gate_latch = false;
		std::mutex m_all_windows_close_same_time;
		std::condition_variable m_public_all_windows_closed_signaler;


	private:
		window_manager() = default;

		inline static window_manager* m_window_create_instance = nullptr;
	};
}


// SOURCE_WINDOW_CLASS_HPP
#endif


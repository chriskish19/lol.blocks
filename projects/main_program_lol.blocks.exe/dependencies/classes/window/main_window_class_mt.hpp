#ifndef WINDOW_CLASS_MT_HPP
#define WINDOW_CLASS_MT_HPP

// stl
#include "main_program_lol.blocks.exe/dependencies/stl/stl_macro_definitions.hpp"

// windows api
#include "main_program_lol.blocks.exe/dependencies/win32api/windows_includes.hpp"

// error handling
#include "main_program_lol.blocks.exe/errors/lol.codes.hpp"

// class dependencies
#include "main_program_lol.blocks.exe/dependencies/classes/utilities/thread_manager.hpp"

namespace window {
	
	class window_class_mt: public utilities::thread_master{
	public:
		window_class_mt() = default;
		~window_class_mt();
		void go(); // call this function with actual system main thread
		void wait() noexcept; // call this function with actual system main thread, safely waits...
	private:
		class latch {
		public:
			std::condition_variable m_safe_exit;
			std::atomic<bool> m_safe_exit_gate_latch = false;
			std::condition_variable m_window_create_signaler;
			std::atomic<bool> m_new_window_gate_latch = false;
			std::atomic<bool> m_is_class_registered = false;
		};
	public:
		latch* m_wcmt_latches = new latch;
	private:
		class window_relative {
		public:
			window_relative() = default;
			window_relative(const std::wstring& title,latch* latches_p) noexcept;
			void change_title(const std::wstring& new_title) noexcept;
			const HWND get_window_handle() noexcept { return m_window_handle; }
			static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) noexcept;
			errors::codes build_relative_window_menu_bar() noexcept;
			void run_window_logic() noexcept;
			std::atomic<bool> m_public_exit_run_window_logic = false;
		private:
			LRESULT CALLBACK PrivateWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) noexcept;
			void register_class() noexcept;
			HWND m_window_handle = nullptr;
			WNDCLASS m_wc = {};
			std::wstring m_c_name = L"Example mt_window";
			std::wstring m_title = L"Happy Window";
			HINSTANCE m_hinst = GetModuleHandle(NULL);
			latch* m_latches;

			enum class window_menu_ids {
				File,
				Help,
				Create
			};
		};

		class window_manager {
		public:
			window_manager(latch* latches_p) noexcept 
			:m_latches(latches_p){}

			window_manager() = default;
			void windows_message_handler() noexcept;
			std::atomic<unsigned int> m_open_window_count = 0;
			std::atomic<bool> m_all_windows_closed_gate_latch = false;
			std::mutex m_all_windows_close_same_time;
			std::condition_variable m_public_all_windows_closed_signaler;
			latch* m_latches;
		};

		class run_windows_class_mt : public utilities::thread_master {
		public:
			run_windows_class_mt(latch* latches_p) noexcept
			:m_wm(new window_manager(latches_p)){}

			run_windows_class_mt() = default;
			~run_windows_class_mt();

			void threads_go();
			void all_windows_closed_gate() noexcept;
			void new_window_gate() noexcept;
		private:
			std::atomic<bool> m_exit_new_window_gate = false;
			window_manager* m_wm;
		};

		run_windows_class_mt* m_thread_runner = new run_windows_class_mt(m_wcmt_latches);

	};
}

// WINDOW_CLASS_MT_HPP
#endif
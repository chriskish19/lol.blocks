/****************************************************************
	Header: main_window_class_mt.hpp

	Purpose: handles the win32 window system. Creates windows that
			 run on seperate threads. Each with its own message 
			 pump and directx11 device.

****************************************************************/


#ifndef WINDOW_CLASS_MT_HPP
#define WINDOW_CLASS_MT_HPP

// stl
#include "main_program_lol.blocks.exe/dependencies/stl/stl_macro_definitions.hpp"

// windows api
#include "main_program_lol.blocks.exe/dependencies/win32api/windows_includes.hpp"

// error handling
#include "main_program_lol.blocks.exe/errors/lol.codes.hpp"

// globals
#include "main_program_lol.blocks.exe/global/globals.hpp"

// class dependencies
#include "main_program_lol.blocks.exe/dependencies/classes/utilities/thread_manager.hpp"
#include "main_program_lol.blocks.exe/dependencies/classes/window/log_window_class.hpp"
#include "main_program_lol.blocks.exe/dependencies/classes/utilities/timer.hpp"
#include "main_program_lol.blocks.exe/dependencies/classes/window/window_class_log_window.hpp"

// dx class dependencies
#include "main_program_lol.blocks.exe/dx/dx_device_init.hpp"
#include "main_program_lol.blocks.exe/dx/draw.hpp"

// lol api
#include "main_program_lol.blocks.exe/dependencies/classes/utilities/lol.api.hpp"



namespace window {
	
	class window_class_mt: public utilities::thread_master{
	public:
		window_class_mt()= default;
		~window_class_mt();
		
		// call this function with actual system main thread
		void go(); 

		// call this function with actual system main thread, safely waits...
		// waits until all window_relative windows are closed
		void wait() noexcept; 
	
	private:
		// class global object
		// mechansims for safe multithreading in window_class_mt
		// we create windows on new threads so we need to know whats happended
		class latch {
		public:
			// when its safe to exit
			std::condition_variable m_safe_exit;
			std::atomic<bool> m_safe_exit_gate_latch = false;


			std::condition_variable m_window_create_signaler;
			std::atomic<bool> m_new_window_gate_latch = false;
		};
	public:
		latch* m_wcmt_latches = new latch;
	private:
		class window_relative {
		public:
			// default constructor: currently not used
			window_relative() = default;

			// constructor that is currently being used to build win32 windows
			window_relative(const string& title,latch* latches_p);

			// clean up new objects
			~window_relative();


			void change_title(const string& new_title) noexcept;
			HWND get_window_handle() noexcept { return m_window_handle; }
			static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
			
			// call this function once to build the win32 menu
			// on a window_relative
			errors::codes build_relative_window_menu_bar();

			// runs the display window rendering
			void run_window_logic(dx::devices_11* dx11_device_p, log_window* log_p);

			// testing drawing simple shapes (triangle, cube etc..)
#if TESTING_SIMPLE_DRAW
			void run_window_logic_draw_primatives(dx::draw* dx_draw_p, log_window* log_p);
#endif

			// while loop boolean variable in run_window_logic()
			// also run_window_logic_draw_primitives()
			std::atomic<bool> m_public_exit_run_window_logic = false;

			// returns width of window_relative
			// calls GetClientRect() (not the fastest)
			UINT get_window_width();

			// returns height of window_relative
			// calls GetClientRect() (not the fastest)
			UINT get_window_height();
		private:
			// return value from registering the class
			inline static std::atomic<ATOM> m_class_atm = 0;

			// this is for the log window menu button
			bool m_show_log_window = false;
			errors::codes view_log_window(bool show);

			// main window procedure
			LRESULT CALLBACK PrivateWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

			// calls RegisterClass(&m_wc);
			void register_class();

			// HWND
			HWND m_window_handle = nullptr;

			// window class description
			WNDCLASS m_wc = {};

			// unique window class name
			string m_c_name = READ_ONLY_STRING("main_window_class_mt_window");

			// title of the window (window bar name)
			string m_title;

			// main exe handle
			HINSTANCE m_hinst = GetModuleHandle(NULL);

			// safe multithreading mechanisms
			latch* m_latches;

			// set inside run_window_logic()
			// these pointers allow drawing and changes to the window
			// wrapped in std::atomic for safe accessing
			/*
			
				std::atomic<log_window*> m_log_window_p = nullptr;
				std::atomic<dx::devices_11*> m_dx11_device_p = nullptr;
				std::atomic<dx::draw*> m_dx_draw_p = nullptr;

			*/

			// log window that receives messages from display window (window_relative)
			std::atomic<log_window*> m_log_window_p = nullptr;

			// main direct x device class pointer
			std::atomic<dx::devices_11*> m_dx11_device_p = nullptr;

			// main drawing simple shapes for testing purpose
			std::atomic<dx::draw*> m_dx_draw_p = nullptr;

			// window menu button ids
			enum class window_menu_ids {
				File,
				Help,
				Create,
				View,
				view_log_window
			};

			// swap chain pointer for drawing purposes
			IDXGISwapChain* m_swp_p = nullptr;
		};

		class window_manager {
		public:
			window_manager(latch* latches_p) noexcept 
			:m_latches(latches_p){}

			window_manager() = default;
			void windows_message_handler();
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
			
			// allocated with new in constructor
			window_manager* m_wm;
		};

		// handles the threads that run the functions needed for window_class_mt
		run_windows_class_mt* m_thread_runner = new run_windows_class_mt(m_wcmt_latches);

	};
}

// WINDOW_CLASS_MT_HPP
#endif
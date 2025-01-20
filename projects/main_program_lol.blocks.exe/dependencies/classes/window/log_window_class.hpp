#pragma once

// type settings
#include "main_program_lol.blocks.exe/dependencies/macros/type_settings.hpp"

// stl
#include "main_program_lol.blocks.exe/dependencies/stl/stl_macro_definitions.hpp"

// windows api
#include "main_program_lol.blocks.exe/dependencies/win32api/windows_includes.hpp"

// class dependencies
#include "main_program_lol.blocks.exe/dependencies/classes/window/starter.hpp"
#include "main_program_lol.blocks.exe/dependencies/classes/utilities/thread_manager.hpp"
#include "main_program_lol.blocks.exe/dependencies/classes/utilities/logging_sys.hpp"

namespace window {
	class log_window :
		public starter{
	public:
		log_window();
		~log_window();
		void go();
	private:
		void create_window() override;
		LRESULT CALLBACK ThisWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) override;
		void message_pump() override;
		void draw_log_window();
		void set_font(LONG size);
		void window_size_changed(HWND hwnd);
		utilities::logger m_logs;
		RECT m_client_window_size = {};
		HFONT m_hFont;
		LONG m_font_size = 20;
		LONG m_line_height;

		class scrolling {
		public:
			scrolling(utilities::logger::logs* log_p,LONG line_height);

			void set_scroll(HWND hwnd);
			void handle_scroll(HWND hwnd, WPARAM wParam);
			void handle_mouse_wheel(HWND hwnd, WPARAM wParam);
			void set_line_rect(const RECT& client, const LONG& offset);
			int get_scroll_position() { return m_scroll_pos; }


			RECT m_line_rect = {};
			// left
			// top
			// right
			// bottom
		private:
			size_t m_number_of_log_lines;
			int m_scroll_pos = 0;
			int m_wheel_delta_accum = 0;
			LONG m_line_height;
		};

		scrolling* m_scroll_p = nullptr;
	};
}
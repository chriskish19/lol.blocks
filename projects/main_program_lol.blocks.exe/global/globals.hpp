/****************************************************************
	Header: globals.hpp

	Purpose: global objects/variables/functions needed for
			 lol.blocks.

****************************************************************/

// NOTE: See class headers for where globals can and cannot be used.

#pragma once

// all macros
#include "main_program_lol.blocks.exe/macros/include/lol.macros.include.hpp"

// all external library headers
#include "main_program_lol.blocks.exe/pch/includes/external.hpp"

// error codes
#include "main_program_lol.blocks.exe/errors/lol.codes.hpp"

// class dependencies
#include "main_program_lol.blocks.exe/classes/window/logging/log_window_class.hpp"
#include "main_program_lol.blocks.exe/classes/window/logging/system_log_window.hpp"



// log window
namespace global {
	
	class global_manager {
	public:
		global_manager() {
			// 2 pointers in this one
			std::atomic<window::log_window*>* m_log_window_p = 
				new std::atomic<window::log_window*>(new window::system_log_window);
			
			// check atomic pointer
			if (m_log_window_p != nullptr) {
				// memory alloc success
				m_new_alloc_count++;
			}

			// check actual window::log_window*
			auto actual_system_log_window_p = m_log_window_p->load();
			if (actual_system_log_window_p != nullptr) {
				m_new_alloc_count++;
			}

			// check atomic boolean pointer
			std::atomic<bool>* m_all_display_windows_closed = 
				new std::atomic<bool>(false);
			if (m_all_display_windows_closed != nullptr) {
				// memory alloc success
				m_new_alloc_count++;
			}
		}

		~global_manager() {
			// actual log pointer
			if (m_log_window_p->load() != nullptr) {
				auto actual_log_window_p = m_log_window_p->load();
				delete actual_log_window_p;
				actual_log_window_p = nullptr;
				m_new_alloc_count--;
			}

			// std::atomic pointer
			if (m_log_window_p != nullptr) {
				delete m_log_window_p;
				m_log_window_p = nullptr;
				m_new_alloc_count--;
			}

			if (m_all_display_windows_closed != nullptr) {
				delete m_all_display_windows_closed;
				m_all_display_windows_closed = nullptr;
				m_new_alloc_count--;
			}
		}

		// send a message to the system log window
		void log_to_system_log_window(const string& message) {
			errors::codes code;

			// a message sent to the system log window
			auto log_p = m_log_window_p->load()->get_logs_p();

			code = log_p->load()->log_message(message);
			errors::handle_basic_error_codes(code);

			errors::win32_codes w32code = m_log_window_p->load()->update();
			errors::handle_win32_error_codes(w32code);
		}

		size_t get_new_alloc_count() { return m_new_alloc_count; }
		std::atomic<window::log_window*>* get_atomicwrapped_system_log_window_p() { return m_log_window_p; }
		std::atomic<bool>* get_display_windows_closed_p() { return m_all_display_windows_closed; }
	protected:
		size_t m_new_alloc_count = 0;

		std::atomic<window::log_window*>* m_log_window_p = nullptr;
		std::atomic<bool>* m_all_display_windows_closed = nullptr;
	};

	class global_error_check : public global_manager{
	public:
		global_error_check() = default;

		errors::any_two<errors::codes, errors::win32_codes> check_for_errors() {
			auto manager = new global_manager;

			if (manager->get_new_alloc_count() != this->get_new_alloc_count()) {
				delete manager;

				return errors::any_two<errors::codes, errors::win32_codes>
					(errors::codes::memory_leak, errors::win32_codes::null);
			}

			delete manager;
			return errors::any_two<errors::codes, errors::win32_codes>
				(errors::codes::success, errors::win32_codes::null);
		}

		~global_error_check() = default;
	};

	extern std::unique_ptr<global_manager> system_global_manager_p;
}

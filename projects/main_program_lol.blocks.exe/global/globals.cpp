#include "globals.hpp"

namespace global {
	// give memory to the extern pointers declared in global.hpp
	std::atomic<window::log_window*>* log_window_p = new std::atomic<window::log_window*>(new window::system_log_window);
	std::atomic<bool>* all_display_windows_closed = new std::atomic<bool>(false);
	

	void log_to_system_log_window(const string& message)
	{
		errors::codes code;
		
		// a message sent to the system log window
		auto log_p = global::log_window_p->load()->get_logs_p();

		code = log_p->load()->log_message(message);
		errors::handle_error_codes(code);

		code = global::log_window_p->load()->update();
		errors::handle_error_codes(code);
	}

	void clean_up()
	{
		// actual log pointer
		if (log_window_p->load() != nullptr) {
			auto actual_log_window_p = log_window_p->load();
			delete actual_log_window_p;
		}

		// std::atomic pointer
		if (log_window_p != nullptr) {
			delete log_window_p;
		}

		if (all_display_windows_closed != nullptr) {
			delete all_display_windows_closed;
		}
	}
}
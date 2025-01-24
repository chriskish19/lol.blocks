#include "globals.hpp"

namespace global {
	std::atomic<window::log_window*>* log_window_p = new std::atomic<window::log_window*>(new window::system_log_window);
	std::atomic<bool>* all_display_windows_closed = new std::atomic<bool>(false);
	
	
	
	void clean_up()
	{
		if (log_window_p->load() != nullptr) {
			auto actual_log_window_p = log_window_p->load();
			delete actual_log_window_p;
		}

		if (log_window_p != nullptr) {
			delete log_window_p;
		}

		if (all_display_windows_closed != nullptr) {
			delete all_display_windows_closed;
		}
	}
}
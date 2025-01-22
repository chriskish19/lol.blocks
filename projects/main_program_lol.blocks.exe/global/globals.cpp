#include "globals.hpp"

namespace global {
	window::log_window* log_window_p = new window::log_window;
	std::atomic<bool>* all_display_windows_closed = new std::atomic<bool>(false);
	
	
	
	void clean_up()
	{
		if (log_window_p != nullptr) {
			delete log_window_p;
		}

		if (all_display_windows_closed != nullptr) {
			delete all_display_windows_closed;
		}
	}
}
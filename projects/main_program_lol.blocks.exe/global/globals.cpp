#include "globals.hpp"

namespace global {
	window::log_window* log_window_p = new window::log_window;
	
	
	
	
	void clean_up()
	{
		if (log_window_p != nullptr) {
			delete log_window_p;
		}
	}
}
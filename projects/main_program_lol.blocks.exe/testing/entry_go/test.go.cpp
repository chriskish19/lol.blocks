#include "test.go.hpp"

errors::codes testing::go() {
	// global logging window messages throughout whole program
	std::thread lw_thread(&window::log_window::go, global::log_window_p->load());

	return errors::codes();
}
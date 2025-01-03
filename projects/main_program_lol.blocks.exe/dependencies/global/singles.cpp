#include "singles.hpp"

namespace singletons {
	// singleton objects
	main_lol_blocks_exe::window_manager* global_window_manager_p = main_lol_blocks_exe::window_manager::get_me_a_window_create_p();
	main_lol_blocks_exe::window_class_mt* global_window_class_mt_p = main_lol_blocks_exe::window_class_mt::create_window_class_mt_instance();
}

void singletons::clean_up_singles() noexcept {
	// clean up the singleton objects
	if (global_window_manager_p) {
		delete global_window_manager_p;
	}
	if (global_window_class_mt_p) {
		delete global_window_class_mt_p;
	}
}
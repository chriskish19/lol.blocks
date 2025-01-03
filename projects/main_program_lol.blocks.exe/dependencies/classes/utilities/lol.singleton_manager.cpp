// class header include
#include "lol.singleton_manager.hpp"

namespace main_lol_blocks_exe {
	window_manager* m_public_window_manager = window_manager::get_me_a_window_create_p();
	window_class_mt* m_public_window_class_mt = window_class_mt::create_window_class_mt_instance();
}

void utilities::clean_up_destructor() noexcept
{
	// clean up all the singleton objects
	if (main_lol_blocks_exe::m_public_window_manager) {
		delete main_lol_blocks_exe::m_public_window_manager;
	}

	if (main_lol_blocks_exe::m_public_window_class_mt) {
		delete main_lol_blocks_exe::m_public_window_class_mt;
	}

	if (main_lol_blocks_exe::m_public_safe_exit) {
		delete main_lol_blocks_exe::m_public_safe_exit;
	}
}

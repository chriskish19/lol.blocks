#include "globals.hpp"

namespace main_lol_blocks_exe {
	// gates and latches for windows
	std::condition_variable* global_safe_exit_p = new std::condition_variable;
	std::atomic<bool>* global_safe_exit_gate_latch_p = new std::atomic<bool>(false);
	std::atomic<bool>* global_new_window_gate_latch_p = new std::atomic<bool>(false);
	std::condition_variable* global_window_create_signaler_p = new std::condition_variable();

	
}

void main_lol_blocks_exe::clean_up_globals() noexcept {
	// clean up gates and latches
	if (global_safe_exit_p) {
		delete global_safe_exit_p;
	}
	if (global_safe_exit_gate_latch_p) {
		delete global_safe_exit_gate_latch_p;
	}
	if (global_new_window_gate_latch_p) {
		delete global_new_window_gate_latch_p;
	}
	if (global_window_create_signaler_p) {
		delete global_window_create_signaler_p;
	}

	
}
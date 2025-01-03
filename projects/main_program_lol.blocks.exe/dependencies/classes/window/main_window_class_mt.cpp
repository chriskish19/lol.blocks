#include "main_window_class_mt.hpp"

namespace main_lol_blocks_exe {
	std::condition_variable* m_public_safe_exit = new std::condition_variable;
	std::atomic<bool>* m_public_safe_exit_gate_latch = new std::atomic<bool>(false);
}
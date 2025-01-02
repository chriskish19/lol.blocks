#ifndef LOL_BLOCKS_SINGLETONS_HEADER_HPP
#define LOL_BLOCKS_SINGLETONS_HEADER_HPP

// include win32gui
#include "win32gui.include/win32gui.include.hpp"

// stl
#include "main_program_lol.blocks.exe/dependencies/stl/stl_macro_definitions.hpp"

// windows api
#include "main_program_lol.blocks.exe/dependencies/win32api/windows_includes.hpp"

// class dependencies
#include "main_program_lol.blocks.exe/dependencies/classes/window/main_window_class.hpp"
#include "main_program_lol.blocks.exe/dependencies/classes/window/main_window_class_mt.hpp"

namespace utilities {
	class singleton_manager {
	public:
		static singleton_manager* get_singleton_manager() noexcept;

		~singleton_manager();
	private:
		static void create_singleton_manager_instance() noexcept;

		singleton_manager() = default;

		inline static singleton_manager* private_inline_static_singleton_manager_instance_p = nullptr;

	public:
		// our singletons!!
		// thread_manager* m_tm = thread_manager::create_thread_manager();
		main_lol_blocks_exe::window_manager* m_wm = main_lol_blocks_exe::window_manager::get_me_a_window_create_p();
		main_lol_blocks_exe::window_class_mt* m_wc_mt = main_lol_blocks_exe::window_class_mt::create_window_class_mt_instance();
	};
}


// LOL_BLOCKS_SINGLETONS_HEADER_HPP
#endif
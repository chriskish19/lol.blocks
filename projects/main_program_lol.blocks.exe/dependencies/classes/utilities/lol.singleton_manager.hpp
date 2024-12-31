#ifndef LOL_BLOCKS_SINGLETONS_HEADER_HPP
#define LOL_BLOCKS_SINGLETONS_HEADER_HPP

#include "main_program_lol.blocks.exe/dependencies/pch/pch.hpp"

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
		thread_manager* m_tm = thread_manager::create_thread_manager();
		main_lol_blocks_exe::window_create* m_wc = main_lol_blocks_exe::window_create::get_me_a_window_create_p();
	};
}


// LOL_BLOCKS_SINGLETONS_HEADER_HPP
#endif
#pragma once

#include "main_program_lol.blocks.exe/dependencies/stl/stl_macro_definitions.hpp"

namespace utilities {
	class thread_creators {
	public:
		thread_creators() = default;
		thread_creators() noexcept {

		}

	private:



	};



	// singleton class
	class thread_manager {
	public:
		thread_manager* create_thread_manager() {
			if (m_instance_threads == nullptr) {
				thread_manager* hello_threaders = new thread_manager();
				m_instance_threads = hello_threaders;
			}
			return m_instance_threads;
		}

		~thread_manager() {
			delete this;
		}

		template<typename function_type,typename ... argrs>
		std::thread* create_new_thread(std::function<function_type> funcer, argrs ... individual_arguments);
		void kill_thread(std::thread::id this_threads_id) {
			auto found_thread = m_thread_p_id_mp.find(this_threads_id);
			if (found_thread != m_thread_p_id_mp.end()) {
				// we found you thread ahaha!
				// now we kill you...
				// the thread that created you can only kill you!!!

			}
		}
	private:
		thread_manager() = default;

		thread_manager* m_instance_threads = nullptr;

		std::unordered_map < std::thread::id,std::thread*> m_thread_p_id_mp = {};
	};


	template<typename function_type, typename ... argrs>
	inline std::thread* thread_manager::create_new_thread(std::function<function_type> funcer, argrs ...individual_arguments)
	{
		std::thread* thread_obj = new std::thread(funcer, individual_arguments);
		m_thread_p_id_mp.emplace(thread_obj->get_id(), thread_obj);
		return thread_obj;
	}
}
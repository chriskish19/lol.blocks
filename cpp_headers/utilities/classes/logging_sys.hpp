#pragma once
#include "pch/lol.blocks.main.PCH.hpp"

#ifdef LOG_SYS_HPP
#define LOG_SYS_HPP_INCLUDED
#else
#define LOG_SYS_HPP_NOT_INCLUDED


#include "lol.blocks_error_codes.hpp"
#include "memory_heap_sys.hpp"


// because we want the fastest possible frame rate we must pre allocate 
// the log_info class and give it a heap ~4MB

class log_info : public lolblock_ec{
public:
	log_info() = default;

	// important notes: this will need to be manually set when a window is created, up to the programmer me not to screw it up.
	void set_window_handle_for_output_logging(HWND window_handle) noexcept { m_logging_window = window_handle; }

	// functions here that collect log data from win32 api and dx12 and lol.blocks internals
private:
	HWND m_logging_window = nullptr;
};


// log_info_manager is designed to be a single class that manages log_info objects
// specifically for win32 open windows, each window will have one log object in use at any given time.
// when a window is closed a log_info object is destroyed, and when a window is created
// a log_info object is also created. 
// This is useful for a logging window that is text based similar to a console window but win32 gui based.

class log_info_manager {
private:
	log_info_manager() = default;

	std::unordered_multimap<std::thread::id, log_info*> m_thread_id_to_log_info_p_mp = {};
	
	log_info_manager* m_log_info_manager_single_instance_p = nullptr;

	inline static log_info_manager* private_inline_static_log_info_manager_single_instance_p = nullptr;

	inline static bool private_inline_static_is_log_info_manager_init = false;

	bool m_is_this_log_info_manager_init = true;


	struct log_info_memory_heap_struct {
		const unsigned long long int m_log_info_memory_heap_size_in_bytes = 4194304;
		
	};

public:
	struct thread_log_struct {
		log_info* log_info_obj_p = nullptr;
		std::thread::id this_thread_id = {};
	};


	bool get_is_this_log_info_manager_init() noexcept { return m_is_this_log_info_manager_init; }


	static log_info_manager* create_log_info_manager() noexcept{
		if (private_inline_static_is_log_info_manager_init == false) {
			log_info_manager* this_instance = new log_info_manager;
			this_instance->m_log_info_manager_single_instance_p = this_instance;
			private_inline_static_is_log_info_manager_init = true;
			return this_instance;
		}
		return nullptr;
	}

	~log_info_manager() {
		// release log_info memory here
	}

	void allocate_log_info_objs(unsigned int count=1,std::thread::id this_thread_id = std::this_thread::get_id()) noexcept{
		// use locks here then allocate new objects and add to the map
	}

	void deallocate_log_info_objs(unsigned int count = 1, std::thread::id this_thread_id = std::this_thread::get_id()) noexcept {
		// use locks here and deallocate objects and remove them from the map

	}

	void assign_log_info_obj_p_to_thread_id(const log_info_manager::thread_log_struct& thread_id_log_simple_obj) noexcept {
		// use locks here to prevent concurrent access to thread id log map

		// if the thread id is new add it to the map and add the log_info* to it.
		// because its a multimap emplace() will handle the case where the same thread has
		// more than one log_info obj assigned to it and also the case where the thread already 
		// exists in the map
		
	}


};

#endif
#ifndef LOGGING_SYSTEM_HEADER_HPP
#define LOGGING_SYSTEM_HEADER_HPP

class log_info : public lolblock_ec{
public:
	log_info() = default;

	void set_window_handle_for_output_logging(HWND window_handle) noexcept { m_logging_window = window_handle; }

private:
	HWND m_logging_window = nullptr;
};


class log_info_manager {
private:
	log_info_manager() = default;

	std::unordered_multimap<std::thread::id, log_info*> m_thread_id_to_log_info_p_mp = {};
	
	log_info_manager* m_log_info_manager_single_instance_p = nullptr;

	inline static log_info_manager* private_inline_static_log_info_manager_single_instance_p = nullptr;

	inline static bool private_inline_static_is_log_info_manager_init = false;

	bool m_is_this_log_info_manager_init = true;


	struct log_info_memory_heap_struct {
		const unsigned long long int m_log_info_memory_heap_size_in_bytes = 4194304; // ~4MB
		
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

	}

	void allocate_log_info_objs(unsigned int count=1,std::thread::id this_thread_id = std::this_thread::get_id()) noexcept{
		
	}

	void deallocate_log_info_objs(unsigned int count = 1, std::thread::id this_thread_id = std::this_thread::get_id()) noexcept {
		

	}

	void assign_log_info_obj_p_to_thread_id(const log_info_manager::thread_log_struct& thread_id_log_simple_obj) noexcept {
		
	}


};

// LOGGING_SYSTEM_HEADER_HPP
#endif
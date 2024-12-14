#ifndef LOL_BLOCKS_MEMORY_MANAGER_HEADER_HPP
#define LOL_BLOCKS_MEMORY_MANAGER_HEADER_HPP



class cpu_memory_pool {
public:
	cpu_memory_pool(unsigned long long int requested_heap_size_bytes) noexcept 
	:m_heap_size_in_bytes(requested_heap_size_bytes){}

	template<typename memory_type>
	struct memory_blob_index_struct {
		unsigned long long int index = 0;
		memory_type* blob_p = nullptr;
		log_info attempted_allocation_log = {};
	};


	template<typename memory_type>
	memory_blob_index_struct<memory_type> send_new_request_for_memory() noexcept{
		unsigned long long int max_total_current_available_physical_memory = this->get_available_physical_memory_in_bytes();
		unsigned long long int available_physical_memory_buffered = 0ull;

		if (max_total_current_available_physical_memory > m_system_ram_buffer_zone_in_bytes) {
			available_physical_memory_buffered = max_total_current_available_physical_memory - m_system_ram_buffer_zone_in_bytes;
		}
		else {
			
		}

		if (available_physical_memory_buffered > m_heap_size_in_bytes) {
			
			memory_type* requested_blob = reinterpret_cast<memory_type*>(malloc(m_heap_size_in_bytes));

			if (requested_blob == nullptr) {
				
			}
			else {
				m_memory_blob_any_vec_ps.push_back(requested_blob);
				++m_memory_blob_any_vec_index; 
				return {m_memory_blob_any_vec_index,requested_blob,log_info()};
			}
		}
		else {
			
		}
	}

	template<typename new_memory_type>
	memory_blob_index_struct<new_memory_type> change_memory_type_for_reuse(unsigned int index=0) noexcept{

	}



private:
	unsigned long long int m_memory_blob_any_vec_index = 0;

	// buffer of 1GB
	const unsigned long long int m_system_ram_buffer_zone_in_bytes = (1024ull * 1024ull * 1024ull);

	unsigned long long int m_heap_size_in_bytes = 0;

	std::vector<std::any> m_memory_blob_any_vec_ps = {};

	unsigned long long int get_available_physical_memory_in_bytes() {
		MEMORYSTATUSEX memoryStatus = {};
		memoryStatus.dwLength = sizeof(MEMORYSTATUSEX);
		if (GlobalMemoryStatusEx(&memoryStatus) == false) {
			
			return 0;
		}

		return static_cast<unsigned long long int>(memoryStatus.ullAvailPhys);
	}

};

template<typename memory_type>
class gpu_memory_pool {
public:
	gpu_memory_pool(unsigned long long int requested_heap_size_bytes) {

	}

private:


};

class memory_pool_manager {

};




#endif
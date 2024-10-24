#pragma once
#include <windows.h>
#include <d3d12.h>
#include "logging_sys.hpp"
#include <vector>
#include <any>


class cpu_memory_pool {
public:
	cpu_memory_pool(unsigned long long int requested_heap_size_bytes) noexcept 
	:m_heap_size_in_bytes(requested_heap_size_bytes){}

	template<typename memory_type>
	memory_type* send_new_request_for_memory() noexcept{
		unsigned long long int current_available_physical_memory = this->get_available_physical_memory_in_bytes();

	}

	template<typename new_memory_type>
	new_memory_type* change_memory_type_for_reuse(unsigned int index=0) noexcept{

	}

private:
	unsigned long long int m_heap_size_in_bytes = 0;

	std::vector<std::any> m_memory_blob_any_vec_ps = {};

	unsigned long long int get_available_physical_memory_in_bytes() {
		MEMORYSTATUSEX memoryStatus = {};
		memoryStatus.dwLength = sizeof(MEMORYSTATUSEX);
		if (GlobalMemoryStatusEx(&memoryStatus) == false) {
			// log error here, need to finish logging system first!
			
			// failed so return 0 bytes avaliable
			return 0;
		}

		return memoryStatus.ullAvailPhys;
	}

};

template<typename memory_type>
class gpu_memory_pool {
public:
	gpu_memory_pool(unsigned long long int requested_heap_size_bytes) {

	}

private:


};



// this class is designed to be a single class object that keeps track of allocations
// and cleans up memory when needed
class memory_pool_manager {

};
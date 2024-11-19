#pragma once
#include "pch/lol.blocks.main.PCH.hpp"


// simple wrapper class that holds other singleton instances and deletes the memory 
// when the program ends, typically singleton objects are used from program beginging to end
class singleton_manager {
public:
	static singleton_manager* get_singleton_manager() noexcept;

	~singleton_manager();
private:
	static void create_singleton_manager_instance() noexcept;

	singleton_manager() = default;

	inline static singleton_manager* private_inline_static_singleton_manager_instance_p = nullptr;

	// create singleton objects here
	// 


};
// class header include
#include "lol.singleton_manager.hpp"

utilities::singleton_manager* utilities::singleton_manager::get_singleton_manager() noexcept
{
	create_singleton_manager_instance();
	return private_inline_static_singleton_manager_instance_p;
}

void utilities::singleton_manager::create_singleton_manager_instance() noexcept
{
	if (private_inline_static_singleton_manager_instance_p == nullptr) {
		private_inline_static_singleton_manager_instance_p = new singleton_manager();
	}
}

utilities::singleton_manager::~singleton_manager()
{
	// clean up all the singleton objects
}
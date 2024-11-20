#include "utilities/classes/lol.singleton_manager.hpp"

singleton_manager* singleton_manager::get_singleton_manager() noexcept
{
	create_singleton_manager_instance();
	return private_inline_static_singleton_manager_instance_p;
}

void singleton_manager::create_singleton_manager_instance() noexcept
{
	if (private_inline_static_singleton_manager_instance_p == nullptr) {
		private_inline_static_singleton_manager_instance_p = new singleton_manager();
	}
}

singleton_manager::~singleton_manager()
{
	// clean up all the singleton objects
}
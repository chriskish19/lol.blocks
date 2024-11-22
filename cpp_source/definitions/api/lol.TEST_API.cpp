#include "testing/test_api.hpp"

lolblock_ec TEST_API::for_loop_count()
{
	std::vector<std::any> all_exceptions_vec = {lol_base_exception(),
								win32_window_error_exception(),
								win32_general_error()};
}

lolblock_ec TEST_API::vector_adding()
{
	return lolblock_ec();
}

lolblock_ec TEST_API::map_find()
{
	return lolblock_ec();
}

lolblock_ec TEST_API::standard_init_templates()
{
	// test the memory allocation system
	///////////////////////////////////////////////////////////////////////
	
	// test the return object instantiation
	// we arent testing the memory allocation just the object instantiation
	
	cpu_memory_pool cpu_memory_pool_test_obj(0);
	auto memory_info = cpu_memory_pool_test_obj.send_new_request_for_memory<int>();

	gpu_memory_pool<int> gpu_memory_pool_test_obj(0);

	memory_pool_manager memory_pool_manager_test_obj; // this will be a singleton instance


	// test the exception system
	////////////////////////////////////////////////////////////////////////


}
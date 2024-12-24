#include "testing/test_api.hpp"

utilities::lolblock_ec TEST_API::for_loop_count()
{
	std::vector<std::any> all_exceptions_vec = { utilities::lol_base_exception(),
								utilities::win32_window_error_exception(),
								utilities::win32_general_error()};
}

utilities::lolblock_ec TEST_API::vector_adding()
{
	return utilities::lolblock_ec();
}

utilities::lolblock_ec TEST_API::map_find()
{
	return utilities::lolblock_ec();
}

utilities::lolblock_ec TEST_API::standard_init_templates()
{
	// test the memory allocation system
	///////////////////////////////////////////////////////////////////////
	
	// test the return object instantiation
	// we arent testing the memory allocation just the object instantiation
	
	utilities::cpu_memory_pool cpu_memory_pool_test_obj(0);
	auto memory_info = cpu_memory_pool_test_obj.send_new_request_for_memory<int>();

	utilities::gpu_memory_pool<int> gpu_memory_pool_test_obj(0);

	utilities::memory_pool_manager memory_pool_manager_test_obj; // this will be a singleton instance


	// test the exception system
	////////////////////////////////////////////////////////////////////////


}
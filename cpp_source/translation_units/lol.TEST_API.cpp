#include "testing/test_api.hpp"

bool TEST_API::standard_init()
{
	// test the memory allocation system
	///////////////////////////////////////////////////////////////////////
	
	// test the return object instantiation
	// we arent testing the memory allocation just the object instantiation
	
	cpu_memory_pool cpu_memory_pool_test_obj(0);
	auto memory_info = cpu_memory_pool_test_obj.send_new_request_for_memory<int>();

	gpu_memory_pool<int> gpu_memory_pool_test_obj(0);

	memory_pool_manager memory_pool_manager_test_obj; // this will be a singleton instance


	// test the logging system
	////////////////////////////////////////////////////////////////////////


}
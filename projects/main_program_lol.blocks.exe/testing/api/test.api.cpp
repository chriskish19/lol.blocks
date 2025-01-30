#include "test.api.hpp"

errors::codes testing::create_number_of_windows(size_t number_of_open_windows)
{
	window::window_class_mt* local_windows = new window::window_class_mt;
	local_windows->go();
	
	
	return errors::codes();
}

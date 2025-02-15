#include "globals.hpp"


// log window
namespace global {
	std::unique_ptr<global_manager> system_global_manager_p = std::make_unique<global_manager>();
}
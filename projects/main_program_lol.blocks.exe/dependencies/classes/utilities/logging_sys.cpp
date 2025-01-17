// class header include
#include "logging_sys.hpp"

utilities::base_logger::base_logger()
{

}

utilities::base_logger::~base_logger()
{

}

utilities::base_logger::time_str::time_str()
{
	m_time_str.reserve(reserved_length_heap_mem);
}

errors::codes utilities::base_logger::time_str::set_current_time()
{
	// Get the current time as a time_point
	auto now = std::chrono::system_clock::now();

	// Convert to a time_t, which represents the time in seconds since the epoch
	auto current_time_tt = std::chrono::system_clock::to_time_t(now);

	// Format the time using a stringstream
	ostringstream oss;
	oss << std::put_time(std::localtime(&current_time_tt), "%Y-%m-%d %H:%M:%S");

	m_time_str = oss.str();
}

utilities::base_logger::log_message::log_message()
{
	m_message.reserve(reserved_length_mem_heap);
}

errors::codes utilities::base_logger::log_message::set_log_message(const string& message)
{
	m_message = message;
}

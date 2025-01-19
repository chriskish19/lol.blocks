// class header include
#include "logging_sys.hpp"

utilities::logger::base_logger::base_logger()
{

}

utilities::logger::base_logger::~base_logger()
{
	if (m_log_message_p != nullptr) {
		delete m_log_message_p;
	}
	if (m_time_str_p != nullptr) {
		delete m_time_str_p;
	}
}

errors::codes utilities::logger::base_logger::log_a_message(const string& message)
{
	if (message.length() > log_message::reserved_length_mem_heap) {
#if ENABLE_FULL_DEBUG
		throw errors::string_length_too_long();
#endif
		return errors::codes::string_length_too_long;
	}
	
	m_time_str_p->set_current_time();
	m_log_message_p->set_log_message(m_time_str_p->m_time_str + message);
	return errors::codes::success;
}

utilities::logger::base_logger::time_str::time_str()
{
	m_time_str.reserve(reserved_length_heap_mem);
}

errors::codes utilities::logger::base_logger::time_str::set_current_time()
{
	// Get the current time as a time_point
	auto now = std::chrono::system_clock::now();

	// Convert to a time_t, which represents the time in seconds since the epoch
	auto current_time_tt = std::chrono::system_clock::to_time_t(now);

	// Format the time using a stringstream
	ostringstream oss;
	oss << std::put_time(std::localtime(&current_time_tt), "[%Y-%m-%d %H:%M:%S]");

	m_time_str = oss.str();
	return errors::codes::success;
}

utilities::logger::base_logger::log_message::log_message()
{
	m_message.reserve(reserved_length_mem_heap);
}

errors::codes utilities::logger::base_logger::log_message::set_log_message(const string& message)
{
	m_message = message;
	return errors::codes::success;
}

utilities::logger::logger()
{
	
}

utilities::logger::~logger()
{
	
}

utilities::logger::logs::logs()
{
	m_bl_vec_p.reserve(m_bl_vec_reserved_capacity);

	// allocate all the base_logs
	for (size_t i = 0; i < m_bl_vec_reserved_capacity; ++i) {
		base_logger* new_base_logger = new base_logger;
		m_bl_vec_p.push_back(new_base_logger);
	}
}

utilities::logger::logs::~logs()
{
	// deallocate all the base loggers
	for (auto p : m_bl_vec_p) {
		if (p != nullptr) {
			delete p;
		}
	}
}

utilities::string utilities::logger::logs::get_most_recent_log()
{
	base_logger* last_element = m_bl_vec_p.back();
	base_logger::log_message* lm_p = last_element->get_message_p();
#if ENABLE_FULL_DEBUG
	if (last_element == nullptr || lm_p == nullptr) {
		throw errors::pointer_is_nullptr();
	}
#endif

#if ENABLE_MED_LOGGING
	if (lm_p->m_message.empty()) {
		return READ_ONLY_STRING("most recent log is empty...");
	}
#endif
	
	return lm_p->m_message;
}

utilities::string utilities::logger::logs::get_log_by_index(size_t index)
{
#if ENABLE_FULL_DEBUG
	if (index > m_bl_vec_reserved_capacity) {
		throw errors::index_out_of_range();
	}
#endif

	base_logger* elm = m_bl_vec_p.at(index);
}

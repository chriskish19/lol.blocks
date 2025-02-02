#include "file_logger.hpp"

utilities::file_logs::file_logs(const std::filesystem::path& log_file_path)
{
	
}

errors::codes utilities::file_logs::create_log_file()
{
	std::fstream log_file(m_log_file_path);
	
	
	return errors::codes();
}

/****************************************************************
	Header: silent_logger.hpp

	Purpose: xxxx

****************************************************************/

#pragma once

// all macros
#include "main_program_lol.blocks.exe/macros/include/lol.macros.include.hpp"

// all external library headers
#include "main_program_lol.blocks.exe/pch/includes/external.hpp"

// classes
#include "main_program_lol.blocks.exe/classes/utilities/logging_sys.hpp"

// errors
#include "main_program_lol.blocks.exe/errors/lol.codes.hpp"

namespace utilities {
	class file_logs : public logger {
	public:
		file_logs() = default;
		file_logs(const std::filesystem::path& log_file_path);

	protected:
		std::filesystem::path m_log_file_path = std::filesystem::current_path()/"log_file.txt";

		errors::codes create_log_file();
	};
}